#include "../include/WebPage.hpp"
#include <sstream>
#include <regex>
#include <queue>
#include <vector>
#include <iterator>
#include <algorithm>

using std::back_inserter;
using std::priority_queue;
using std::regex;
using std::regex_replace;
using std::stringstream;
using std::vector;

namespace wd
{
    WebPage::WebPage(string &doc, SplitTool &splitTool,
                     set<string> &stopWords)
        : _doc(doc), _totalWords(0), _splitTool(splitTool), _stopWords(stopWords)
    {
        processDoc();
    }

    //获取文档的docid
    int WebPage::getDocid() const
    {
        return _docId;
    }

    string WebPage::getDoc() const
    {
        return _doc;
    }

    //获取文档的词频统计map
    map<string, int> &WebPage::getWordsMap()
    {
        return _wordsMap;
    }

    int WebPage::getTotalWords() const
    {
        return _totalWords;
    }

    //对格式化文档进行处理
    void WebPage::processDoc()
    {
        stringstream ss(_doc);
        string word;

        while (ss >> word)
        {
            if ("<title>" == word)
            {
                ss >> _docTitle;
                storeWords(_docTitle);
            }
            else if ("<link>" == word)
            {
                ss >> _docUrl;
            }
            else if ("<description>" == word)
            {
                ss >> _docSummary;
                storeWords(_docSummary);
            }
            else if ("<content>" == word)
            {
                ss >> _docContent;
                storeWords(_docContent);
            }
        }

        //获取单词总数
        for (auto &word : _wordsMap)
        {
            _totalWords += word.second;
        }

        //统计出前20个词
        calcTopK(TOPK_NUMBER);
    }

    //词频统计
    void WebPage::storeWords(const string &str)
    {
        vector<string> vec = _splitTool.cut(str);
        for (auto &elem : vec)
        {
            if (_stopWords.find(elem) != _stopWords.end())
            {
                continue;
            }
            _wordsMap[elem]++;
        }
    }

    class Comp
    {
    public:
        bool operator()(const pair<string, int> &rhs, const pair<string, int> &lhs)
        {
            return lhs.second > rhs.second; //降序
        }
    };

    void WebPage::calcTopK(size_t tpk)
    {
        priority_queue<pair<string, int>, vector<pair<string, int>>, Comp> priQue;
        for (auto &elem : _wordsMap)
        {
            priQue.push(elem);
            if (priQue.size() > tpk)
            {
                priQue.pop();
            }

            //赋值给_topWords
            while (!priQue.empty())
            {
                _topWords.push_back(priQue.top().first);
                priQue.pop();
            }

            std::sort(_topWords.begin(), _topWords.end()); //排序
        }
    }

    //判断两篇文档是否相等，TOPK算法重载==运算符
    bool operator==(const WebPage &lhs, const WebPage &rhs)
    {
        vector<string> vec1 = lhs._topWords;
        vector<string> vec2 = rhs._topWords;
        vector<string> intersection;
        std::set_intersection(vec1.begin(), vec1.end(),
                              vec2.begin(), vec2.end(), back_inserter(intersection));
        if (intersection.size() == TOPK_NUMBER) //前K个高频词都相同
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    //对文档按Docid进行排序
    bool operator<(const WebPage &lhs, const WebPage &rhs)
    {
        return lhs < rhs;
    }
}
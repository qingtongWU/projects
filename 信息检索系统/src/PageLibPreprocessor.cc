#include "../include/PageLibPreprocessor.hpp"
#include <cmath>

using std::cerr;
using std::make_pair;
using std::ofstream;

namespace wd
{
    PageLibPreprocessor::PageLibPreprocessor(const string &stopWordsdir, const string &ripePagedir, const string &offsetdir)
        : _stopWordsdir(stopWordsdir), _ripePagedir(ripePagedir), _offsetdir(offsetdir)
    {

        readInfoFromFile();
    }

    void PageLibPreprocessor::readInfoFromFile()
    {
        //读取停词库
        ifstream stop_words_File(_stopWordsdir);
        if (!stop_words_File.good())
        {
            cerr << "file open error" << endl;
            return;
        }
        string words;
        while (getline(stop_words_File, words))
        {
            _stopWords.insert(words);
        }

        //读取偏移库
        ifstream pageFile(_ripePagedir);
        ifstream offsetFile(_offsetdir);
        if (!pageFile.good() || !offsetFile.good())
        {
            cerr << "file open error" << endl;
            return;
        }

        //去重
        string s;
        int docid;
        off_t beg, end;
        while (getline(offsetFile, s))
        {
            stringstream ss(s);
            ss >> docid >> beg >> end;

            char buf[65536] = {0};
            pageFile.read(buf, end - beg);
            string doc(buf);
            WebPage page(doc, _splitTool, _stopWords);

            //如果是相同的网页则不必再次加入
            if (std::find(_pageLib.begin(), _pageLib.end(), page) == _pageLib.end())
            {
                _pageLib.push_back(std::move(page));
            }
        }
        stop_words_File.close();
        offsetFile.close();
        pageFile.close();
    }

    //去重后重新存入
    void PageLibPreprocessor::storeOnDisk(const string &newPageFile, const string &newoffset, const string &invertIndex)
    {
        ofstream pageFile(newPageFile, ofstream::out);
        ofstream offsetFile(newoffset, ofstream::out);
        ofstream invertIndexFile(invertIndex, ofstream::out); //文件输出流
        if (!pageFile.good() || !offsetFile.good() || !invertIndexFile.good())
        {
            cerr << "file open error!" << endl;
            return;
        }

        //写入新的网页库与偏移库
        for (size_t i = 0; i < _pageLib.size(); i++)
        {
            string doc = _pageLib[i].getDoc(); //获取文档
            //计算文档开始位置和结束位置
            off_t beg = pageFile.tellp(); //文档开始的位置
            pageFile << doc;              //将文档写入文件
            off_t end = pageFile.tellp();
            offsetFile << i << " " << beg << " " << end << endl;
        }

        //计算DF
        getDF();

        //建立倒排索引表
        buildInvertIndexTable();

        //写入倒排索引文件
        for (auto &elem : _invertIndexTable)
        {
            invertIndexFile << elem.first << " "; //写入单词
            for (auto &es : elem.second)
            {
                invertIndexFile << es.first << " " << es.second << " "; //写入单词所在文档和权重
            }
            invertIndexFile << endl;
        }

        pageFile.close();
        offsetFile.close();
        invertIndexFile.close();
        cout << "新的网页库，新的偏移库和倒排索引库创建成功" << endl;
    }

    //建立倒排索引表
    void PageLibPreprocessor::buildInvertIndexTable()
    {
        vector<vector<pair<string, double>>> weights(_pageLib.size()); //<单词，未归一化权重> temp下标代表文章id

        for (size_t i = 0; i < _pageLib.size(); i++)
        {
            map<string, int> &wordsMap = _pageLib[i].getWordsMap();
            for (auto &elem : wordsMap)
            {                             // <单词，词频>
                string word = elem.first; //获取单词

                double TF = (double)elem.second / _pageLib[i].getTotalWords();
                int DF = _DF[word];
                int N = _pageLib.size(); //文档总数

                //逆文档频率，表示该词对于该篇文章的重要性系数
                double IDF = log10((double)N / (DF + 1)); //+1为了防止分母为0
                double w = TF * IDF;
                weights[i].push_back(make_pair(word, w));
            }
        }

        //将单词的权重进行归一化处理 W = w /sqrt(w1^2 + w2^2 +...+ wn^2)
        for (size_t i = 0; i < weights.size(); i++)
        {
            vector<pair<string, double>> &wordsVec = weights[i]; //i号文档的 <单词，未处理权重>
            double sum = 0.0;
            for (auto &elem : wordsVec)
            {
                sum += elem.second * elem.second;
            }
            sum = sqrt(sum);
            for (auto &elem : wordsVec)
            {
                elem.second /= sum;
            }
        }

        //插入结果到倒排索引表
        for (size_t i = 0; i < weights.size(); i++)
        {
            vector<pair<string, double>> &wordsVec = weights[i]; //i号文档的 <单词，归一化权重>
            for (auto &elem : wordsVec)
            {
                _invertIndexTable[elem.first].push_back(make_pair(i, elem.second));
            }
        }
    }

    //得到该词在所有文章中出现的次数DF
    void PageLibPreprocessor::getDF()
    {
        for (size_t i = 0; i < _pageLib.size(); i++)
        {
            map<string, int> &wordsMap = _pageLib[i].getWordsMap();
            for (auto &elem : wordsMap)
            {
                _DF[elem.first]++;
            }
        }
    }
}
#ifndef __WEBPAGE_HPP__
#define __WEBPAGE_HPP__

#include "../include/SplitTool.hpp"
#include <string>
#include <vector>
#include <map>
#include <set>

using std::map;
using std::pair;
using std::set;
using std::string;
using std::vector;

namespace wd
{
    const static size_t TOPK_NUMBER = 10; //网页中词频最高的10个词

    //网页类
    class WebPage
    {
    public:
        friend bool operator==(const WebPage &lhs, const WebPage &rhs); //判断两篇文档是否相等
        friend bool operator<(const WebPage &lhs, const WebPage &rhs);  //对文档按Docid进行排序

        WebPage(string &doc, SplitTool &SplitTool,
                set<string> &stopWords);

        int getDocid() const;  //获取文档的docid
        string getDoc() const; //获取文档

        map<string, int> &getWordsMap(); //获取文档的词频统计map

        int getTotalWords() const; //获取单词总数

        void processDoc(); //对格式化文档进行处理

        void storeWords(const string &str); //词频统计

        void calcTopK(size_t tpk); //求取文档的topk集

        //void WebPage::makeSummary(const map<string,int>& wordsMap);

        string getTitle() const { return _docTitle; }
        string getLink() const { return _docUrl; }
        string getSummary() const { return _docSummary; }

    private:
        string _doc;        //整篇文档，包含在xml中
        int _docId;         //文档id
        string _docTitle;   //文档标题
        string _docUrl;     //文档url
        string _docContent; //文档内容
        string _docSummary; //文档摘要，自动生成

        int _totalWords;            //单词总数
        vector<string> _topWords;   //词频最高的20个词
        map<string, int> _wordsMap; //保存每篇文档所有的词语和词频，不包括停用词

        SplitTool &_splitTool;   //cppjieba中文分词库
        set<string> &_stopWords; //停词库
    };

}

#endif
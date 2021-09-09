#ifndef __PAGELIBPREPROCESSOR_HPP__
#define __PAGELIBPREPROCESSOR_HPP__

#include "Configuration.hpp"
#include "SplitTool.hpp"
#include "WebPage.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include <unordered_map>

using std::cout;
using std::endl;
using std::ifstream;
using std::set;
using std::string;
using std::stringstream;
using std::unordered_map;

namespace wd
{
    //网页去重，建立倒排索引
    class PageLibPreprocessor
    {
    public:
        PageLibPreprocessor(const string &sdir, const string &rdir, const string &odir); //构造函数
        //void doProcess();//执行预处理

        void readInfoFromFile(); //从停词库，网页库，偏移库读取数据, 进行去重

        void cutRedundantPages(); //对冗余的网页去重

        void buildInvertIndexTable(); //构建倒排索引表
        void getDF();                 //获取DF

        void storeOnDisk(const string &, const string &, const string &); //处理后的网页库写回磁盘

    private:
        string _stopWordsdir;
        string _ripePagedir;
        string _offsetdir;

        vector<WebPage> _pageLib;       //网页库的容器对象
        unordered_map<string, int> _DF; //文档频率 <单词，文档频率>

        //单词，所在文档id,单词权重
        unordered_map<string, vector<pair<int, double>>> _invertIndexTable; //倒排索引表对象
        set<string> _stopWords;                                             //停词库
        SplitTool _splitTool;                                               //分词对象
    };

}
#endif
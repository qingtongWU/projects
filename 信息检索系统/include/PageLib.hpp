#ifndef __PAGELIB_HPP__
#define __PAGELIB_HPP__

#include "DirScanner.hpp"
#include "Configuration.hpp"

#include "tinyxml2/RssReader.h"

#include <vector>
#include <string>
#include <map>

using std::map;
using std::pair;
using std::string;
using std::vector;

namespace wd
{
    class PageLib
    {
    public:
        PageLib(DirScanner &dir, RssReader &rss);
        //void create();//创建网页库
        void store(const string &pdir, const string &odir); //存储网页库和位置偏移库

    private:
        DirScanner &_dirScanner;             //目录扫描对象的引用
        RssReader &_rssReader;               //语料库处理对象
        vector<string> _pageLib;             //存放格式化后的网页的容器
        map<int, pair<int, int>> _offsetLib; //存放每篇文档在网页库的位置信息
    };
}
#endif

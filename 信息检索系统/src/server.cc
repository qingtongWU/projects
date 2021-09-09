#include "../include/DirScanner.hpp"
#include "../include/PageLib.hpp"
#include "../include/Configuration.hpp"
#include "../include/WebPage.hpp"
#include "../include/SplitTool.hpp"
#include "../include/PageLibPreprocessor.hpp"
#include "RssReader.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
using std::cout;
using std::endl;
using std::cerr;
using std::ifstream;
using std::set;
using std::stringstream;

using namespace wd;

//静态对象
Configuration *Configuration::_pInstance = new Configuration("/home/wuqingtong/c++/day32/conf/setting.conf"); //饿汉模式，绝对路径，线程安全

void test1()
{
    DirScanner rssScanner(Configuration::getpInstance()->getConfigMap()["rss_dir"]);
    vector<string> rssFiles = rssScanner.getFiles();
    for (auto &elem : rssFiles)
    {
        ifstream ifs(elem, ifstream::in);
        if (!ifs.good())
        {
            cerr << "open is failured" << endl;
        }
    }
}

//从rss语料库解析后导入 网页库 与 偏移库
void test2()
{
    DirScanner rssScanner(Configuration::getpInstance()->getConfigMap()["rss_dir"]);
    RssReader rssReader;
    vector<string> rssFiles = rssScanner.getFiles();
    for (auto &elem : rssFiles)
    {
        rssReader.parseRss(elem);
    }
    PageLib pageLib(rssScanner, rssReader);
    pageLib.store(Configuration::getpInstance()->getConfigMap()["ripePage_dir"], Configuration::getpInstance()->getConfigMap()["offset_dir"]);
}

//从已经建立好的网页库 和 偏移库 中读取
void test3()
{
    PageLibPreprocessor pageLibs(Configuration::getpInstance()->getConfigMap()["stop_words.utf8"]
        ,Configuration::getpInstance()->getConfigMap()["ripePage_dir"]
        ,Configuration::getpInstance()->getConfigMap()["offset_dir"]);

    pageLibs.storeOnDisk(Configuration::getpInstance()->getConfigMap()["NewRipePage_dir"]
        ,Configuration::getpInstance()->getConfigMap()["Newoffset_dir"]
        ,Configuration::getpInstance()->getConfigMap()["invertIndex_dir"]);
    
}

int main()
{
    test1();
    test2();
    test3();
    return 0;
}
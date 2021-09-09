#ifndef __DIRSCANNER_HPP__
#define __DIRSCANNER_HPP__

#include <vector>
#include <string>

using std::string;
using std::vector;

namespace wd{
    //目录扫描类，递归扫描
    class DirScanner{
    public:
        DirScanner(const string &dir);
        vector<string> &getFiles(); //返回_files的引用
        void traverse();            //获取某一目录下的所有文件
    private:
        string _dir;           //语料库目录
        vector<string> _files; //存放每个语料文件的绝对路径
    };
}
#endif
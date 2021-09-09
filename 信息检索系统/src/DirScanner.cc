#include "../include/DirScanner.hpp"
#include "../include/Configuration.hpp"

#include <sys/types.h>
#include <dirent.h>
#include <iostream>

using std::cerr;
using std::cout;
using std::endl;

namespace wd
{
    DirScanner::DirScanner(const string &dir)
        : _dir(dir)
    {
        traverse();//构造函数里面调用
    }

    vector<string> &DirScanner::getFiles(){
        return _files;
    }

    //获取某一目录下的所有文件
    void DirScanner::traverse(){
        DIR *dir = opendir(_dir.c_str());//打开目录
        if (!dir){
            cerr << "dir open error!" << endl;
            return;
        }

        //readdir是依次读出目录中的所有文件，每次只能读一个
        struct dirent *pdir;
        //读取目录信息
        while ((pdir = readdir(dir)) != nullptr){
            string filename(pdir->d_name);
            if (("." == filename) || ".." == filename){
                continue;
            }
            string str = _dir + "/" + pdir->d_name;//生成语料库路径
            _files.push_back(str);//语料库路径加入_files
        }
        closedir(dir);//关闭目录
    }
}

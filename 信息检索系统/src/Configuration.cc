#include "../include/Configuration.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;

namespace wd
{
    Configuration *Configuration::getpInstance(){
        
    if (_pInstance == nullptr){
        _pInstance = new Configuration("../conf/setting.conf");
        atexit(destroy);//单例模式的自动释放
    }
        return _pInstance;
    }

    //对象的销毁
    void Configuration::destroy(){
        if (_pInstance){
            delete _pInstance;
            _pInstance = nullptr;
        }
    }

    //获取存储配置文件内容的map
    map<string, string> &Configuration::getConfigMap(){
        return _configs;
    }

    //构造函数
    Configuration::Configuration(const string &filepath)
        : _configFilePath(filepath)
    {
        readConf(); //读取配置文件
    }

    //析构函数
    Configuration::~Configuration(){
        destroy();
    }

    //读取配置文件
    void Configuration::readConf(){
        ifstream ifs(_configFilePath, ifstream::in);//读取到文件末尾

        if (!ifs.good()){
            cerr << "ifstream is not good" << endl;
            return;
        }

        string line;
        string first, second;
        //一次读取一行
        while (getline(ifs, line)){
            stringstream ss(line);
            ss >> first >> second;
            _configs[first] = second;
        }
        ifs.close();
    }
}
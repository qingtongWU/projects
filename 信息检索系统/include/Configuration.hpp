#ifndef __CONFIGURATION_HPP__
#define __CONFIGURATION_HPP__

#include <string>
#include <map>

using std::map;
using std::string;

namespace wd
{
    //单例模式，配置文件类
    class Configuration
    {
    public:
        static Configuration *getpInstance(); //单例对象
        static void destroy();

        map<string, string> &getConfigMap(); //获取存储配置文件内容的map
    private:
        Configuration(const string &filepath); //构造函数私有化
        ~Configuration();
        void readConf(); //读取配置文件
    private:
        string _configFilePath;       //配置文件路径
        map<string, string> _configs; //配置文件内容
        static Configuration *_pInstance;
    };
}
#endif

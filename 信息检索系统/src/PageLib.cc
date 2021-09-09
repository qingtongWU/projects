#include "../include/PageLib.hpp"
#include "../include/Configuration.hpp"

namespace wd
{
    PageLib::PageLib(DirScanner &dirScanner, RssReader &rssReader)
        : _dirScanner(dirScanner)
        , _rssReader(rssReader) {}

    //生成网页库和网页偏移库
    void PageLib::store(const string &pdir, const string &odir){
        _rssReader.dump(pdir, odir, _pageLib, _offsetLib);
    }

}

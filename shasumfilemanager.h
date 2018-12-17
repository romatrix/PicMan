#ifndef SHASUMFILEMANAGER_H
#define SHASUMFILEMANAGER_H
#include <string>
#include <unordered_map>
#include <shasumfile.h>

class ShaSumFileManager
{
public:
    ShaSumFileManager(const std::string cacheFile): m_cacheFile(cacheFile){
        loadCache();
    }
    ~ShaSumFileManager(){
        storeCache();
    }


    bool scanDirectory(const std::string& path);
    bool storeCache();
    bool loadCache();

private:
    const std::string m_cacheFile;
    std::unordered_map<std::string, ShaSumFile> m_shaSumFileMap;
};

#endif // SHASUMFILEMANAGER_H

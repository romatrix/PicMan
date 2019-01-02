#ifndef SHASUMFILEMANAGER_H
#define SHASUMFILEMANAGER_H
#include <string>
#include <unordered_map>
#include <shasumfile.h>
#include <vector>

class ShaSumFileManager
{
public:
    ShaSumFileManager(const std::string settingsFile): m_settingsFile(settingsFile){
        loadCache();
    }
    ~ShaSumFileManager(){
        storeCache();
    }

    bool loadCacheFiles(const std::string cacheFiles);
    bool scanDirectory(const std::string& path);
    bool storeCache();
    bool loadCache();

private:
    std::string m_settingsFile;
    std::string m_cacheFile;
    std::unordered_map<std::string, ShaSumFile> m_shaSumFileMap;
};

#endif // SHASUMFILEMANAGER_H

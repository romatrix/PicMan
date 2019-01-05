#ifndef SHASUMFILEMANAGER_H
#define SHASUMFILEMANAGER_H
#include <string>
#include <map>
#include <shasumfile.h>
#include <vector>
#include <unordered_set>
#include "settingsfile.h"

class ShaSumFileManager
{
public:
    ShaSumFileManager(string casheFile);
    ~ShaSumFileManager();

    bool loadCacheFiles(const std::string cacheFiles);
    bool scanDirectory(const std::string& path);
    bool storeCache();
    bool loadCache();

private:
    void storeDuplicates(SettingsFile &cacheFile, const std::string &section, const std::vector<ShaSumFile> &duplicates);
    std::pair<const std::string&, const std::string&> splitPath(std::string path);
    std::string m_settingsFile;
    std::string m_cacheFile;
    std::map<std::string, ShaSumFile> m_shaSumFileMap;
    std::unordered_set<std::string> m_directories;
    std::unordered_set<std::string> m_files;
};

#endif // SHASUMFILEMANAGER_H

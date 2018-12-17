#ifndef SHASUMFILEMANAGER_H
#define SHASUMFILEMANAGER_H
#include <string>

class ShaSumFileManager
{
public:
    ShaSumFileManager(const std::string cacheFile): m_cacheFile(cacheFile){}

    bool scanDirectory(const std::string& path);
    bool storeCache();
    bool loadCache();

private:
    const std::string m_cacheFile;
};

#endif // SHASUMFILEMANAGER_H

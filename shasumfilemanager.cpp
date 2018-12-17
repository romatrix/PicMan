#include "shasumfilemanager.h"
#include <fstream>


bool ShaSumFileManager::scanDirectory(const std::string &path)
{
    return true;
}

bool ShaSumFileManager::storeCache()
{
    std::ofstream stream;

    stream.open(m_cacheFile);

    stream.close();

    return true;
}

bool ShaSumFileManager::loadCache()
{
    return true;
}

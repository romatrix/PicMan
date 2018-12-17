#include "shasumfilemanager.h"
#include <fstream>
#include <systemcmd.h>
#include <iostream>


bool ShaSumFileManager::scanDirectory(const std::string &path)
{
    std::stringstream ss = SystemCmd::execute("find " + path + " -iname '*.jpg' ");

    std::cout << ss.str();

    while(!ss.bad()){
        std::string line;
        std::getline(ss, line);

        int pos = line.find_last_of('/');
        std::string file = line.substr(pos + 1);
        std::string directory = line.substr(0, pos);
        ShaSumFile sha(directory, file);

        if(sha.getSha().length()){
            auto it = m_shaSumFileMap.find(sha.getSha());

            if(it != m_shaSumFileMap.end()){
                std::string duplicated = "duplicated picture 1st=" + it->second.getFullPath() + " second=" + sha.getFullPath();
                std::cout << duplicated << std::endl;
            } else {
                m_shaSumFileMap.emplace(std::make_pair(sha.getSha(), std::move(sha)));
            }
        }else{
            std::cout << "Something went wrong with: " << sha.getFullPath() << std::endl;
        }
    }

    return true;
}

bool ShaSumFileManager::storeCache()
{
    std::ofstream stream;

    stream.open(m_cacheFile);
    stream.exceptions(std::ifstream::failbit);

    try{
        for(const auto& file: m_shaSumFileMap){
            std::cout << "Storing: " << file.second.getFullPath() << std::endl;
            file.second.store(stream);
        }

        stream.close();
    }catch(...){
        std::cout << "Failed to store data in cach file:" << m_cacheFile << std::endl;
    }

    return true;
}

bool ShaSumFileManager::loadCache()
{
    std::ifstream stream;
    stream.exceptions(std::ifstream::failbit);

    try{
        stream.open(m_cacheFile);

        while(!stream.bad()){
            ShaSumFile file(stream);
            std::cout << "Loaded: " << file.getFullPath() << std::endl;
            m_shaSumFileMap.emplace(std::make_pair(file.getSha(), std::move(file)));
        }

        stream.close();
    } catch(...){
        std::cout << "Failed to load data from cache file:" << m_cacheFile << std::endl;
    }

    return true;
}

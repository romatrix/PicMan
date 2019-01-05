#include "shasumfilemanager.h"
#include <fstream>
#include <systemcmd.h>
#include <iostream>


ShaSumFileManager::ShaSumFileManager(std::string casheFile): m_cacheFile(casheFile){
    //loadCache();
}

ShaSumFileManager::~ShaSumFileManager(){
    //storeCache();
}

bool ShaSumFileManager::scanDirectory(const std::string &path)
{
    std::stringstream ss = SystemCmd::execute("find " + path + " -iname '*.jpg'");

    std::cout << ss.str();
    // true;

    std::cout << std::endl;

    while(ss){
        std::string line;
        std::getline(ss, line);

        if(!line.length()){
            break;
        }

        std::pair<const string &, const string &> path = splitPath(line);

        ShaSumFile sha(path.first, path.second);

        if(sha.getSha().length() && sha.getCreationDate().length()){
            string key = sha.getCreationDate()+ "_" + sha.getSha();
            auto it = m_shaSumFileMap.find(key);

            if(it != m_shaSumFileMap.end()){
                std::string duplicated = "duplicated picture 1st=" + it->second.getFullPath() + " second=" + sha.getFullPath();
                std::cout << duplicated << std::endl;
                it->second.addDuplicate(std::move(sha));
            } else {
                m_shaSumFileMap.emplace(std::make_pair(key, std::move(sha)));
            }
        }else{
            std::cout << "Something went wrong with: " << sha.getFullPath() << std::endl;
        }
    }

    return true;
}

bool ShaSumFileManager::storeCache()
{
    SettingsFile cacheFile(m_cacheFile);
    try{
        for(const auto& file: m_shaSumFileMap){
            std::cout << "Storing: " << file.second.getFullPath() << std::endl;
            cacheFile.addVariable(file.first, "file_name", file.second.getFileName());
            cacheFile.addVariable(file.first, "directory_name", file.second.getDirectoryName());
            storeDuplicates(cacheFile, file.first, file.second.getDuplicates());
        }

    }catch(...){
        std::cout << "Failed to store data in cach file:" << m_cacheFile << std::endl;
    }

    cacheFile.store();

    return true;
}

void ShaSumFileManager::storeDuplicates(SettingsFile& cacheFile, const std::string& section, const std::vector<ShaSumFile>& duplicates){
    for(int i = 0; i < duplicates.size(); ++i){
        cacheFile.addVariable(section, "file_name_duplicated" + std::to_string(i + 1), duplicates[i].getFileName());
        cacheFile.addVariable(section, "directory_name_duplicated" + std::to_string(i + 1), duplicates[i].getDirectoryName());
    }
}

bool ShaSumFileManager::loadCache()
{
//    std::ifstream stream;
//    stream.exceptions(std::ifstream::failbit);

//    try{
//        stream.open(m_cacheFile);

//        while(!stream.bad()){
//            ShaSumFile file(stream);
//            std::cout << "Loaded: " << file.getFullPath() << std::endl;
//            m_shaSumFileMap.emplace(std::make_pair(file.getSha(), std::move(file)));
//        }

//        stream.close();
//    } catch(...){
//        std::cout << "Failed to load data from cache file:" << m_cacheFile << std::endl;
//    }

    return true;
}

std::pair<const string &, const string &> ShaSumFileManager::splitPath(string path)
{
    int pos = path.find_last_of('/');
    std::string file = path.substr(pos + 1);
    std::string directory = path.substr(0, pos);

    std::cout << path.length() << " pos: " << pos << " directory:" << directory << " file:" << file <<  std::endl;
    return {*(m_directories.insert(directory).first), *(m_files.insert(file).first)};
}

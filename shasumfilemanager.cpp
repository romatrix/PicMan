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
    cacheFile.addVariable(section,"duplicate_count", std::to_string(duplicates.size()));

    for(int i = 0; i < duplicates.size(); ++i){
        cacheFile.addVariable(section, "file_name_duplicated" + std::to_string(i + 1), duplicates[i].getFileName());
        cacheFile.addVariable(section, "directory_name_duplicated" + std::to_string(i + 1), duplicates[i].getDirectoryName());
    }
}

bool ShaSumFileManager::loadCache()
{
    SettingsFile cacheFile(m_cacheFile);

    std::string fileName;
    std::string path;
    std::string sha;
    std::string creationDate;
    std::string duplicateCount;

    std::map<string, string> duplicatedFiles;
    std::map<string, string> duplicatedDirectories;
    std::string lastSection;
    const std::string duplicatedFileName = "file_name_duplicated";
    const int duplicatedFileNameLen = duplicatedFileName.length();
    const std::string duplicatedDirectoryName = "directory_name_duplicated";
    const int duplicatedDirectoryNameLen = duplicatedDirectoryName.length();

    //ShaSumFile shaFile(path, fileName, sha, creationDate);

    auto callback = [&,this](const std::string& section, const std::string& variable, const std::string& value){
        if(not variable.empty()){
            lastSection = section;

            if(variable == "file_name"){
                fileName = value;
            } else if(variable == "directory_name"){
                path = value;
            } else if( variable.find("file_name_duplicated") != std::string::npos){
                std::cout << "Found file_name_duplicated" << std::endl;
                duplicatedFiles[variable.substr(duplicatedFileNameLen)] = value;
            } else if(variable.find("directory_name_duplicated")!= std::string::npos){
                std::cout << "Found directory_name_duplicated" << std::endl;
                duplicatedDirectories[variable.substr(duplicatedDirectoryNameLen)] = value;
            }

            if(fileName != "" && path != ""){
                int pos = section.find('_');
                creationDate = section.substr(0, pos);
                sha = section.substr(pos + 1);
                std::pair<const string &, const string &> pathSplit = splitPath(path + "/" + fileName);
                m_shaSumFileMap.emplace(std::make_pair(section, ShaSumFile(pathSplit.first, pathSplit.second, sha, creationDate)));
                //m_shaSumFileMap[section] = std::move(ShaSumFile(pathSplit.first, pathSplit.second, sha, creationDate));

                fileName = "";
                path = "";
                creationDate = "";
                sha = "";
            }
        } else {
            auto shaFileIt = m_shaSumFileMap.find(lastSection);

            if(shaFileIt != m_shaSumFileMap.end() && duplicatedFiles.size()){
                std::cout << "Adding duplicates to lastSection, dup count:" << duplicatedFiles.size() << std::endl;

                for(auto i =0; i < duplicatedFiles.size(); ++i){
                    shaFileIt->second.addDuplicate(ShaSumFile(duplicatedDirectories[std::to_string(i)],
                                                              duplicatedFiles[std::to_string(i)],
                                                              sha,
                                                              creationDate));
                }

                duplicatedFiles.clear();
                duplicatedDirectories.clear();
            }
        }
    };
    cacheFile.load(callback);
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

    //std::cout << "directory:" << directory << " file:" << file <<  std::endl;
    return {*(m_directories.insert(directory).first), *(m_files.insert(file).first)};
}

#include "shasumfile.h"
#include <array>
#include <memory>
#include <string>
#include <iostream>
#include "systemcmd.h"

//ShaSumFile::ShaSumFile(ShaSumFile &&file):m_path(file.m_path),
//                                          m_fileName(file.m_fileName),
//                                          m_sha(file.m_sha),
//                                          m_creationDate(file.m_creationDate){
//}

//ShaSumFile &ShaSumFile::operator =(ShaSumFile &&file){
//    m_sha = file.m_sha;
//    m_creationDate = file.m_creationDate;
//    return *this;
//}

const std::string &ShaSumFile::getSha(){
    if(m_sha != ""){
        return m_sha;
    }

    std::stringstream ss = SystemCmd::execute("sha256sum \""+ m_path + "/" + m_fileName + "\"");

    m_sha = ss.str();

    if(m_sha.length()){
        m_sha.resize(m_sha.find_first_of(' '));
    }

    return m_sha;
}

const std::string &ShaSumFile::getCreationDate()
{
    if(m_creationDate != ""){
        return m_creationDate;
    }
    m_creationDate = SystemCmd::execute("exif -t DateTimeOriginal \"" + m_path + "/" + m_fileName + "\" | grep 'Value\\|^\\./'").str();

    if(m_creationDate.length()){
        m_creationDate = m_creationDate.substr(9, 19);
    }

    return m_creationDate;
}

const std::string &ShaSumFile::getFileName() const
{
    return m_fileName;
}

const std::string &ShaSumFile::getDirectoryName() const
{
    return m_path;
}

bool ShaSumFile::store(std::ofstream& stream) const
{
    stream << m_sha << "," << m_path << "," << m_fileName << std::endl;
    return true;
}

int ShaSumFile::addDuplicate(ShaSumFile&& duplicate)
{
    //std::cout << __FUNCTION__ << std::endl;
    m_duplicates.push_back(std::move(duplicate));
    return m_duplicates.size();
}

const std::vector<ShaSumFile>& ShaSumFile::getDuplicates() const
{
    return m_duplicates;
}


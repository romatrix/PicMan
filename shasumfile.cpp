#include "shasumfile.h"
#include <array>
#include <memory>
#include <string>
#include <iostream>
#include "systemcmd.h"

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
    m_duplicates.push_back(std::move(duplicate));
    return m_duplicates.size();
}

const std::vector<ShaSumFile>& ShaSumFile::getDuplicates() const
{
    return m_duplicates;
}


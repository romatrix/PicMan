#include "shasumfile.h"
#include <array>
#include <memory>
#include <string>
#include <iostream>
//ShaSumFile::ShaSumFile()
//{

//}
ShaSumFile::ShaSumFile(std::ifstream &stream)
{
    load(stream);
}

const std::string &ShaSumFile::getSha(){
    if(m_sha != ""){
        return m_sha;
    }

    std::array<char, 128> buffer;
    const std::string cmd = "sha256sum \"" + m_path + "/" + m_fileName + "\"";
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        m_sha += buffer.data();
    }

    if(m_sha.length()){
        m_sha.resize(m_sha.find_first_of(' '));
    }

    return m_sha;
}

bool ShaSumFile::store(std::ofstream& stream) const
{
    stream << m_sha << "," << m_path << "," << m_fileName << std::endl;
    return true;
}

void ShaSumFile::load(std::ifstream &stream)
{
    std::getline(stream, m_sha, ',');
    std::getline(stream, m_path, ',');
    std::getline(stream, m_fileName, ',');
}


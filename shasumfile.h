#ifndef SHASUMFILE_H
#define SHASUMFILE_H

#include <string>
#include <fstream>

class ShaSumFile
{
public:
    ShaSumFile(std::ifstream &stream);
    ShaSumFile(const std::string& path, const std::string& fileName): m_path(path), m_fileName(fileName){}
    ShaSumFile(const std::string& path, const std::string& fileName, const std::string sha): m_path(path), m_fileName(fileName), m_sha(sha){}
    const std::string& getSha();
    bool store(std::ofstream &stream) const;
    void load(std::ifstream &stream);
    std::string getFullPath()const { return "\"" + m_path + "/" + m_fileName + "\""; }
private:
    std::string m_path;
    std::string m_fileName;
    std::string m_sha;
};

#endif // SHASUMFILE_H

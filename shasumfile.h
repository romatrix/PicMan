#ifndef SHASUMFILE_H
#define SHASUMFILE_H

#include <string>
#include <fstream>

class ShaSumFile
{
public:
    ShaSumFile(const std::string& path, const std::string& fileName): m_path(path), m_fileName(fileName){}
    ShaSumFile(const std::string& path, const std::string& fileName, const std::string sha): m_path(path), m_fileName(fileName), m_sha(sha){}
    const std::string& getSha();
    bool store(std::ofstream &stream);
    static ShaSumFile load(std::ifstream &stream);
private:
    const std::string m_path;
    const std::string m_fileName;
    std::string m_sha;
};

#endif // SHASUMFILE_H

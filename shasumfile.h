#ifndef SHASUMFILE_H
#define SHASUMFILE_H

#include <string>
#include <fstream>
#include <vector>

class ShaSumFile
{
public:
    //ShaSumFile(ShaSumFile &&file);
    ShaSumFile(const std::string& path, const std::string& fileName): m_path(path), m_fileName(fileName){}
//    ShaSumFile(const std::string& path, const std::string& fileName, const std::string sha): m_path(path), m_fileName(fileName), m_sha(sha){}
    ShaSumFile(const std::string& path,
               const std::string& fileName,
               const std::string& sha,
               const std::string& creationDate):
                    m_path(path),
                    m_fileName(fileName),
                    m_sha(sha),
                    m_creationDate(creationDate){}
    //ShaSumFile &operator =(ShaSumFile &&file);

    const std::string& getSha();
    const std::string& getCreationDate();
    const std::string& getFileName() const;
    const std::string& getDirectoryName() const;


    bool store(std::ofstream &stream) const;
    void load(std::ifstream &stream);
    std::string getFullPath()const { return "\"" + m_path + "/" + m_fileName + "\""; }
    int addDuplicate(ShaSumFile&& duplicate);
    const std::vector<ShaSumFile> &getDuplicates() const;
private:
    const std::string& m_path;
    const std::string& m_fileName;
    std::string m_sha;
    std::string m_creationDate;
    std::vector<ShaSumFile> m_duplicates;
};

#endif // SHASUMFILE_H

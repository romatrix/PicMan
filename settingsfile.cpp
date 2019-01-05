#include "settingsfile.h"
#include <fstream>
#include <algorithm>
#include <iostream>

// code taken from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring =>
// trim from start (in place)
static inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
static inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

// trim from both ends (in place)
static inline void trim(std::string &s) {
    ltrim(s);
    rtrim(s);
}

// trim from start (copying)
static inline std::string ltrim_copy(std::string s) {
    ltrim(s);
    return s;
}

// trim from end (copying)
static inline std::string rtrim_copy(std::string s) {
    rtrim(s);
    return s;
}

// trim from both ends (copying)
static inline std::string trim_copy(std::string s) {
    trim(s);
    return s;
}

//code taken from https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring <=

SettingsFile::SettingsFile(std::string file): m_file(file)
{
    //load();
}

SettingsFile::~SettingsFile()
{
    //store();
}

void SettingsFile::addVariable(std::string sectionName, std::string variableName, std::string value)
{
    sections[sectionName][variableName].insert(value);
}

vector<string> SettingsFile::getVariable(string sectionName, string variableName) const
{
    vector<string> ret;
    try{
        for(const auto&val: sections.at(sectionName).at(variableName)){
            ret.push_back(val);
        }
    } catch(const out_of_range& exc)
    {
        cout << __FUNCTION__ << " section or variabel not found: secName:" << sectionName << " varName:" << variableName << endl;
    }

    return ret;
}


//void SettingsFile::parseLine(std::string line, std::string &section, std::pair<std::string, std::string>& entry )
//{
//    trim(line);
//    if(line[0] == '#'){
//        return;
//    }
//    if(line[0] == '[' && line[line.length() - 1] == ']'){
//        std::string sectionName = line.substr(1, line.length() - 2);
//        sections[sectionName]=SectionEntry
//    }

//}

void SettingsFile::load()
{
    std::ifstream stream;
    stream.exceptions(std::ifstream::failbit);

    std::string sectionName;

    try{

        stream.open(m_file);
        int lineNumber = 0;
        while(true){
            std::string line;
            std::getline(stream, line);
            ++lineNumber;

            trim(line);
            if(line[0] == '#'){
                continue;
            }

            if(!line.length()){
                continue;
            }

            if(line[0] == '[' && line[line.length() - 1] == ']'){
                sectionName = line.substr(1, line.length() - 2);
                std::cout << "Found section:" << sectionName << std::endl;
            } else {
                int pos = line.find_first_of('=');
                if(pos == std::string::npos){
                    std::cout << "Error during parsing line " << lineNumber << ":" << line << std::endl;
                    continue;
                }
                std::string varName = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                //sections[sectionName].insert({name,{name, value}});
                sections[sectionName][varName].insert(value);
                std::cout << "Adding var:" << varName << "=" << value << std::endl;
            }
            //std::getline(stream, m_path, ',');
            //std::getline(stream, m_fileName, ',');
        }
    }catch(...){

    }

    stream.close();
}

void SettingsFile::store()
{
    std::ofstream stream;
    stream.open(m_file);

    for(const auto &section:sections){
        const string& sectionName = section.first;
        cout << "Adding section:" << sectionName << endl;
        stream << '[' << sectionName << ']' << endl;

        for(const auto&var_pair:section.second){
            for(const auto&var: var_pair.second){
                const string& varName = var_pair.first;
                const string& value = var;
                cout << "Adding var:" << varName << "=" << value << endl;
                stream << varName << '=' << value << endl;
            }
            //const std::string& varName = var.first;
            //const std::string& value = var.second;
            //stream << varName << '=' << value << std::endl;
        }
    }

    stream.close();
}

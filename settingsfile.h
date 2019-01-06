#ifndef SETTINGSFILE_H
#define SETTINGSFILE_H

#include <string>
#include <unordered_map>
#include <map>
#include <vector>
#include <set>
#include <functional>

using namespace std;

class SettingsFile
{
public:
    using SectionEntry = multimap<string, string>;
    using VariableRange = pair<multimap<string,string>::const_iterator, multimap<string,string>::const_iterator>;
    SettingsFile(std::string file);
    ~SettingsFile();
    void addVariable(std::string section, std::string variable, std::string value);
    vector<string> getVariable(string sectionName, string variableName) const;
    const SectionEntry getSection(std::string section);
    void store();
    void load(std::function<void (const string &, const string &, const string &)> callback);
    private:
    //void parseLine(std::string line);
private:
    std::unordered_map<string, unordered_map<string, set<string>> > sections;
    std::string m_file;
};

#endif // SETTINGSFILE_H

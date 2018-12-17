#ifndef SYSTEMCMD_H
#define SYSTEMCMD_H

#include <string>
#include <vector>
#include <sstream>

class SystemCmd
{
public:
    SystemCmd();
    static std::stringstream execute(const std::string cmd);
};

#endif // SYSTEMCMD_H

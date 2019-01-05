#include "systemcmd.h"
#include <array>
#include <memory>

SystemCmd::SystemCmd()
{

}

std::stringstream SystemCmd::execute(const std::string cmd){
    std::array<char, 128> buffer;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd.c_str(), "r"), pclose);

    if (!pipe){
        throw std::runtime_error("popen() failed!");
    }

    std::stringstream ss;

    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
        ss << buffer.data();
    }

    return ss;
}

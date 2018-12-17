#include <iostream>
//#include <cstdio>
//#include <iostream>
//#include <memory>
//#include <stdexcept>
//#include <string>
//#include <array>
#include "shasumfile.h"
#include "shasumfilemanager.h"

//std::string exec(const char* cmd) {
//    std::array<char, 128> buffer;
//    std::string result;
//    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
//    if (!pipe) throw std::runtime_error("popen() failed!");
//    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr){
//        result += buffer.data();
//    }
//    return result;
//}

//class ShaSumFile{

//};

int main()
{
    ShaSumFileManager s("dupa.txt");
    s.scanDirectory("~");
    //std::cout << ShaSumFile("~/Pictures/", "DSC_2864.jpg").getSha() << "|" << std::endl;
    //std::cout << "Hello World! " << exec("sha256sum ~/Pictures/DSC_2864.jpg") << std::endl;
    return 0;
}

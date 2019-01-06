#include <iostream>
#include "shasumfile.h"
#include "shasumfilemanager.h"
#include "settingsfile.h"
#include "systemcmd.h"

#include <unordered_set>

void store(){
    ShaSumFileManager s("dupa.txt");
    s.scanDirectory("~/Pictures/2017");
    s.storeCache();
}

void load(){
    ShaSumFileManager s("dupa.txt");
    s.loadCache();
}


int main()
{
//    SettingsFile sf("settings.txt");

//    sf.addVariable("dupa", "var", "12345");
//    std::cout << "var:" << sf.getVariable("dupa1", "var").at(0) << std::endl;
    //std::stringstream ss = SystemCmd::execute("exif -t DateTimeOriginal ~/Pictures/2018/czerwiec/torun/DSC_5524.JPG | grep 'Value\\|^\\./'");
    //std::cout << ss.str() << std::endl;

    //ShaSumFileManager s("dupa.txt");
    //s.scanDirectory("~/Pictures/2017");
    //s.storeCache();
    load();

    //ShaSumFile s("~/Pictures", "DSC 2864.jpg");


    //std::cout << s.getSha() << "|" << s.getCreationDate() << " " << std::endl;
    //std::cout << "Hello World! " << exec("sha256sum ~/Pictures/DSC_2864.jpg") << std::endl;
    return 0;
}

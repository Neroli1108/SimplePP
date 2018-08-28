#include "SimplePP.h"
//Implement all functions in PerformanceProfiler header file

//Implementation of FileManager class
FileManager::FileManager(std::string src, std::string dst)
{
    srcFile = new std::fstream(src.c_str());
    dstFile = new std::ofstream(dst.c_str());
}
FileManager::FileManager()
{
    srcFile = NULL;
    dstFile = NULL;
}
FileManager::~FileManager()
{
    delete srcFile;
    delete dstFile;
    srcFile = NULL;
    dstFile = NULL;
    storeData.clear();
}

std::vector<Data> &FileManager::getStoreFiles()
{
    return this->storeData;
}
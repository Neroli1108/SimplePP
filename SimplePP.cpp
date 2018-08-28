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

std::fstream *FileManager::getSrcFile()
{
    return this->srcFile;
}

void FileManager::setSrcFile(std::string srcAddress)
{
    srcFile = new std::fstream(srcAddress.c_str());
}

std::vector<Data> &FileManager::getStoreFiles()
{
    return this->storeData;
}

void FileManager::recordSummaryData()
{
    *dstFile << "Stat Name"
             << "\t"
             << "Actual"
             << "\t"
             << std::endl;

    for (std::map<std::string, float>::iterator it = storeData.back().data.begin(); it != storeData.back().data.end(); it++)
    {
        *dstFile << it->first << "\t" << it->second << std::endl;
    }
}

//Implement the ConverterOperation class

void ConverterOperation::storeCSVData(std::fstream *srcfile, std::vector<Data> &storeFiles)
{
    Data fileData;
    std::string value;
    std::vector<std::string> temporaryStore;
    int firstLine = 1;
    std::string prevId, curId;
    while (srcfile->good())
    {
        if (firstLine)
        {
            std::getline(*srcfile, value);
            firstLine--;
        }
        else
        {
            int counter = 0;
            while (std::getline(*srcfile, value))
            {

                std::stringstream ss(value);
                std::string subvalue;

                while (std::getline(ss, subvalue, ','))
                {

                    if (counter == 0)
                    {
                        prevId = subvalue;
                    }
                    else if (counter % 3 == 0 && counter != 0)
                    {
                        curId = subvalue;
                        if (curId != prevId)
                        {
                            fileData.ID = std::atoi(temporaryStore[0].c_str());
                            for (int i = 1; i < temporaryStore.size(); i++)
                            {
                                fileData.data[temporaryStore[i]] = std::atof(temporaryStore[i + 1].c_str());
                                i++;
                            }
                            storeFiles.push_back(fileData);
                            temporaryStore.clear();
                            prevId = curId;
                        }
                    }

                    if (std::find(temporaryStore.begin(), temporaryStore.end(), subvalue) == temporaryStore.end())
                        temporaryStore.push_back(subvalue);

                    counter++;
                }
            }
        }
    }
}

void ConverterOperation::calculateSummaryData(std::vector<Data> &storeFiles)
{
    Data tmp = storeFiles[0];
    int size = storeFiles.size();
    for (int i = 1; i < storeFiles.size(); i++)
    {
        tmp += storeFiles[i];
    }
    for (std::map<std::string, float>::iterator it = tmp.data.begin(); it != tmp.data.end(); it++)
    {
        it->second = (it->second) / size;
    }
}

//implement the Converter function
Converter::Converter()
{
    this->fm = new FileManager();
    this->co = new ConverterOperation();
}
Converter::Converter(std::string src, std::string dst)
{
    this->srcAddress = src;
    this->dstAddress = dst;
    this->fm = new FileManager(this->srcAddress, this->dstAddress);
    this->co = new ConverterOperation();
}
Converter::~Converter()
{
    delete this->fm;
    delete this->co;
    this->fm = NULL;
    this->co = NULL;
}

FileManager *Converter::getFileManager()
{
    return this->fm;
}

void Converter::storeData()
{
    this->co->storeCSVData(this->fm->getSrcFile(), this->fm->getStoreFiles());
}

void Converter::writeSummary()
{
    this->storeData();
    this->co->calculateSummaryData(this->fm->getStoreFiles());
    this->fm->recordSummaryData();
}
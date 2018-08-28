#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>
#include <algorithm>
#include <map>
#include <iomanip>

typedef int FrameId;

//store data

struct Data
{
    FrameId ID;
    std::map<std::string, float> data;
    Data &operator=(Data a)
    {
        this->ID = a.ID;
        this->data = a.data;
        return *this;
    }

    Data &operator+=(Data a)
    {
        std::map<std::string, float>::iterator ait = a.data.begin();
        std::map<std::string, float>::iterator it = this->data.begin();
        while (it != this->data.end())
        {
            it->second += ait->second;
            it++;
            ait++;
        }
        return *this;
    }
};

class FileManager
{
  public:
    FileManager();
    ~FileManager();
    FileManager(std::string Sourceaddress, std::string DestAddress);
    std::vector<Data> &getStoreFiles();
    std::vector<Data> &getStoreSummaryData();
    void recordSummaryData();
    std::fstream *getSrcFile();
    void setSrcFile(std::string);

  private:
    std::vector<Data> storeData;
    std::fstream *srcFile;
    std::ostream *dstFile;
};

//Operate the CSV files
class ConverterOperation
{
  public:
    void storeCSVData(std::fstream *srcFile, std::vector<Data> &storeFiles);
    void calculateSummaryData(std::vector<Data> &storeFiles);
};

// main class
class Converter
{
  public:
    Converter();
    ~Converter();
    Converter(std::string src, std::string dst);
    void storeData();
    void writeSummary();
    FileManager *getFileManager();

  private:
    FileManager *fm;
    ConverterOperation *co;
    std::string srcAddress;
    std::string dstAddress;
};
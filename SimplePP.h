#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <ostream>
#include <ctime>
#include <algorithm>
#include <map>

typedef int FrameId;

//store data

struct Data
{
    FrameId ID;
    std::map<std::string, float> data;
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

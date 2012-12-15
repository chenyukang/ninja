#ifndef __LOADCONFIG_H__
#define __LOADCONFIG_H__

#include <string>
#include <vector>
using namespace std;

class LoadConfig {
public:
    LoadConfig()
        {
        }
    int Init_LoadConfig(std::string path);
    int Fresh_LoadConfig(std::string path);

private:
    int Load_files_iter(const char* path);
    int is_source_file(const char* file);
    int is_main_file(const char* file);
    int get_more_line(fstream& stream, string& res);
    int is_head_file(const char* file);
private:
    std::vector<std::string> files;
    std::string output;
    
};
    
    
#endif

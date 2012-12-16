#ifndef __LOADCONFIG_H__
#define __LOADCONFIG_H__

#include <string>
#include <vector>
using namespace std;
enum FileType {
    UNDEF = 1,
    HEADER,
    CSRC,
    CCSRC,
    CMAIN,
    CCMAIN
};

class SourceFile {
public:
    SourceFile(string path, FileType type): path(path), type(type)
        { }
    
    string path;
    FileType type;
};

class LoadConfig {
    
public:
    LoadConfig() {}
    int Init_LoadConfig(std::string path);
    int Fresh_LoadConfig(std::string path);

private:
    int Load_files_iter(const char* path);
    int Write_config_file();
    FileType Get_FileType(const char* name);
    int is_main_file(const char* file);
    int get_more_line(fstream& stream, string& res);
    int is_head_file(const char* file);
    string Get_obj_name(const string& name, string end);
    
private:
    std::vector<SourceFile> files;
    std::string output;
    
};

#endif

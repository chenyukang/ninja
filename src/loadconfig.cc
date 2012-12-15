#include "loadconfig.h"
#include "util.h"
#include <assert.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;

int LoadConfig::is_head_file(const char* file) {
    if(strstr(file, ".h") != 0 ||
       strstr(file, ".hh") != 0 ||
       strstr(file, ".hpp") != 0) {
        return 1;
    }
    return 0;
}

int LoadConfig::get_more_line(fstream& stream, string& res) {
    string line;
    size_t comment = 0;
    size_t begin = 0;
    size_t end = 0;
    size_t no  = string::npos;
    while((getline(stream, line)) != 0) {
        comment = line.find("//");
        begin   = line.find("/*");
        end     = line.find("*/");
        if(comment == no &&
           begin   == no &&
           end     == no) {
            res = line;
            return 1;
        }
        if(comment == 0)
            continue;
        if((comment != no && begin == no) ||
           (comment != no && comment < begin)) {
            res = line.substr(0, comment);
            return 1;
        }

        if(begin != no && end != no) {
            for(size_t k =0; k<line.size(); k++) {
                if(k >= begin && k <= end + 1) continue;
                else res += line[k];
            }
            return 1;
        } else if(begin != no && end == no) {
            res = line.substr(0, begin);
            while((getline(stream, line)) != 0) {
                if((end = line.find("*/")) != no) {
                    if(end + 2 < line.size()) 
                        res += line.substr(end+2, line.size() - end - 2);
                    break;
                }
            }
        }
    }
    return 0;
}

int LoadConfig::is_main_file(const char* file) {
    assert(file && strlen(file) != 0);
    if(is_head_file(file))
        return 0;
    fstream stream(file);
    string line;
    string str;
    while(get_more_line(stream, line)) {
        if(Have_main_func(line)) {
            return 1;
        }
    }
    return 0;
}

int LoadConfig::is_source_file(const char* name) {
    const char* extensions[] = {".h", ".c", ".hh", ".cc",
                                ".cpp", ".hpp", NULL};
    int k = 0;
    const char* p;
    for(k=0; p = extensions[k] , p != NULL; k++) {
        char* pos = strstr(name, p);
        if(pos != 0 && strlen(pos) == strlen(p)) {
            return 1;
        }
    }
    return 0;
}

int LoadConfig::Load_files_iter(const char* path) {
    assert(path && strlen(path) != 0) ;
    struct dirent* ent = 0;
    DIR* pdir = opendir(path);
    struct stat stat_buf;
    if(pdir == 0) {
        perror("Failed to open dir in loadconfig_init!");
        return 1;
    }

    while((ent = readdir(pdir)) != 0) {
        char all_path[512];
        memset(all_path, 0, sizeof(all_path));
        snprintf(all_path, 512, "%s/%s", path, ent->d_name);
        lstat(all_path, &stat_buf);
        if(S_ISDIR(stat_buf.st_mode)) {
            if(strcmp(ent->d_name, ".") == 0 ||
               strcmp(ent->d_name, "..") == 0 ) {
                continue;
            } else {
                Load_files_iter(all_path);
            }
        }
        else {
            if(is_source_file(ent->d_name)) {
                std::string err;
                string res(all_path);
                CanonicalizePath(&res, &err);
                files.push_back(res);
            }
        }
    }
    closedir(pdir);
    return 0;
}

int LoadConfig::Init_LoadConfig(std::string path) {
    Load_files_iter(path.c_str());
    for(vector<string>::iterator iter = files.begin();
        iter != files.end(); ++iter) {
        if(is_main_file(iter->c_str())) {
            printf("yes main source: %s\n", iter->c_str());
        }
    }
    
    return 0;
}

int LoadConfig::Fresh_LoadConfig(std::string path) {
    return 0;
}

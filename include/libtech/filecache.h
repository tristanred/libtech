#pragma once

#include "libtech.h"

#include <cstdint>
#include <list>

using namespace std;

// The entry owns the file_name but not 'contents'. The content must be managed by the caller.
class FileCache_Entry
{
public:
    char* file_name;

    uint8_t* contents;
    size_t length;
};

class LIBTECH_CLASS FileCache
{
public:
    FileCache(bool writeThrough = false);
    ~FileCache();
    
    uint8_t* ReadFileContents(const char* filepath, size_t*  length);
    void WriteFileContents(const char* filepath, size_t length, uint8_t* content);
    void RemoveFromCache(const char* filepath);
    void ClearCache();

private:
    std::list<FileCache_Entry*>* cache_entries;

    bool update_filesystem;

    FileCache_Entry* findFileInCache(const char* filename);

};
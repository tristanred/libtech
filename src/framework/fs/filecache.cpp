#include "libtech/filecache.h"

#include <string>
#include "libtech/binreader.h"

FileCache::FileCache(bool writeThrough)
{
    cache_entries = new std::list<FileCache_Entry *>();
    update_filesystem = writeThrough;
}

FileCache::~FileCache()
{
    auto begin = cache_entries->begin();
    auto end = cache_entries->end();
    while(begin != end)
    {
        FileCache_Entry* entry = *begin;
        //delete(entry->file_name); // Leaking. TODO
        delete(*begin);

        begin++;
    }

    cache_entries->clear();
}

uint8_t* FileCache::ReadFileContents(char* filepath, size_t* length)
{
    FileCache_Entry* found = findFileInCache(filepath);

    // If the file is found in the cache, return it.
    if(found)
    {
        *length = found->length;
        return found->contents;
    }

    // If not in the cache, read it from disk.
    size_t size = 0;
    uint8_t* content = (uint8_t*)getfilebytes(filepath, &size);

    if(size == 0)
    {
        *length = 0;
        return NULL;
    }

    // If the read was successful, enter it in the cache and return the contents.
    FileCache_Entry* created = new FileCache_Entry();
    created->file_name = new char[strlen(filepath)];
    strcpy(created->file_name, filepath);
    created->length = size;
    created->contents = content;
    
    cache_entries->push_back(created);

    *length = size;
    return content;
}

void FileCache::WriteFileContents(char* filepath, size_t length, uint8_t* content)
{
    FileCache_Entry* found = findFileInCache(filepath);

    if(found)
    {
        found->contents = content;
        found->length = length;
    }
    else
    {
        FileCache_Entry* created = new FileCache_Entry();
        created->file_name = new char[strlen(filepath)];
        strcpy(created->file_name, filepath);
        created->contents = content;
        created->length = length;

        cache_entries->push_back(created);
    }

    if(this->update_filesystem)
    {
        // TODO
    }
}

void FileCache::RemoveFromCache(char* filepath)
{
    auto begin = cache_entries->begin();
    auto end = cache_entries->end();
    while(begin != end)
    {
        FileCache_Entry* entry = *begin;

        if(strcmp(entry->file_name, filepath) == 0)
        {
            cache_entries->remove(entry);
            return;
        }

        begin++;
    }
}

void FileCache::ClearCache()
{
    auto begin = cache_entries->begin();
    auto end = cache_entries->end();
    while(begin != end)
    {
        FileCache_Entry* entry = *begin;

        delete(entry->file_name);
        delete(entry);

        begin++;
    }

    cache_entries->clear();
}

FileCache_Entry* FileCache::findFileInCache(char* filename)
{
    auto begin = cache_entries->begin();
    auto end = cache_entries->end();
    while(begin != end)
    {
        FileCache_Entry* entry = *begin;

        if(strcmp(entry->file_name, filename) == 0)
        {
            return entry;
        }

        begin++;
    }

    return NULL;
}

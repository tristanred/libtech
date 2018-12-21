#include "libtech/pathutils.h"

#include <string>
#include <string.h>

char* get_file_name(const char* path)
{
    const char* ret = strrchr(path, '/');

    size_t substrlen = strlen(ret) + 1;

    char* namestr = new char[substrlen];
    strcpy(namestr, ret + 1);

    return namestr;
}

char* get_file_name_noext(const char* path)
{
    const char* extPtr = strrchr(path, '.') + 1;
    const char* lastSlash = strrchr(path, '/') + 1;

    size_t substrlen = extPtr - lastSlash - 1;

    char* namestr = new char[substrlen];
    namestr[substrlen] = '\0';
    strncpy(namestr, lastSlash, substrlen);

    return namestr;
}

char* get_file_extension(const char* path)
{
    const char* extPtr = strrchr(path, '.');

    size_t extlen = strlen(extPtr) + 1;

    char* extstr = new char[extlen];
    strcpy(extstr, extPtr);

    return extstr;
}

char* get_parent_directory_path(const char* path)
{
    const char* substr = strrchr(path, '/');
    size_t substrlen = substr - path;

    char* parentstr = new char[substrlen];
    parentstr[substrlen] = '\0';
    strncpy(parentstr, path, substrlen);

    return parentstr;
}

std::list<char*>* get_path_parts(const char* path)
{
    char* pathCopy = new char[strlen(path) + 1];
    strcpy(pathCopy, path);

    std::list<char*>* parts = new std::list<char*>();

    char* token = strtok(pathCopy, "/");
    while(token)
    {
        char* partstr = new char[strlen(token) + 1];
        strcpy(partstr, token);

        parts->push_back(partstr);
        token = strtok(NULL, "/");
    }

    delete[] pathCopy;
    return parts;
}

void sanitize_path_slashes(const char* original, char* sanitized)
{
#ifdef _WIN32
    int len = strlen(original);

    for(int i = 0; i < len; i++)
    {
        if(original[i] == '/')
        {
            sanitized[i] = '\\';
        }
        else
        {
            sanitized[i] = original[i];
        }
    }

#elif linux
    int len = strlen(original);

    for(int i = 0; i < len; i++)
    {
        if(original[i] == '\\')
        {
            sanitized[i] = '/';
        }
        else
        {
            sanitized[i] = original[i];
        }
    }

#endif
}

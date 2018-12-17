#include "libtech/fsutils.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

#include "libtech/linkedlist.h"

#ifdef _WIN32

#include <Windows.h>
#include "libtech/sysutils.h"

#endif

char** get_lines_of_file(const char* filePath, int* count)
{
    LinkedList<char*>* lines = new LinkedList<char*>();

    std::string fileName = filePath;

    std::ifstream reader(fileName, std::ios::binary);

    while(reader.eof() == false)
    {
        char lineResult[1024];
        reader.getline(lineResult, 1024, '\n');

        unsigned int readSize = (unsigned int)reader.gcount();

        char* lineBytes = new char[readSize];
        std::strncpy(lineBytes, lineResult, readSize);

        lines->Add(lineBytes);
    }

    reader.close();

    *count = lines->Size();
    return lines->GetLinear();
}

char* read_characters(const char * filePath, size_t * length)
{
    std::ifstream reader(filePath, std::ios::binary | std::ios::ate);

    unsigned int size = (unsigned int)reader.tellg();
    
    char* contents = new char[size];
    reader.seekg(0);
    reader.read(contents, size);

    *length = size;
    return contents;
}

void write_characters(const char* filePath, char* data, size_t length)
{
    std::ofstream writer(filePath);

    writer.write(data, length);
    
    writer.flush();
}

void get_directory_files(const char* folderPath, bool recursive, ArrayList<char*>* aggregate)
{
#ifdef _WIN32
    WIN32_FIND_DATAA ffd;

    ArrayList<char*>* files = aggregate;
    if(files == NULL)
    {
        files = new ArrayList<char*>();
    }
    
    std::string directorySearchAlias = std::string(folderPath);
    directorySearchAlias.append("\\*");
    
    HANDLE hFind = FindFirstFileA(directorySearchAlias.c_str(), &ffd);
    
    if(hFind == INVALID_HANDLE_VALUE)
    {
        DWORD err = GetLastError();
        return;
    }
    
    do
    {
        if(IsDotFile(ffd))
            continue;
        
        bool isDirectory = ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY;
        
        if(isDirectory && recursive)
        {
            std::string subDirectoryPath;
            subDirectoryPath.append(folderPath);
            subDirectoryPath.append("\\");
            subDirectoryPath.append(ffd.cFileName);
            
            get_directory_files(subDirectoryPath.c_str(), recursive, aggregate);
        }
        else
        {
            char* filePath = new char[MAX_PATH];
            sprintf(filePath, "%s\\%s", folderPath, ffd.cFileName);
            
            aggregate->Add(filePath);
        }
        
    } while(FindNextFileA(hFind, &ffd) != 0);
    
    FindClose(hFind);
#endif
}

char* find_subdir_file(const char* fileName, const char* folder)
{
    ArrayList<char*> filesList;
    get_directory_files(folder, true, &filesList);
    
    for(uint64_t i = 0; i < filesList.Count(); i++)
    {
        char* element = filesList.Get(i);
        
        if(strstr(element, fileName) != NULL)
        {
            return element;
        }
    }
    
    return NULL;
}
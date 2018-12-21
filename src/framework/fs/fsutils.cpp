#include "libtech/fsutils.h"

#include <iostream>
#include <fstream>
#include <cstring>
#include <list>

#include "libtech/linkedlist.h"
#include "libtech/filelogger.h"
#include "libtech/sysutils.h"

#ifdef _WIN32

#include <Windows.h>
#include "libtech/sysutils.h"

#elif linux

#include <sys/types.h>
#include <dirent.h>

#elif __APPLE__

#include <sys/types.h>
#include <dirent.h>

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
#elif linux

    DIR *dp;
    struct dirent *ep;

    dp = opendir(folderPath);
    if (dp != NULL)
    {
        while (ep = readdir(dp))
        {
            if(is_dot_file(ep->d_name))
                continue;
            
            if(ep->d_type == DT_DIR)
            {
                // Is directory
                std::string subDirectoryPath;
                subDirectoryPath.append(folderPath);
                subDirectoryPath.append("\\");
                subDirectoryPath.append(ep->d_name);
                
                get_directory_files(subDirectoryPath.c_str(), recursive, aggregate);
            }
            else if(ep->d_type == DT_REG)
            {
                char* filePath = new char[256];
                sprintf(filePath, "%s\\%s", folderPath, ep->d_name);

                // Is file
                aggregate->Add(filePath);
            }
            else
            {
                // File type not regocnized
            }
        }

        closedir (dp);
    }
    else
    {
        LogError("Couldn't open the directory");
    }
#elif __APPLE__
    struct dirent** namelist;
    int n = scandir(folderPath, &namelist, 0, alphasort);
    if (n < 0)
    {
        perror("scandir");
    }
    else
    {
        for (int i = 0; i < n; i++)
        {
            if(is_dot_file(namelist[i]->d_name))
                continue;
            
            if(namelist[i]->d_type == DT_DIR)
            {
                std::string subDirectoryPath;
                subDirectoryPath.append(folderPath);
                subDirectoryPath.append("\\");
                subDirectoryPath.append(namelist[i]->d_name);

                get_directory_files(subDirectoryPath.c_str(), recursive, aggregate);
            }
            else if(namelist[i]->d_type == DT_REG)
            {
                char* filePath = new char[256];
                sprintf(filePath, "%s/%s", folderPath, namelist[i]->d_name);

                aggregate->Add(filePath);
            }
            else
            {
                // File type not regocnized
            }
            
            free(namelist[i]);
            printf("%s\n", namelist[i]->d_name);
            
        }
    }
    
    free(namelist);
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

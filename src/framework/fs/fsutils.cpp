#include "libtech/fsutils.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include "libtech/linkedlist.h"


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

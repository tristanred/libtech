#include "libtech/fsutils.h"

#include <iostream>
#include <fstream>
#include <cstring>

#include "libtech/linkedlist.h"


char** get_lines_of_file(char* filePath, int* count)
{
    LinkedList<char*>* lines = new LinkedList<char*>();

    std::string fileName = filePath;

    std::ifstream reader(fileName, std::ios::binary);

    while(reader.eof() == false)
    {
        char lineResult[1024];
        reader.getline(lineResult, 1024, '\n');

        int readSize = reader.gcount();

        char* lineBytes = new char[readSize];
        std::strncpy(lineBytes, lineResult, reader.gcount());

        lines->Add(lineBytes);
    }

    reader.close();

    *count = lines->Size();
    return lines->GetLinear();
}

LIBTECH_API char* read_characters(char * filePath, size_t * length)
{
    std::ifstream reader(filePath, std::ios::binary | std::ios::ate);

    auto size = reader.tellg();
    
    char* contents = new char[size];
    reader.seekg(0);
    reader.read(contents, size);

    *length = size;
    return contents;
}

void write_characters(char* filePath, char* data, size_t length)
{
    std::ofstream writer(filePath);

    writer.write(data, length);
    
    writer.flush();
}

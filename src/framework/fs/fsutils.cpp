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
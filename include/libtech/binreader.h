#pragma once

#include <stdio.h>
#include <stdint.h>

#include "libtech.h"

class LIBTECH_API binreader
{
public:
    binreader();
    explicit binreader(char* filepath);
    ~binreader();

    void Open(char* filepath);
    void Close();

    char* ReadBytes();

    size_t GetSize();

private:
    char* loadedPath;
    FILE* fp;
};



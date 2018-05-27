#pragma once

#include <stdio.h>
#include <stdint.h>

#include "libtech.h"

class LIBTECH_CLASS binreader
{
public:
    binreader();
    explicit binreader(const char* filepath);
    ~binreader();

    void Open(const char* filepath);
    void Close();

    char* ReadBytes();

    size_t GetSize();

private:
    char* loadedPath;
    FILE* fp;
};

LIBTECH_API char* getfilebytes(const char* filepath, size_t* length);

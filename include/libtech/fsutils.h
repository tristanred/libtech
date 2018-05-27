#pragma once

#include "libtech.h"

#include <cstdint>
using namespace std;

LIBTECH_API char** get_lines_of_file(const char* filePath, int* count);

LIBTECH_API char* read_characters(const char* filePath, size_t* length);

LIBTECH_API void write_characters(const char* filePath, char* data, size_t length);
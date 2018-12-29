#pragma once

#include "libtech.h"
#include "arraylist.h"

#include <stdint.h>

LIBTECH_API char** get_lines_of_file(const char* filePath, int* count);

LIBTECH_API char* read_characters(const char* filePath, size_t* length);

LIBTECH_API void write_characters(const char* filePath, char* data, size_t length);

LIBTECH_API void get_directory_files(const char* filePath, bool recursive, ArrayList<char*>* aggregate);

LIBTECH_API char* find_subdir_file(const char* fileName, const char* folder);

LIBTECH_API bool path_is_directory(const char* path);
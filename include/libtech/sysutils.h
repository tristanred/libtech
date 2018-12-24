#pragma once

#include "libtech.h"

LIBTECH_API char* get_working_directory();

LIBTECH_API bool is_dot_file(char* dirName);

#ifdef _WIN32

#include "Windows.h"

LIBTECH_API void print_last_win32_error();
LIBTECH_API void print_win32_error(DWORD errorCode);
LIBTECH_API char* get_win32_error_text(DWORD errorCode);
LIBTECH_API bool IsDotFile(WIN32_FIND_DATAA dir);

#endif

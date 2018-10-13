#pragma once

#include "libtech.h"

LIBTECH_API char* get_working_directory();

#ifdef WIN32

#include "Windows.h"

LIBTECH_API void print_last_win32_error();
LIBTECH_API void print_win32_error(DWORD errorCode);
LIBTECH_API char* get_win32_error_text(DWORD errorCode);

#endif
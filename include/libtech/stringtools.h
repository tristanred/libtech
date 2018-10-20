#pragma once

#include "libtech.h"

/**
 * Turns a line of text into a list of ints. The text must be in the format
 * "1 2 3 4 66 80 120 34"
 * Each number must be separated by one or multiple whitespace char
 * Supported whitespaces are : spaces, tabs, newlines
 */
LIBTECH_API int* convert_string_to_int_list(const char* line, long int* count);
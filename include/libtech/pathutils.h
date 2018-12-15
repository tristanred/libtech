#pragma once

#include <list>

#include "libtech.h"

/**
 * Get the name part of a path containing the extension.
 */
LIBTECH_API char* get_file_name(const char* path);

/**
 * Get the name part of a path without the extension part.
 */
LIBTECH_API char* get_file_name_noext(const char* path);

/**
 * Get the extension part in a path containing the '.' .
 */
LIBTECH_API char* get_file_extension(const char* path);

/**
 * Get the path to the parent directory.
 */
LIBTECH_API char* get_parent_directory_path(const char* path);

/**
 * Get each folder part of the path structure.
 * Everything in between the slashes is put into the list.
 */
LIBTECH_API std::list<char*>* get_path_parts(const char* path);

/**
 * Replace backslashes with forward slashes.
 */
LIBTECH_API void replace_path_slashes(char* path);
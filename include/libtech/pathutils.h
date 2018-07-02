#pragma once

#include <list>

/**
 * Get the name part of a path containing the extension.
 */
char* get_file_name(const char* path);

/**
 * Get the name part of a path without the extension part.
 */
char* get_file_name_noext(const char* path);

/**
 * Get the extension part in a path containing the '.' .
 */
char* get_file_extension(const char* path);

/**
 * Get the path to the parent directory.
 */
char* get_parent_directory_path(const char* path);

/**
 * Get each folder part of the path structure.
 * Everything in between the slashes is put into the list.
 */
std::list<char*>* get_path_parts(const char* path);

/**
 * Replace backslashes with forward slashes.
 */
void  replace_path_slashes(char* path);
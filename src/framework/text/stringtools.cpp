#include "libtech/stringtools.h"

#include <string>
#include <string.h>
#include <ctype.h>
#include "libtech/arraylist.h"

LIBTECH_API int* convert_string_to_int_list(const char* line, long int* count)
{
    ArrayList<int> number_list;

    size_t stringLength = strlen(line);

    size_t currentIndex = 0;

    int numberReadingIndex = 0;
    char numberReading[256];
    memset(numberReading, 0, 256);
    while(currentIndex < stringLength)
    {
        char c = line[currentIndex];
        int num_check = isdigit(c);

        if(num_check != 0)
        {
            // Start or continue reading a number
            numberReading[numberReadingIndex] = c;
            numberReadingIndex++;
        }
        else
        {
            // Stop reading the number
            if(numberReadingIndex > 0)
            {
                int read_num = atoi(numberReading);
                number_list.Add(read_num);
                memset(numberReading, 0, 256);
            }

            numberReadingIndex = 0;
        }

        currentIndex++;
    }
    if (numberReadingIndex > 0)
    {
        int read_num = atoi(numberReading);
        number_list.Add(read_num);
    }

    *count = (long)number_list.Count();
    return number_list.GetListData();
}

LIBTECH_API char** string_split(const char* source, const char* delim, int* result_count)
{
    // Basic helper function around strtok for strings.
    // Might leak a bunch of memory with the copies but this
    // should work for now.

    char* sourceScratcher = new char[strlen(source)];
    strcpy(sourceScratcher, source);

    ArrayList<char*> splitParts;

    char* token = strtok(sourceScratcher, delim);
    while(token)
    {
        char* tokenCopy = new char[strlen(token)];
        strcpy(tokenCopy, token);
        splitParts.Add(tokenCopy);

        token = strtok(NULL, delim);

    }

    *result_count = splitParts.Count();
    char** res = splitParts.GetListData();

    return res;
}

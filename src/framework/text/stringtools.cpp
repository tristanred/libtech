#include "libtech/stringtools.h"

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
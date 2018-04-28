#include <cstring>
#include <errno.h>
#include "libtech/binreader.h"

binreader::binreader()
{
    fp = NULL;
    loadedPath = NULL;
}

binreader::binreader(char *filepath) : binreader()
{
    this->Open(filepath);
}

binreader::~binreader()
{
    this->Close();
}

void binreader::Open(char *filepath)
{
    if(loadedPath != NULL && strcmp(loadedPath, filepath) == 0)
        return;

    errno = 0;
    FILE* newfile = fopen(filepath, "rb");

    int err = errno;

    if(newfile != NULL)
    {
        this->Close();

        fp = newfile;

        loadedPath = new char[strlen(filepath)];
        strcpy(loadedPath, filepath);
    }
}

void binreader::Close()
{
    if(fp != NULL)
    {
        fclose(fp);
        fp = NULL;
    }

    if(loadedPath != NULL)
    {
        delete(loadedPath);
    }
}

char *binreader::ReadBytes()
{
    char* output = new char[GetSize()];

    if(fp != NULL)
    {
        int offset = 0;
        int c;
        while((c = fgetc(fp)) != EOF)
        {
            output[offset] = (char)c;
            offset++;
        }
    }

    return output;
}

size_t binreader::GetSize()
{
    if(fp != NULL)
    {
        fseek(fp, 0, SEEK_SET);

        long size = ftell(fp);

        return (size_t)size;
    }

    return 0;
}


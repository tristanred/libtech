#include <cstring>
#include <errno.h>
#include "libtech/binreader.h"

binreader::binreader()
{
    fp = NULL;
    loadedPath = NULL;
}

binreader::binreader(const char *filepath) : binreader()
{
    this->Open(filepath);
}

binreader::~binreader()
{
    this->Close();
}

void binreader::Open(const char *filepath)
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
        char* returned = strcpy(loadedPath, filepath);
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
        // Not able to delete, flagged as heap corruption. TODO
        //delete(loadedPath); // Currently leaking.
    }
}

char *binreader::ReadBytes()
{
    if(fp != NULL)
    {
        char* output = new char[GetSize()];

        int offset = 0;
        int c;
        while((c = fgetc(fp)) != EOF)
        {
            output[offset] = (char)c;
            offset++;
        }

        return output;
    }

    return NULL;
}

size_t binreader::GetSize()
{
    if(fp != NULL)
    {
        long curpos = ftell(fp);

        fseek(fp, 0, SEEK_END);

        long size = ftell(fp);

        fseek(fp, curpos, SEEK_SET);

        return (size_t)size;
    }

    return 0;
}

LIBTECH_API char* getfilebytes(char* filepath, size_t* length)
{
    binreader reader(filepath);

    if(reader.GetSize() > 0)
    {
        char* buf = reader.ReadBytes();

        *length = reader.GetSize();
        return buf;

    }
    else
    {
        *length = 0;
        return NULL;
    }
}
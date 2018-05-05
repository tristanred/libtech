#include "libtech/shaderloader.h"
#include <libtech/binreader.h>

ShaderLoader::ShaderLoader()
{
}

ShaderLoader::~ShaderLoader()
{
}

char *ShaderLoader::LoadShader(char *path)
{
    char* contents = NULL;

    binreader reader;
    reader.Open(path);

    contents = reader.ReadBytes();

    return contents;
}

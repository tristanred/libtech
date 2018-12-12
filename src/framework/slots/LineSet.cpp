#include "libtech/slots/LineSet.h"

#include <stdlib.h>

#include <libtech/stringtools.h>

#define PUGIXML_HEADER_ONLY
#include "pugixml.hpp"

LineSet::LineSet()
{
    this->PatternsCount = 0;
    this->LinePatterns = NULL;
}

LineSet::LineSet(int** linePatterns, int patternCount)
{
    this->LinePatterns = linePatterns;
    this->PatternsCount = patternCount;
}

LineSet::~LineSet()
{
    for (int i = 0; i < this->PatternsCount; i++)
    {
        delete[] this->LinePatterns[i];
    }

    delete[] this->LinePatterns;
}

LineSet* LineSet::CreateLinesetFromConfig(const char* configPath)
{
    pugi::xml_document doc;
    pugi::xml_parse_result result = doc.load_file(configPath);
    if(!result)
    {
        // File not found
        return NULL;
    }

    pugi::xpath_node_set lineNodes = doc.select_nodes("/linesetConfig/lineset[@id='0']/line");

    LineSet* newSet = new LineSet();
    newSet->PatternsCount = lineNodes.size();
    newSet->LinePatterns = new int*[newSet->PatternsCount];

    for(pugi::xpath_node node: lineNodes)
    {
        pugi::xml_node lineNode = node.node();

        int lineIndex = lineNode.attribute("id").as_int();

        const char* lineData = lineNode.text().as_string();
        long int count = 0;
        newSet->LinePatterns[lineIndex] = convert_string_to_int_list(lineData, &count);
    }

    return newSet;
}

LineSet* LineSet::Generate10Lines()
{
    LineSet* newSet = new LineSet();
    newSet->PatternsCount = 10;

    newSet->LinePatterns = new int*[10];

    for (int i = 0; i < newSet->PatternsCount; i++)
    {
        newSet->LinePatterns[i] = new int[5];
    }

    // Line 1
    newSet->LinePatterns[0][0] = 1;
    newSet->LinePatterns[0][1] = 1;
    newSet->LinePatterns[0][2] = 1;
    newSet->LinePatterns[0][3] = 1;
    newSet->LinePatterns[0][4] = 1;

    // Line 2
    newSet->LinePatterns[1][0] = 0;
    newSet->LinePatterns[1][1] = 0;
    newSet->LinePatterns[1][2] = 0;
    newSet->LinePatterns[1][3] = 0;
    newSet->LinePatterns[1][4] = 0;

    // Line 3
    newSet->LinePatterns[2][0] = 2;
    newSet->LinePatterns[2][1] = 2;
    newSet->LinePatterns[2][2] = 2;
    newSet->LinePatterns[2][3] = 2;
    newSet->LinePatterns[2][4] = 2;

    // Line 4
    newSet->LinePatterns[3][0] = 0;
    newSet->LinePatterns[3][1] = 1;
    newSet->LinePatterns[3][2] = 2;
    newSet->LinePatterns[3][3] = 2;
    newSet->LinePatterns[3][4] = 2;

    // Line 5
    newSet->LinePatterns[4][0] = 2;
    newSet->LinePatterns[4][1] = 1;
    newSet->LinePatterns[4][2] = 0;
    newSet->LinePatterns[4][3] = 0;
    newSet->LinePatterns[4][4] = 0;

    // Line 6
    newSet->LinePatterns[5][0] = 0;
    newSet->LinePatterns[5][1] = 1;
    newSet->LinePatterns[5][2] = 2;
    newSet->LinePatterns[5][3] = 1;
    newSet->LinePatterns[5][4] = 0;

    // Line 7
    newSet->LinePatterns[6][0] = 2;
    newSet->LinePatterns[6][1] = 1;
    newSet->LinePatterns[6][2] = 0;
    newSet->LinePatterns[6][3] = 1;
    newSet->LinePatterns[6][4] = 2;

    // Line 8
    newSet->LinePatterns[7][0] = 0;
    newSet->LinePatterns[7][1] = 0;
    newSet->LinePatterns[7][2] = 1;
    newSet->LinePatterns[7][3] = 2;
    newSet->LinePatterns[7][4] = 2;

    // Line 9
    newSet->LinePatterns[8][0] = 2;
    newSet->LinePatterns[8][1] = 2;
    newSet->LinePatterns[8][2] = 1;
    newSet->LinePatterns[8][3] = 0;
    newSet->LinePatterns[8][4] = 0;

    // Line 10
    newSet->LinePatterns[9][0] = 1;
    newSet->LinePatterns[9][1] = 0;
    newSet->LinePatterns[9][2] = 0;
    newSet->LinePatterns[9][3] = 0;
    newSet->LinePatterns[9][4] = 0;

    return newSet;
}

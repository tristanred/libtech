#pragma once

#include "libtech.h"

#define DELETE_LIST_ELEMENTS(lst, T) \
    auto begin = lst->begin();       \
    auto end = lst->end();           \
    while(begin != end)              \
    {                                \
        T* obj = *begin;             \
        delete(obj);                 \
        begin++;                     \
    }                                \
    lst->clear();

#define DELETE_XDIM_ARRAY(lst, dim) \
    for(int i = 0; i < dim; i++)    \
    {                               \
        delete(lst[i]);             \
    }                               \
    delete(lst);
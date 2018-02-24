#pragma once

#include "libtech.h"
#include "collections/linkedlist.h"

template<class T>
class LIST_NODE
{
public:
    T data;
    LIST_NODE* next;

    LIST_NODE()
    {
        data = NULL;
        next = NULL;
    }

    ~LIST_NODE()
    {

    }
};

template<class T>
class LinkedList
{
public:
    LinkedList()
    {
        _first = NULL;
    }

    ~LinkedList()
    {

    }

    unsigned int Size()
    {
        if (_first == NULL)
            return 0;

        unsigned int count = 0;
        LIST_NODE<T>* next = _first;
        while (next != NULL)
        {
            count++;

            next = next->next;
        }

        return count;
    }

    void Add(T element)
    {
        LIST_NODE<T>* next = _first;
        while (next != NULL)
        {
            if (next->next == NULL)
            {
                LIST_NODE<T>* newNode = new LIST_NODE<T>();
                newNode->data = element;
                newNode->next = NULL;

                next->next = newNode;

                return;
            }

            next = next->next;
        }
    }

    void Remove(unsigned int index)
    {
        if(_first == NULL)
            return;

        unsigned int count = 0;
        LIST_NODE<T>* previous = NULL;
        LIST_NODE<T>* current = _first;

        while(count < index)
        {
            previous = current;
            current = current->next;

            count++;

            if(current == NULL)
                return; // Index bigger than size
        }

        T nextItem = current->next;

        previous->next = nextItem;
    }

    void Remove(T element)
    {

    }

    T Get(unsigned int index)
    {
        if (_first == NULL)
            return NULL;

        unsigned int count = 0;
        LIST_NODE<T>* next = _first;
        while (next != NULL)
        {
            if (count == index)
            {
                return next->data;
            }

            count++;

            next = next->next;
        }
    }

    T* GetLinear()
    {
        if(_first == NULL)
            return NULL;

        T* list = new T[this->Size()];

        int index = 0;
        LIST_NODE<T>* next = _first;
        while(next != NULL)
        {
            list[index] = next->data;

            next = next->next;
        }

        return list;
    }
private:
    LIST_NODE<T>* _first;
};
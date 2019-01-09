#pragma once

#include <queue>
#include <list>
#include <functional>

template <class T>
class Queue
{
public:
    Queue()
    {
        this->_container = new std::list<T>();
        
    };
    
    ~Queue()
    {
        this->_container->clear();
        delete(this->_container);
    };
    
    void Push(T item)
    {
        _container->push_front(item);
    };
    
    T Pop()
    {
        T item = _container->front();
        _container->pop_front();
        
        return item;
    };
    
    T Front()
    {
        T item = _container->front();
        
        return item;
    };
    
    T Get(uint64_t index)
    {
        auto begin = _container->begin();
        auto end = _container->end();
        int iterIndex = 0;
        while (begin != end)
        {
            T obj = *begin;

            if (iterIndex == index)
                return obj;

            begin++;
        }
        
        return NULL;
    };
    
private:
    //std::queue<T>* _container;
    std::list<T>* _container;
};
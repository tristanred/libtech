#pragma once

#include <functional>
#include <list>
#include <queue>

template <class T>
class Queue
{
public:
    Queue() { this->_container = new std::list<T>(); };

    ~Queue()
    {
        this->_container->clear();
        delete(this->_container);
    };

    void Push(T item) { _container->push_front(item); };

    void PushRange(Queue<T>* items)
    {
        auto it = items->GetContainer()->begin();

        while(it != items->GetContainer()->end())
        {
            T listItem = *it;

            _container->push_back(listItem);

            it++;
        }
    };

    T Pop()
    {
        if(_container->size() > 0)
        {
            T item = _container->front();
            _container->pop_front();

            return item;
        }

        return NULL;
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
        while(begin != end)
        {
            T obj = *begin;

            if(iterIndex == index)
                return obj;

            begin++;
        }

        return NULL;
    };

    std::list<T>* GetContainer() { return _container; };

private:
    // std::queue<T>* _container;
    std::list<T>* _container;
};

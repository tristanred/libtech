#pragma once

#include <vector>
#include <list>
#include <functional>
#include <algorithm>
#include <cassert>

template <class T>
class ArrayList
{
public:
    ArrayList()
    {
        _container = new std::vector<T>();
    };

    ArrayList(uint64_t initialSize)
    {
        _container = new std::vector<T>();

        _container->reserve(initialSize);
    };

    ~ArrayList()
    {
        _container->clear();
        delete(_container);
    };

    void Add(T item)
    {
        _container->push_back(item);
    };

    void AddRange(ArrayList<T>* items)
    {
        auto it = items->GetContainer()->begin();

        while (it != items->GetContainer()->end())
        {
            T listItem = *it;

            _container->push_back(listItem);

            it++;
        }
    };

    T Get(uint64_t index)
    {
        if (index < _container->size())
        {
            return _container->at(index);
        }
        
        return 0;
    };

    T& operator[] (uint64_t index)
    {
        return _container->at(index);
    }

    T GetBy(std::function<bool(T)> predicate)
    {
        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T element = *it;

            if (predicate(element))
            {
                return element;
            }
        }

        return 0;
    };

    T First()
    {
        auto it = _container->begin();

        return (*it);
    };

    T Last()
    {
        auto it = _container->end();

        it--;

        return (*it);
    };

    ArrayList<T>* Where(std::function<bool(T)> predicate)
    {
        ArrayList<T>* retList = new ArrayList<T>();

        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            auto test = predicate(*it);

            if (test)
            {
                retList->Add(*it);
            }
        }

        return retList;
    };

    T Single(std::function<bool(T)> predicate)
    {
        T retValue = NULL;

        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T val = *it;

            auto test = predicate(*it);

            if (test)
            {
                retValue = val;
            }
        }

        return retValue;
    };

    bool Contains(std::function<bool(T)> predicate)
    {
        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T element = *it;

            if (predicate(element))
            {
                return true;
            }
        }

        return false;
    };

    bool ContainsItem(T item)
    {
        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T element = *it;

            if (element == item)
            {
                return true;
            }
        }

        return false;
    }

    void ForEach(std::function<void(T)> func)
    {
        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T val = *it;

            func(val);
        }
    };

    uint64_t IndexOf(T item)
    {
        uint64_t i = 0;

        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T current = (*it);

            if (current == item)
            {
                return i;
            }
        }

        return 0;
    };

    void Swap(uint64_t indexA, uint64_t indexB)
    {
        auto x = _container->begin();
        auto y = _container->begin();
        // I would like to know what type to put in instead of auto
        auto elementA = std::next(x, indexA);
        auto elementB = std::next(y, indexB);

        std::iter_swap(elementA, elementB);
    };

    // void Shuffle()
    // {
    //     int length = this->Count();
    //     RandomGen rng;

    //     for (int i = length - 1; i > 0; i--)
    //     {
    //         int randomIndex = rng.GetRandom(length - 1);

    //         this->Swap(length - 1, randomIndex);
    //     }
    // };

    void RemoveAt(uint64_t index)
    {
        auto it = _container->begin();

        std::advance(it, index);

        _container->erase(it);
    };

    void RemoveObject(T object)
    {
        for (typename std::list<T>::iterator it = this->_container->begin(); it != this->_container->end(); it++)
        {
            T current = (*it);

            if (current == object)
            {
                _container->erase(it);

                break;
            }
        }
    };

    void Clear()
    {
        _container->clear();
    };

    uint64_t Count()
    {
        return _container->size();
    };
    
    T* GetListData()
    {
        T* data = new T[this->Count()];
        
        for(uint64_t i = 0; i < this->Count(); i++)
        {
            data[i] = this->Get(i);
        }
        
        return data;
    }

    T** GetListAs2dArray(uint64_t width)
    {
        assert(width > 0);

        uint64_t totalItems = this->Count();

        if (totalItems % width != 0)
            return 0;


        uint64_t columnIndex = 0;
        uint64_t rowIndex = 0;

        T** resultList = new T*[totalItems];
        T* row = new T[width];
        resultList[rowIndex] = row;

        auto it = this->GetContainer()->begin();
        while (it != this->GetContainer()->end())
        {
            resultList[rowIndex][columnIndex] = (*it);

            columnIndex++;

            if (columnIndex % width == 0)
            {
                rowIndex++;
                T* newRow = new T[width];
                resultList[rowIndex] = newRow;

                columnIndex = 0;
            }

            it++;
        }

        return resultList;
    };

    std::vector<T>* GetContainer()
    {
        return _container;
    };



protected:
    std::vector<T>* _container;

};

template <class T, class U>
ArrayList<U>* ListSelect(ArrayList<T>* input, std::function<U(T)> selector)
{
    ArrayList<U>* outList = new ArrayList<U>();

    for (typename std::vector<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
    {
        T element = *it;

        auto projected = selector(element);

        outList->Add(projected);
    }

    return outList;
};

template <class T, class Agg>
Agg ListAggregate(ArrayList<T>* input, Agg initial, std::function<Agg(Agg, T)> func)
{
    Agg aggregateValue = initial;

    for (typename std::vector<T>::iterator it = input->GetContainer()->begin(); it != input->GetContainer()->end(); it++)
    {
        T element = *it;

        aggregateValue = func(aggregateValue, element);
    }

    return aggregateValue;
}
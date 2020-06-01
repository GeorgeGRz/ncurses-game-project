#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <string.h>
#include "iostream"
#include "../Items/Item/Item.h"
#include <vector>

using namespace std;


class DynamicArray
{
private:
    Item  *items;
    size_t size = 0;
    size_t capacity;
public:
    DynamicArray();
    ~DynamicArray();

    void push_back(Item  *);
    void push_back(Item &);

    void erase(int index);
    
    void erase(Item  *);

    DynamicArray & operator=(DynamicArray &copy);

    void clear();

    Item  & operator[](int);

    vector<Item> toVector();
    
    int getSize();
    class iterator
    {
    private:
        Item *ptr;

    public:
        explicit iterator()
            : ptr(nullptr)
        {
        }
        explicit iterator(Item *p)
            : ptr(p)
        {
        }
        bool operator==(const iterator &rhs) const
        {
            return ptr == rhs.ptr;
        }
        bool operator!=(const iterator &rhs) const
        {
            return !(*this == rhs);
        }
        Item operator*() const
        {
            return *ptr;
        }
        iterator &operator++()
        {
            ++ptr;
            return *this;
        }
        iterator operator++(int)
        {
            iterator temp(*this);
            ++*this;
            return temp;
        }
        iterator begin();

        iterator end();
    };
    typename DynamicArray::iterator begin(){
        return iterator(items);
    }
    typename DynamicArray::iterator end(){
        return iterator(items + size);
    }
    
};

#endif

#include "DynamicArray.h"
DynamicArray & DynamicArray::operator=(DynamicArray & copy)
{
    if (this == &copy)
        return *this;

    delete[] items;
    size = copy.size;
    items = new Item[size];

    for (int i = 0; i < size; i++)
        items[i] = copy.items[i];
    return *this;
}

int DynamicArray::getSize()
{
    return size;
}

vector<Item> DynamicArray::toVector()
{
    vector<Item> ret;
    int i;
    for (i = 0; i < size; i++)
    {
        ret.push_back(items[i]);
        
    }
    return ret;
}

void DynamicArray::erase(Item * itm)
{
    int i;
    for (i = 0; i < size; i++)
    {
        if (&items[i] == itm)
        {
            erase(i);
            break;
        }
    }
}

Item & DynamicArray::operator[](int index)
{
    if (index < size)
    {
        return items[index];
    }
}


void DynamicArray::erase(int index)
{

    Item *temp_array = new Item[size - 1];
    int tempCounter = 0;
    for (int i = 0; i < size; i++)
    {
        if (i != index)
        {
            temp_array[tempCounter] = items[i];
            tempCounter++;
        }
    }
    if (this->items != nullptr)
    {
        delete[] items;
    }

    this->size -= 1;
    this->items = temp_array;
}


DynamicArray::DynamicArray()
{
    size = 0;
    capacity = 10;
    items = nullptr;
}


void DynamicArray::clear()
{
    ;
}
DynamicArray::~DynamicArray()
{
    delete[] items;
}
 
  

void DynamicArray::push_back(Item * item)
{
    Item * temp_array = new Item[size + 1];

    for (int i = 0; i < size; ++i)
    {
        if(items != nullptr )
            temp_array[i] = items[i];
    }

    temp_array[size] = *item;
    if (this->items != nullptr)
    {
        delete[] items;
    }

    this->size += 1;
    this->items = temp_array;
}

void DynamicArray::push_back(Item & item)
{
    Item * temp_array = new Item[size + 1];

    for (int i = 0; i < size; ++i)
    {
        if(items != nullptr )
            temp_array[i] = items[i];
    }

    temp_array[size] = item;

    if (this->items != nullptr)
    {
        delete[] items;
    }

    this->size += 1;
    this->items = temp_array;
}
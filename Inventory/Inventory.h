#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
using namespace std;
#include <vector>
#include "../Items/Item/Item.h"
#include "../DynamicArray/DynamicArray.h"
class Inventory{
    private:
        DynamicArray<Item> invItems;
    public:
        Inventory();
        Inventory(Item *items,int itemCount);
        Inventory(const Inventory & copy);
        ~Inventory();

        void addItem(Item &item);
        
        DynamicArray<Item> getInventoryItems();

        Item & getItemAt(int index);

        void removeItemAt(int index);
        
        DynamicArray<int> itemTypeCount();

        size_t getSize(){return invItems.size();}

        Inventory& operator=( Inventory & inv);

        void removeAll();

        DynamicArray<Item> removeAfterCrafting(itemType itemCraftedType);
};


#endif

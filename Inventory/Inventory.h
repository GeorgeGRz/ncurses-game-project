#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
using namespace std;
#include <vector>
#include "../Items/Item/Item.h"
#include "../DynamicArray/DynamicArray.h"
class Inventory{
    private:
        DynamicArray invItems;
    public:
        Inventory();
        Inventory(Item *items,int itemCount);
        Inventory(const Inventory & copy);
        ~Inventory();

        void addItem(Item &item);
        
        DynamicArray getInventoryItems();

        Item & getItemAt(int index);

        void removeItemAt(int index);
        
        Inventory& operator=( Inventory & inv);

        void removeAll();

        DynamicArray removeAfterCrafting(itemType itemCraftedType);
};


#endif

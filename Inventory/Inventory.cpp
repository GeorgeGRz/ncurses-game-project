#include "Inventory.h"

Inventory::Inventory()
{
    ;
}


Inventory::Inventory(const Inventory &copy)
{
    //this->inventoryItems = copy.inventoryItems;
}
Inventory::Inventory(Item *items, int itemCount)
{
    int i;
    for (i = 0; i < itemCount; i++)
    {
        //this->inventoryItems.push_back(&items[i]);
    }
}
Item &Inventory::getItemAt(int index)
{
    return invItems[index];
}
Inventory& Inventory::operator=(Inventory &inv)
{
    this->invItems = inv.invItems;
    return *this;
}

void Inventory::addItem(Item &item)
{
    
    this->invItems.push_back(item);
}
void Inventory::removeAll()
{
    
    invItems.clear();

}
void Inventory::removeItemAt(int index)
{
    invItems.erase(index);
}
DynamicArray Inventory::getInventoryItems(){
    DynamicArray cpArray;
    cpArray = invItems;
    return cpArray;
}
Inventory::~Inventory(){
    ;
}
DynamicArray Inventory::removeAfterCrafting(itemType itemCraftedType)
{
    DynamicArray itemsRemoved;
    
    int count = 0;
    bool rockFlag = false;
    bool cocFlag = false;
    bool leafFlag = false;
    bool woodFlag = false;
    
    int size = invItems.getSize();
    int i;
    for (i = 0; i < size ;){
        if (itemCraftedType == axe && (invItems[i].getType() == rock && rockFlag == false))
        {
            itemsRemoved.push_back(invItems[i]);
            invItems.erase(i);
            rockFlag = true;
            count++;
            
        }
        else if (itemCraftedType == axe && (invItems[i].getType() == woodstick && woodFlag == false))
        {
            itemsRemoved.push_back(invItems[i]);
            invItems.erase(i);
            woodFlag = true;
            count++;
           
        }
        else if (itemCraftedType == opencoconut && (invItems[i].getType() == coconut && cocFlag == false))
        {
            itemsRemoved.push_back(invItems[i]);
            invItems.erase(i);
            cocFlag = true;
            count++;
           
        }
        else if (itemCraftedType == opencoconut && (invItems[i].getType() == rock && rockFlag == false))
        {
            itemsRemoved.push_back(invItems[i]);
            invItems.erase(i);
            rockFlag = true;
            count++;
            
        }
        else if (itemCraftedType == lightedtorch && (invItems[i].getType() == leafs && leafFlag == false))
        {
            itemsRemoved.push_back(invItems[i]);
            invItems.erase(i);
            leafFlag = true;
            count++;
            
        }
        else if (itemCraftedType == lightedtorch && (invItems[i].getType() == woodstick && woodFlag == false))
        {
            itemsRemoved.push_back(invItems[i]);
            invItems.erase(i);
            woodFlag = true;
            count++;
           
        }
        else{
            i++;
           
        }
        if (count == 2)
            break;
    }
    
    return itemsRemoved;
}
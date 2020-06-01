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
    int i = 0;
    for(DynamicArray<Item>::iterator it= invItems.begin(); it!= invItems.end();){
        if(i == index){
            it = invItems.erase(it);
        }
        else{
            it++;
        }
        i++;
    }
    //invItems.erase(index);
}

DynamicArray<Item> Inventory::getInventoryItems(){
    DynamicArray<Item> cpArray;
    cpArray = invItems;
    return cpArray;
}
Inventory::~Inventory(){
    ;
}
DynamicArray<Item> Inventory::removeAfterCrafting(itemType itemCraftedType)
{
    DynamicArray<Item> itemsRemoved;
    
    int count = 0;
    bool rockFlag = false;
    bool cocFlag = false;
    bool leafFlag = false;
    bool woodFlag = false;
    
    int size = invItems.size();
    int count2 = 0;
    for (DynamicArray<Item>::iterator i = invItems.begin(); i !=invItems.end() ;){
        if (itemCraftedType == axe && (invItems[count2].getType() == rock && rockFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            rockFlag = true;
            count++;
            
        }
        else if (itemCraftedType == axe && (invItems[count2].getType() == woodstick && woodFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            woodFlag = true;
            count++;
           
        }
        else if (itemCraftedType == opencoconut && (invItems[count2].getType() == coconut && cocFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            cocFlag = true;
            count++;
           
        }
        else if (itemCraftedType == opencoconut && (invItems[count2].getType() == rock && rockFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            rockFlag = true;
            count++;
            
        }
        else if (itemCraftedType == lightedtorch && (invItems[count2].getType() == leafs && leafFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            leafFlag = true;
            count++;
            
        }
        else if (itemCraftedType == lightedtorch && (invItems[count2].getType() == woodstick && woodFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            woodFlag = true;
            count++;
           
        }
        else{
            i++;
            count2++;
        }
        if (count == 2)
            break;
    }
    
    return itemsRemoved;
}
#include "Player.h"
#include "../Vector2D/Vector2D.h"
#include "../Inventory/Inventory.h"
#include "../Items/Item/Item.h"
#include "../Items/LightedTorch/LightedTorch.h"
#include "../Items/OpenCoconut/OpenCoconut.h"
#include "../DynamicArray/DynamicArray.h"
#include "../Items/Axe/Axe.h"


ostream &operator<<(ostream &os, Item item)
{
    os << item.getId() + ";" + item.getName() + ";" + to_string(item.getType()) + ";" + to_string(item.getIfOnFloor()) + ";" + to_string(item.getPosition().x) + ";" + to_string(item.getPosition().y);
    return os;
}
Player::Player()
{
    playerName = "null";
}
DynamicArray<Item> Player::getItems()
{
    return playerItems.getInventoryItems();
}
DynamicArray<Item> Player::getCrafted()
{
    DynamicArray<Item> ret;
    int i = 0;
    int j = 0;
    DynamicArray<Item> items = (getItems());
    for (auto i : items)
    {
        for (auto j : items)
        {
            if(i.getId() == j.getId()) continue;
            Item ptr = i + j;
            if(ptr.getId()!="null")
                ret.push_back(ptr);
        }
    }
    return ret;
}
void Player::removeAllFromPlayer()
{
    playerItems.removeAll();
}
Player::Player(Vector2D<int> position, Inventory inv, string name):playerItems(inv),playerPosition(position)
{
    this->playerName = name;
    
}
Player::Player(const Player &copy):playerItems(copy.playerItems)
{
    this->playerPosition = copy.playerPosition;
    this->playerName = copy.playerName;
}
void Player::addToInventory(Item &itm)
{
    playerItems.addItem(itm);
}
void Player::moveToCoordinates(int X, int Y)
{
    this->playerPosition.x = X;
    this->playerPosition.y = Y;
}
Player Player::operator=(const Player &copy)
{
    if (this == &copy)
        return *this;
    else
    {
        this->playerName = copy.playerName;
        this->playerPosition = copy.playerPosition;
        
    }
    return *this;
}
void Player::showInventory(ostream &os)
{
    for (auto x : playerItems.getInventoryItems())
    {
        cout << x;
    }
}
void Player::removeFromInventory(int index)
{
    this->playerItems.removeItemAt(index);
}

void Player::deallocateItem(Item &itemptr)
{
    //this->playerItems->deallocateItem(itemptr);
}

Item &Player::getItemAt(int index)
{
    return this->playerItems.getItemAt(index);
}

DynamicArray<Item> Player::removeAfterCrafting(itemType itemCraftedType)
{
    return playerItems.removeAfterCrafting(itemCraftedType);
}

Player::~Player(){
   
    //delete playerPosition;
}
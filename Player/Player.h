#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;
#include "../Vector2D/Vector2D.h"
#include "../Inventory/Inventory.h"
#include <vector>
class Inventory;

class Item;
class Player
{
private:
    string playerName;
    Vector2D<int> playerPosition;
    Inventory playerItems;
    int hunger = 100;
public:
    Player(Vector2D<int> position, Inventory inv, string name = "P");
    Player(const Player &copy);
    Player();
    ~Player();

    int getHunger(){return hunger;}
    void setHunger(int h){hunger = h;}
    void addToInventory(Item &item);
    void deallocateItem(Item &item);
    void showInventory(ostream &stream);

    string getName() { return this->playerName; }
    const Vector2D<int> &getPosition() { return playerPosition; }
    Inventory &getInventory() { return playerItems; }

    Item &getItemAt(int index);

    void setName(string newName) { this->playerName = newName; }

    DynamicArray<Item> getItems();

    void moveToCoordinates(int X, int Y);
    void moveToCoordinates(Vector2D<int> newPosition);

    void removeFromInventory(int index);
    

    Player operator=(const Player &copy);

    DynamicArray<Item> getCrafted();

    void removeAllFromPlayer();

    DynamicArray<Item> removeAfterCrafting(itemType itemCraftedType);
};

#endif

#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;
#include "../../Vector2D/Vector2D.h"
enum itemType
{
    coconut,
    leafs,
    lighter,
    rock,
    woodstick,
    axe,
    hut,
    lightedtorch,
    opencoconut
};
class Item
{
private:
    string name;
    itemType typeOfItem;
    string id;
    bool isOnFloor;
    Vector2D<int> pos;

public:
    Item();
    Item(string name, string id, Vector2D<int> position, bool isOnFloor = true);
    Item(const Item &copy);

    string getName() const { return name; }
    string getId() const { return id; }
    bool getIfOnFloor() const { return isOnFloor; }
    itemType getType() const { return typeOfItem; }
    Vector2D<int> getPosition() const { return this->pos; }

    void setType(itemType type) { this->typeOfItem = type; }
    void setisOnFloor(bool value) { this->isOnFloor = value; }
    virtual ~Item();

    Item operator+(Item &item);
};
#endif
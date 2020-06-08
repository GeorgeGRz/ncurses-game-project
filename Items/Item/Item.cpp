#include "Item.h"
#include "../Axe/Axe.h"
#include "../LightedTorch/LightedTorch.h"
#include "../OpenCoconut/OpenCoconut.h"

#include "../Coconut/Coconut.h"
#include "../Leafs/Leafs.h"
#include "../Rock/Rock.h"
Item::Item()
{
    name = "null";
    id = "null";
    isOnFloor = true;
}

Item::Item(string name, string id, Vector2D<int> position, bool isOnFloor)
{
    this->name = name;
    this->id = id;
    this->isOnFloor = isOnFloor;
    this->pos = position;
}
Item::Item(const Item &itm)
{
    this->name = itm.name;
    this->id = itm.id;
    this->isOnFloor = itm.isOnFloor;
    this->pos = itm.pos;
    this->typeOfItem = itm.typeOfItem;
}

Item Item::operator+(Item &item)
{
    if (this->getType() == woodstick && item.getType() == leafs)
    {
        //Εάν ο τύπος του αντικειμένου 
        return  LightedTorch("lightedTorch", "l1", this->getPosition(), false);
    }
    else if (this->getType() == rock && item.getType() == coconut)
    {
        return  OpenCoconut("OpenCoconut", "oc1", this->getPosition(), false);
    }
    else if (this->getType() == woodstick && item.getType() == rock)
    {
        return  Axe("Axe", "a1", this->getPosition(), false);
    }
    return Axe("null","null",Vector2D<int>(0,0));
}
Item::~Item() { ; }
#include "Hut.h"
#include "../../Vector2D/Vector2D.h"
Hut::Hut() : Item()
{
    this->setType(hut);
}
Hut::Hut(string name, string id, Vector2D<int> pos, bool isOnFloor) : Item(name, id, pos, isOnFloor)
{
    this->setType(hut);
}
Hut::Hut(const Hut &copy) : Item(copy.getName(), copy.getId(), copy.getPosition(), copy.getIfOnFloor())
{
    this->setType(hut);
}

Hut::~Hut() { ; }
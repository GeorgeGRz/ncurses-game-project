#ifndef Hut_H
#define Hut_H
#include "../Item/Item.h"

class Hut : public Item
{
private:
public:
    Hut();
    Hut(string name, string id, Vector2D<int> pos, bool isOnFloor = true);
    Hut(const Hut &copy);

    ~Hut();
};
#endif
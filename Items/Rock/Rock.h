#ifndef Rock_H
#define Rock_H
#include "../Item/Item.h"

class Rock : public Item{
    private:

    public:
        Rock();
        Rock(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        Rock(const Rock& copy);

        ~Rock();
};
#endif
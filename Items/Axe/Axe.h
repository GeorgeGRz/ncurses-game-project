#ifndef Axe_H
#define Axe_H
#include "../Item/Item.h"

class Axe : public Item{
    private:

    public:
        Axe();
        Axe(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        Axe(const Axe& copy);

        ~Axe();
};
#endif
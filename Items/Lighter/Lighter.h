#ifndef Lighter_H
#define Lighter_H
#include "../Item/Item.h"

class Lighter : public Item{
    private:

    public:
        Lighter();
        Lighter(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        Lighter(const Lighter& copy);

        ~Lighter();
};
#endif
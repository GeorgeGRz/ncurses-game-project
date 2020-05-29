#ifndef OpenCoconut_H
#define OpenCoconut_H
#include "../Item/Item.h"

class OpenCoconut : public Item{
    private:

    public:
        OpenCoconut();
        OpenCoconut(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        OpenCoconut(const OpenCoconut& copy);

        ~OpenCoconut();
};
#endif
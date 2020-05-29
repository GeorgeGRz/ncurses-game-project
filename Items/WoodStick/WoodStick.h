#ifndef WoodStick_H
#define WoodStick_H
#include "../Item/Item.h"
#include "../Rock/Rock.h"
#include "../Axe/Axe.h"
class WoodStick : public Item{
    private:

    public:
        WoodStick();
        WoodStick(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        WoodStick(const WoodStick& copy);

        
        ~WoodStick();
};
#endif
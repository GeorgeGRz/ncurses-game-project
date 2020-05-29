#include "WoodStick.h"
#include "../../Vector2D/Vector2D.h"
WoodStick::WoodStick():Item(){
    this->setType(woodstick);
}
WoodStick::WoodStick(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(woodstick);
}
WoodStick::WoodStick(const WoodStick & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(woodstick);
}


WoodStick::~WoodStick(){;}
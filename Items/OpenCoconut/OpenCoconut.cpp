#include "OpenCoconut.h"
#include "../../Vector2D/Vector2D.h"
OpenCoconut::OpenCoconut():Item(){
    this->setType(opencoconut);
}
OpenCoconut::OpenCoconut(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(opencoconut);
}
OpenCoconut::OpenCoconut(const OpenCoconut & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(opencoconut);
}

OpenCoconut::~OpenCoconut(){;}
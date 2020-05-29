#include "Axe.h"
#include "../../Vector2D/Vector2D.h"
Axe::Axe():Item(){
    this->setType(axe);
}
Axe::Axe(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(axe);
}
Axe::Axe(const Axe & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(axe);
}

Axe::~Axe(){;}
#include "Coconut.h"
#include "../../Vector2D/Vector2D.h"
Coconut::Coconut():Item(){
    this->setType(coconut);
}
Coconut::Coconut(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(coconut);
}
Coconut::Coconut(const Coconut & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(coconut);
}

Coconut::~Coconut(){;}
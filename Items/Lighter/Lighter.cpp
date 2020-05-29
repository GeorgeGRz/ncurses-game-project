#include "Lighter.h"
#include "../../Vector2D/Vector2D.h"
Lighter::Lighter():Item(){
    this->setType(lighter);
}
Lighter::Lighter(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(lighter);
}
Lighter::Lighter(const Lighter & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(lighter);
}

Lighter::~Lighter(){;}
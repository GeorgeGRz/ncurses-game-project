#include "Leafs.h"
#include "../../Vector2D/Vector2D.h"
Leafs::Leafs():Item(){
    this->setType(leafs);
}
Leafs::Leafs(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(leafs);
}
Leafs::Leafs(const Leafs & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(leafs);
}

Leafs::~Leafs(){;}
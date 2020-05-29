#include "Rock.h"
#include "../../Vector2D/Vector2D.h"
Rock::Rock():Item(){
    this->setType(rock);
}
Rock::Rock(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(rock);
}
Rock::Rock(const Rock & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(rock);
}

Rock::~Rock(){;}
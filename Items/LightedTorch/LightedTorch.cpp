#include "LightedTorch.h"
#include "../../Vector2D/Vector2D.h"
LightedTorch::LightedTorch():Item(){
    this->setType(lightedtorch);
}
LightedTorch::LightedTorch(string name,string id,Vector2D<int> pos, bool isOnFloor):Item(name,id,pos,isOnFloor){
    this->setType(lightedtorch);
}
LightedTorch::LightedTorch(const LightedTorch & copy):Item(copy.getName(),copy.getId(),copy.getPosition(),copy.getIfOnFloor()){
    this->setType(lightedtorch);
}

LightedTorch::~LightedTorch(){;}
#include <iostream>
using namespace std;
#include "Player/Player.h"
#include "Items/Item/Item.h"
#include "Inventory/Inventory.h"
#include "Items/Coconut/Coconut.h"
#include "Items/Rock/Rock.h"
#include "Environment/Environment.h"
#include "GameScene/GameScene.h"
ostream & operator<<(ostream& s, Player p){
    s<< p.getName();
    return s;
}

int main(){
    
    GameScene * scene = new GameScene;
    
    delete scene;
    
    
    
    return 0;
}
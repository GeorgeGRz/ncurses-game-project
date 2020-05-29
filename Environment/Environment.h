#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include <iostream>
using namespace std;
#include "../DynamicArray/DynamicArray.h"
#include <vector>
#include "../Player/Player.h"
class Item;
class Player;


class Environment{
    private:
        vector<Item> groundItems;
        Player  playerEntity;
        char ** Grid;
        int gridX,gridY;
    public:
        static int lastID;
        Environment();
        Environment(const Environment & env);
        Environment(Player &player, int X, int Y);
        
        ~Environment();

        char ** getGrid(){return this->Grid;}
        void movePlayer(int x,int y);

        void addItemToInv(Item & itemPtr);
        
        void addItemToGround(Item & item);
        
        void addItemToGround(vector<Item > items);

        void removeFromPlayerInv(Item & itemptr);
        void removeItem(Item & itemptr);

        void clearAll();

        void generateGrid(int numberOfEntities);
        vector<Item> getGroundItems(){ return groundItems;}
        vector<Item> getPlayerItems();
        Player & getPlayer(){return this->playerEntity;}

        Item & getItemAt(int X, int Y);

        void handleLoadedData(vector<Item> ldata,bool isStartup);

        int getX(){return this->gridX;}
        int getY(){return this->gridY;}

        int checkOccurences(Item & item);

        Item & getPlayerItem(int index);
        vector<Item> getItemsNearPlayer();

        DynamicArray getPlayerCraft();

        

        
};


#endif

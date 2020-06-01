#ifndef IOCLASS_H
#define IOCLASS_H
#include <ncurses.h>
#include <vector>
#include <iostream>
#include "../Player/Player.h"

using namespace std;
class Item;
class Environment;
class IoClass{
    private:

    public:
        IoClass();
        vector<Item> loadFromFile(string fileName);
        void saveToFile(string fileName,Environment & env);

        string readString();

        void printToCoordsAnimated(int x, int y,string stringToPrint,std::initializer_list<string> a_args,int speed);

        int showMenu(std::vector<string> selections);

        void printEnvironment(Environment& env);
        void printPlayerStats(Player& player);
        ~IoClass();

        int getMaxX();
        int getMaxY();
        int getInput();   


};

#endif
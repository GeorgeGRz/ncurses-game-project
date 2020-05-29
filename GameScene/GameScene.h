#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <iostream>
using namespace std;

enum GameState {initializing,waiting,running,saving,loading,exiting};
class Environment;
class IoClass;

class GameScene{
    private:
        GameState state;
        IoClass *ioManager;
        Environment *env;
        bool isOver = false;
        bool continueAfterEnd = false;
        bool endByMenu = false;
    public:
        GameScene();
        GameScene(IoClass *ioManager,Environment *env);
        GameScene(const GameScene & copy);
        
        GameState getState(){return state;}
        

        void setState(GameState state){this->state = state;}
        string startupScreen();
        void Play();

        void parseSelection(int c);

        void handleMainMenu(int menuSelection);
        void handleInventoryMenu(int menuSelection);
        void handleCraftingMenu(int menuSelection);
        void handleEndingMenu(int menuSelection);
        
        ~GameScene();
};





#endif

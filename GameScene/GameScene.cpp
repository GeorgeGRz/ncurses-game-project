#include "GameScene.h"
#include "../Environment/Environment.h"
#include "../IO/IoClass.h"
#include "../Inventory/Inventory.h"
#include "../Items/Axe/Axe.h"
#include "../Items/Coconut/Coconut.h"
#include "../Items/LightedTorch/LightedTorch.h"
#include "../Items/OpenCoconut/OpenCoconut.h"
#include "../Player/Player.h"

#include "unistd.h"
GameScene::GameScene()
{
    this->state = initializing;
    this->ioManager = new IoClass();
    string playerName = startupScreen();//Χρήση της startupScreen() για να λάβουμε το όνομα του χρήστη
    Player player(Vector2D<int>(2, 2), Inventory(), playerName);//Δημιουργία αντικειμένου παίκτη
    int id;
    vector<Item> initDat = this->ioManager->loadFromFile("data/init.csv", id);//Ανάγνωση των δεδομένων απο το αρχικό αρχείο ώστε να φορτωθούν
    this->env = new Environment(player, ioManager->getMaxY(), ioManager->getMaxX(), id);//Δημιουργία αντικειμένου περιβάλλοντος
    this->setState(loading);

    this->env->handleLoadedData(initDat, true);//Καλούμε την handleLoadedData με ορίσματα τον vector που περιέχει τα δεδομένα που διαβάστηκαν απο το αρχείο καθώς και με flag = true ώστε να γίνουν οι ενέργιες του startup
    env->generateGrid(9);//Στη συνέχεια δημιουργείται πλέγμα με 9 αντικείμενα 
    Play();//Καλείται η κύρια μέθοδος - game loop
}
GameScene::~GameScene()
{
    delete ioManager;
    delete env;
}

void GameScene::handleMainMenu(int menuSelection)
{
    int id;
    if (menuSelection == 3) {
        endByMenu = true;//εάν η επιλογή του μενού είναι η 3η, δηλαδή επιλέχθηκε ο τερματισμός τότε 
        //γίνεται SET το flag endByMenu ωστε να γίνει ο τερματισμός του παιχνιδιού
    } else if (menuSelection == 1) {//Αλλιώς εάν πρόκειται για LOAD απο αρχείο
        vector<Item> lDat = this->ioManager->loadFromFile("data/appData.csv", id);//Φορτώνονται τα δεδομένα του αρχείου ως αντικείμενα στον vector lDat
        this->env->handleLoadedData(lDat, false);//Στη συνέχεια καλείται η handleLoadedData με ορίσματα ldat και false αυτή τη φορά διότι δεν πρόκειται για startup
    } else if (menuSelection == 2) {//Αλλιώς εάν έχει επιλεχθεί το SAVE τότε καταγράφονται τα δεδομένα της εφαρμογής στο κατάλληλο αρχείο
        this->ioManager->saveToFile("data/appData.csv", *env);
    }
    this->setState(running);
}
/**
 * @brief Δέχεται δυναμικό πίνακα με ακεραίους και επιστρέφει true εάν βρεί έναν ακέραιο μεγαλύτερο του 1.
 * 
 * @param items Ο δυναμικός πίνακας με τους ακεραίους.
 * @return true Βρέθηκε στοιχείο μεγαλύτερο του 1.
 * @return false Δέν βρέθηκε στοιχείο μεγαλύτερο του 1.
 */
bool uparxounDipla(DynamicArray<int> items)
{
    for (auto x : items) {
        if (x > 1)
            return true;
    }
    return false;
}

void GameScene::handleInventoryMenu(int menuSelection)
{
    this->setState(running);
    int sel = menuSelection;
    if (sel > 0) {
        Item itm;
        //Εάν υπάρχουν διπλά,τριπλά η n-πλα αντικείμενα τότε δημιουργόταν πρόβλημα λόγω του summarization που γινόταν.
        //Για να λυθεί απλα παίρνουμε το αντικείμενο χρησιμοποιόντας το menuSelection και οχι menuSelection-1.
        //Αυτό γιατι με το summarization άλλαζε το index.
        if (uparxounDipla(env->getPlayer().getInventory().itemTypeCount())) {
            itm = env->getPlayerItem(menuSelection);
        } else
            itm = env->getPlayerItem(menuSelection - 1);
        int pX = env->getPlayer().getPosition().x;
        int pY = env->getPlayer().getPosition().y;
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);
        if (pX < maxY - 1 && pX > 0 && pY < maxX - 1 && pY > 0) {
            if (env->getGrid()[pX + 1][pY + 1] == ' ') {
                itm.setPosition(Vector2D<int>(pX + 1, pY + 1));
                this->env->removeFromPlayerInv(itm);
            }
        }
    }
}
void GameScene::handleCraftingMenu(int menuSelection)
{
    this->setState(running);
    if (menuSelection > 0) {
        Item craftedItem = env->getPlayerCraft()[menuSelection - 1];
        DynamicArray<Item> itemsRemoved;

        if (craftedItem.getType() == axe) {
            Axe craftedAxe(craftedItem.getName(), craftedItem.getId(), craftedItem.getPosition());
            this->env->addItemToGround(craftedAxe);
            this->env->addItemToInv(craftedAxe);
            itemsRemoved = (env->getPlayer().removeAfterCrafting(axe));
        } else if (craftedItem.getType() == opencoconut) {
            OpenCoconut craftedOpenCoconut(craftedItem.getName(), craftedItem.getId(), craftedItem.getPosition());
            this->env->addItemToGround(craftedOpenCoconut);
            this->env->addItemToInv(craftedOpenCoconut);
            itemsRemoved = (env->getPlayer().removeAfterCrafting(opencoconut));
        } else if (craftedItem.getType() == lightedtorch) {
            LightedTorch craftedLightedTorch(craftedItem.getName(), craftedItem.getId(), craftedItem.getPosition());
            this->env->addItemToGround(craftedLightedTorch);
            this->env->addItemToInv(craftedLightedTorch);
            itemsRemoved = (env->getPlayer().removeAfterCrafting(lightedtorch));
        }

        DynamicArray<Item>::iterator allIt = itemsRemoved.begin();
        for (; allIt != itemsRemoved.end();) {
            this->env->removeItemFromGround(*allIt);
            allIt++;
        }
        this->isOver = true;
    }
}

void GameScene::parseSelection(int c)
{
    switch (c) {

    case 109: //if key is m then we have to handle the main menu
    {
        clear();
        this->setState(waiting);
        handleMainMenu(this->ioManager->showMenu({ "Back to Game", "Load", "Save", "Exit" }));
        break;
    }
    case 10: //if key is enter
    {
        if (env->getPlayer().getInventory().getSize() <= 10) {
            vector<Item> itemsNear = this->env->getItemsNearPlayer();
            for (auto x : itemsNear) {
                this->env->addItemToInv(x);
            }
        } else {
            ioManager->printToCoordsAnimated(1, 1, "Not enough space, player can hold only 10 items", { "" }, 1);
            refresh();
        }

        break;
    }
    case 105: //if key is i then we have to show player inventory
    {
        clear();
        this->setState(waiting);
        vector<string> items;
        items.push_back("Back to game");
        for (auto x : env->getPlayer().summarizeItems()) { 
            items.push_back(x);
        }
        handleInventoryMenu(this->ioManager->showMenu(items));
        break;
    }
    case 99: // if key is c then we have to show what user can craft
    {
        clear();
        this->setState(waiting);
        vector<string> items;
        items.push_back("Back to game");
        for (auto x : env->getPlayerCraft()) {
            items.push_back((x.getName() + " ID " + x.getId()));
        }
        handleCraftingMenu(this->ioManager->showMenu(items));
        break;
    }
    case KEY_UP: {
        clear();
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x - 1, y);
        break;
    }
    case KEY_DOWN: {
        clear();
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x + 1, y);
        break;
    }
    case KEY_LEFT: {
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x, y - 1);
        break;
    }
    case KEY_RIGHT: {
        clear();
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x, y + 1);
        break;
    }
    default: {
        refresh();
        break;
    }
    }
}
void GameScene::handleEndingMenu(int menuSelection)
{
    if (menuSelection == 0) // yes
    {
        continueAfterEnd = true;
    } else // no
    {
        continueAfterEnd = false;
    }
}
void GameScene::checkHunger(chrono::minutes::rep& timePassed, chrono::_V2::system_clock::time_point& start)
{
    if (timePassed > 1) {
        int playerHunger = env->getPlayer().getHunger();
        env->getPlayer().setHunger(playerHunger - 10);
        timePassed = 0;
        start = chrono::high_resolution_clock::now();
    }
}
void GameScene::Play()
{

    auto startTime = std::chrono::high_resolution_clock::now();
    while (1) {
        if (env->getPlayer().getHunger() == 0)
            break;
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (endByMenu == true)
            break;
        this->setState(running);
        parseSelection(this->ioManager->getInput());
        this->ioManager->printEnvironment(*(this->env));
        if (isOver == true && continueAfterEnd == false) {
            clear();
            this->ioManager->printToCoordsAnimated(0, 0, "Congrats, you have finished the game, would you like to continue?", { "" }, 1);
            usleep(30000);
            clear();
            handleEndingMenu(this->ioManager->showMenu({ "Yes", "No" }));
            if (continueAfterEnd == false)
                break;
        }
        auto timePassed = chrono::duration_cast<chrono::minutes>(currentTime - startTime).count();
        checkHunger(timePassed, startTime);
    }
}
string GameScene::startupScreen()
{
    this->ioManager->printToCoordsAnimated(0, 0, "Hello, give me your name please\n", { " " }, 1);
    string playerName = ioManager->readString();
    if (playerName == "")
        playerName = "Player";
    clear();
    this->ioManager->printToCoordsAnimated(0, 0, "Γεία σου %s!\n ", { playerName }, 1);
    return playerName;
}
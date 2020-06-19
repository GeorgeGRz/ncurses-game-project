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
    string playerName = startupScreen();                         //Χρήση της startupScreen() για να λάβουμε το όνομα του χρήστη
    Player player(Vector2D<int>(2, 2), Inventory(), playerName); //Δημιουργία αντικειμένου παίκτη
    int id;
    vector<Item> initDat = this->ioManager->loadFromFile("data/init.csv", id);           //Ανάγνωση των δεδομένων απο το αρχικό αρχείο ώστε να φορτωθούν
    this->env = new Environment(player, ioManager->getMaxY(), ioManager->getMaxX(), id); //Δημιουργία αντικειμένου περιβάλλοντος
    this->setState(loading);

    this->env->handleLoadedData(initDat, true); //Καλούμε την handleLoadedData με ορίσματα τον vector που περιέχει τα δεδομένα που διαβάστηκαν απο το αρχείο καθώς και με flag = true ώστε να γίνουν οι ενέργιες του startup
    env->generateGrid(9);                       //Στη συνέχεια δημιουργείται πλέγμα με 9 αντικείμενα
    Play();                                     //Καλείται η κύρια μέθοδος - game loop
}
GameScene::~GameScene()
{
    delete ioManager;
    delete env;
}

void GameScene::handleMainMenu(int menuSelection)
{
    int id;
    if (menuSelection == 3)
    {
        endByMenu = true; //εάν η επιλογή του μενού είναι η 3η, δηλαδή επιλέχθηκε ο τερματισμός τότε
        //γίνεται SET το flag endByMenu ωστε να γίνει ο τερματισμός του παιχνιδιού
    }
    else if (menuSelection == 1)
    {                                                                              //Αλλιώς εάν πρόκειται για LOAD απο αρχείο
        vector<Item> lDat = this->ioManager->loadFromFile("data/appData.csv", id); //Φορτώνονται τα δεδομένα του αρχείου ως αντικείμενα στον vector lDat
        this->env->handleLoadedData(lDat, false);                                  //Στη συνέχεια καλείται η handleLoadedData με ορίσματα ldat και false αυτή τη φορά διότι δεν πρόκειται για startup
    }
    else if (menuSelection == 2)
    { //Αλλιώς εάν έχει επιλεχθεί το SAVE τότε καταγράφονται τα δεδομένα της εφαρμογής στο κατάλληλο αρχείο
        this->ioManager->saveToFile("data/appData.csv", *env);
    }
    this->setState(running);
}

void GameScene::handleInventoryMenu(int menuSelection)
{
    this->setState(running);
    int sel = menuSelection;
    if (sel > 0)
    {
        Item itm;
        itemType tempType = env->getPlayerItem(menuSelection - 1).getType();
        //Ανάλογα με τον τύπο του αντικειμένου θέλουμε και το αντίστοιχο τελευταίο αντικείμενο.
        //Πχ εάν ο παίκτης θέλει να πετάξει στην γή ενα αντικείμενο τύπου πέτρας, τότε θα επιλεχθεί το τελευταίο αντικείμενο πετρας που βρίσκετα
        //Στον δυναμικό πίνακα.Ομοίως και με τα υπόλοιπα αντικείμενα.Η getIndexOfLastItem() επιστρέφει δυναμικό πίνακα όπου κάθε στοιχείο του 
        //Περιέχει το last index για κάθε τύπο αντικειμένων.Για παράδειγμα το 1ο στοιχείο του(θέση 0) περιέχει το last index απο τα αντικείμενα lighter.
        //Έτσι, εάν ο χρήστης επιλέξει να πετάξει αναπτήρα τότε θα χρησιμοποιήσουμε την getIndexOfLastItem() για να πετάξουμε τον τελευταίο αναπτήρα που έχει ο χρήστης στα αντικείμενα του
        //Αυτό λόγω του summarization που έγινε, οι θέσεις των αντικειμένων δεν είναι οι absolute θέσεις.
        if (tempType == lighter)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[0]);
        }
        else if (tempType == woodstick)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[1]);
        }
        else if (tempType == leafs)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[2]);
        }
        else if (tempType == rock)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[3]);
        }
        else if (tempType == coconut)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[4]);
        }
        else if (tempType == axe)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[5]);
        }
        else if (tempType == opencoconut)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[6]);
        }
        else if (tempType == lightedtorch)
        {
            itm = env->getPlayerItem(env->getPlayer().getInventory().getIndexOfLastItem()[7]);
        }
        int pX = env->getPlayer().getPosition().x;
        int pY = env->getPlayer().getPosition().y;
        int maxX, maxY;
        getmaxyx(stdscr, maxY, maxX);
        if (pX < maxY - 1 && pX > 0 && pY < maxX - 1 && pY > 0)
        {
            bool flag = true;//Χρησιμοποιείται ώστε να ξέρουμε εάν ο χρήστης μπορεί να πετάξει σε αυτό το σημείο το αντικείμενο, δεν πρεπει να κανει overlap.
            for (int k = env->getPlayer().getPosition().y + 1; k <= env->getPlayer().getPosition().y + 1 + itm.getName().length(); k++)
            {
                if (env->getGrid()[env->getPlayer().getPosition().x + 1][k] != ' ')
                    flag = false;//Εάν έστω και μία θέση είναι κατειλημένη τότε ο χρήστης δέν μπορεί να πετάξει το αντικείμενο εκεί
                break;
            }
            if (flag == true)
            {
                //εάν δεν βρεθεί κατειλημένη θέση τοτε αλλάζουμε την θέση του αντικειμένου και το πετάμε στο πάτωμα στη θέση του παίκτη + 1 προς τα κάτω.
                itm.setPosition(Vector2D<int>(pX + 1, pY + 1));
                this->env->removeFromPlayerInv(itm);
            }
        }
    }
}
void GameScene::handleCraftingMenu(int menuSelection)
{
    this->setState(running);
    if (menuSelection > 0)
    {
        Item craftedItem = env->getPlayerCraft()[menuSelection - 1];
        //Η getPlayerCraft() επιστρέφει δυναμικό πίνακα με τα αντικείμενα που μπορεί ο χρήστης να φτιάξει
        //Στη συνέχεια γίνεται επιλογή για το αντικείμενο που επέλεξε ο χρήστης στο μενού
        DynamicArray<Item> itemsRemoved;

        if (craftedItem.getType() == axe)
        {
            /*
                Εάν πρόκειται για αντικείμενο τύπου τσεκούρι(axe) τότε δημιουργείται ενα νεό αντικείμενο τσεκούρι.
                Στη συνέχεια το προσθέτει στο πάτωμα και μετά στο inventory του χρήστη.
                Τέλος, πρωτού τερματιστεί αφαιρεί τα αντικείμενα που χρησιμοποίησε ώστε να craftarei το τσεκούρι καλόντας την removeAfterCrafting() με παράμετρο axe
                
                Σημείωση : Το ίδιο γίνεται και για τα άλλα 2 αντικείμενα, ωστόσο δεν θα γραψω αναλυτικά ωστε να μην γεμίσει ο κώδικας με ανούσια σχόλια.
            */
            Axe craftedAxe(craftedItem.getName(), craftedItem.getId(), craftedItem.getPosition());
            this->env->addItemToGround(craftedAxe);
            this->env->addItemToInv(craftedAxe);
            itemsRemoved = (env->getPlayer().removeAfterCrafting(axe));
        }
        else if (craftedItem.getType() == opencoconut)
        {
            OpenCoconut craftedOpenCoconut(craftedItem.getName(), craftedItem.getId(), craftedItem.getPosition());
            this->env->addItemToGround(craftedOpenCoconut);
            this->env->addItemToInv(craftedOpenCoconut);
            itemsRemoved = (env->getPlayer().removeAfterCrafting(opencoconut));
        }
        else if (craftedItem.getType() == lightedtorch)
        {
            LightedTorch craftedLightedTorch(craftedItem.getName(), craftedItem.getId(), craftedItem.getPosition());
            this->env->addItemToGround(craftedLightedTorch);
            this->env->addItemToInv(craftedLightedTorch);
            itemsRemoved = (env->getPlayer().removeAfterCrafting(lightedtorch));
        }

        /*
            Τέλος πρωτού τερματιστεί χρησιμοποιεί την επιστροφή της removeAfterCrafting() ώστε να αφαιρέσει απο το πλέγμα τα αντικείμενα
            που χρησιμοποιήθηκαν για την δημιουργία του αντικειμένου
        */
        DynamicArray<Item>::iterator allIt = itemsRemoved.begin();
        for (; allIt != itemsRemoved.end();)
        {
            this->env->removeItemFromGround(*allIt);
            allIt++;
        }
        this->isOver = true;//Κάνει SET το Flag τερματισμού.
    }
}

void GameScene::parseSelection(int c)
{
    switch (c)
    {

    case 109: //Εάν ο χρήστης πατήσει το κουμπί m -> Main Menu
    {
        clear();
        this->setState(waiting);
        handleMainMenu(this->ioManager->showMenu({"Back to Game", "Load", "Save", "Exit"}));//Εμφανίζεται μενού με τις επιλογές και καλείται η handleMainMenu με παράμετρο τον αριθμο της επιλογής.
        break;
    }
    case 10: //Εάν ο χρήστης πατήσει το κουμπί enter(return) και ΔΕΝ ειναι κανένα μενου ενεργοποιημένο τότε ο χρήστης προσπαθεί να προσθέσει αντικείμενο στο inventory του
    {
        if (env->getPlayer().getInventory().getSize() <= 10)//Εάν έχει χώρο, στην τσάντα του
        {
            vector<Item> itemsNear = this->env->getItemsNearPlayer();//Λαμβάνονται τα αντικείμενα γύρω απο τον παίκτη
            for (auto x : itemsNear)
            {
                this->env->addItemToInv(x);//Προστίθενται ενα προς ένα
            }
        }
        else
        {
            //Αλλιώς εμφανίζεται κατάλληλο μύνημα
            ioManager->printToCoordsAnimated(1, 1, "Not enough space, player can hold only 10 items", {""}, 1);
            refresh();
        }

        break;
    }
    case 105: //Εάν ο χρήστης πατήσει το κουμπί i -> Inventory
    {
        clear();
        this->setState(waiting);
        vector<string> items;
        items.push_back("Back to game");
        //Προστίθεται 1η επιλογή back to game και στη συνέχεια αφού γίνουν τα αντικείμενα summarize προστίθονται οι περιγραφές τους στον vector items
        for (auto x : env->getPlayer().summarizeItems())
        {
            items.push_back(x);
        }
        handleInventoryMenu(this->ioManager->showMenu(items));//Εμφανίζεται μενού με τις περιγραφές των αντικειμένων και καλείται η handleInventoryMenu με παράμετρο τον αριθμό επιλογής που έκανε ο χρήστης στο μενου.
        break;
    }
    case 99: //Εάν ο χρήστης πατήσει το κουμπί c -> Crafting menu
    {
        //Εαν ο χρήστης πατήσει το κουμπί c τότε εμφανίζονται σε μενού τα αντικείμενα που μπορεί να φτιάξει και καλείται να επιλέξει ενα η να επιστρεψει στο αρχικό μενου
        clear();
        this->setState(waiting);
        vector<string> items;
        items.push_back("Back to game");
        for (auto x : env->getPlayerCraft())
        {
            items.push_back(x.getName());
        }
        //Αφου εμφανιστει το μενου και ο χρήστης επιλέξει αντικείμενο που θέλει να δημιουργήσει τότε καλείται η handleCraftingMenu η οποία παίρνει ως παράμετρο τον αριθμό της επιλογής που έκανε ο χρήστης στο μενού
        handleCraftingMenu(this->ioManager->showMenu(items));
        break;
    }
    case KEY_UP:
    {
        clear();
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x - 1, y);//Χ - 1 διότι μετακινείται ο χρήστης κατα ενα row προς τα πάνω.Εδω δουλεύει κάπως ανάποδα.
        break;
    }
    case KEY_DOWN:
    {
        clear();
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x + 1, y);//Ομοιως Χ + 1 γιατι μετακινείται ενα row προς τα κατω
        break;
    }
    case KEY_LEFT:
    {
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x, y - 1);//Αντιστοιχα ενα column πιο αριστερά
        break;
    }
    case KEY_RIGHT:
    {
        clear();
        int x = this->env->getPlayer().getPosition().x;
        int y = this->env->getPlayer().getPosition().y;
        this->env->movePlayer(x, y + 1);//Ένα column πιο δεξιά
        break;
    }
    default:
    {
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
    }
    else // no
    {
        continueAfterEnd = false;
    }
}
void GameScene::checkHunger(chrono::minutes::rep &timePassed, chrono::_V2::system_clock::time_point &start)
{
    if (timePassed > 1)
    {
        //Εάν έχει περάσει 1 λεπτό τότε μειώνεται το επίπεδο πείνας του παίκτη και στη συνέχεια εκχωρείται η τιμη 0 στον χρόνο που έχει περάσει
        //Καθώς και αλλάζει η τιμή του start στην τωρινή ώρα.
        int playerHunger = env->getPlayer().getHunger();
        env->getPlayer().setHunger(playerHunger - 10);
        timePassed = 0;
        start = chrono::high_resolution_clock::now();
    }
}
void GameScene::Play()
{
    //Κύριο Game loop
    auto startTime = std::chrono::high_resolution_clock::now();
    while (1)
    {
        if (env->getPlayer().getHunger() == 0)
            break;//εαν το επιπεδο πεινας φτάσει να ειναι 0 τότε τερματίζεται το παιχνίδι
        auto currentTime = std::chrono::high_resolution_clock::now();
        if (endByMenu == true)
            break;
        this->setState(running);
        parseSelection(this->ioManager->getInput());//Περιμένει μέχρι ο χρήστης να πατήσει ένα πλήκτρο και στη συνέχεια δρα ανάλογα με οτ πλήκτρο που πάτησε ο χρήστης
        this->ioManager->printEnvironment(*env);//Ζωγραφίζει το πλέγμα καθώς και όλα τα αντικείμενα στην κύρια οθόνη
        if (isOver == true && continueAfterEnd == false)//Εάν ο χρήστης εφτιαξε αντικείμενο τότε εμφανίζεται μύνημα με το εάν θέλει να συνεχίσει διότι τυπικά το παιχνίδι τερματίζεται οταν δημιουργηθεί ένα αντικείμενο
        {
            clear();
            this->ioManager->printToCoordsAnimated(0, 0, "Congrats, you have finished the game, would you like to continue?", {""}, 1);
            usleep(30000);
            clear();
            handleEndingMenu(this->ioManager->showMenu({"Yes", "No"}));
            if (continueAfterEnd == false)
                break;
        }
        auto timePassed = chrono::duration_cast<chrono::minutes>(currentTime - startTime).count();
        checkHunger(timePassed, startTime);//Εάν δέν εχει τερματιστεί τότε γίνεται ο υπολογισμός του επιπέδου πείνας του παίκτη
    }
}
string GameScene::startupScreen()
{
    //Ζητάει απο τον χρήστη να πληκτρολογίσει το όνομα του και στη συνέχεια εμφανίζει κατάλληλο μύνημα με οδηγείες
    this->ioManager->printToCoordsAnimated(0, 0, "Hello, give me your name please\n", {" "}, 0.7);
    string playerName = ioManager->readString();
    if (playerName == "")
        playerName = "Player";
    clear();
    this->ioManager->printToCoordsAnimated(0, 0, "Welcome to our world %s!", {playerName},0.7);
    this->ioManager->printToCoordsAnimated(1,0,"Use arrow keys to navigate",{""},0.7);
    this->ioManager->printToCoordsAnimated(2,0,"Press m to open main menu and return to select option",{""},0.7);
    this->ioManager->printToCoordsAnimated(3,0,"Press i to open inventory and return to select item",{""},0.7);
    this->ioManager->printToCoordsAnimated(4,0,"Press c to open crafting menu and return to select item",{""},0.7);
    this->ioManager->printToCoordsAnimated(5,0,"Add items to your inventory using return",{""},0.7);
    this->ioManager->printToCoordsAnimated(6,0,"Press a key to continue",{""},0.7);
    return playerName;
}
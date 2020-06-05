#include "Environment.h"
#include "../Items/Item/Item.h"
#include <string.h>
#include <algorithm>
#include "../Inventory/Inventory.h"
#include "../Items/Coconut/Coconut.h"
#include "../Items/Rock/Rock.h"
#include "../Items/Lighter/Lighter.h"
#include "../Items/WoodStick/WoodStick.h"
#include "../Vector2D/Vector2D.h"
#include "../Items/Leafs/Leafs.h"
int Environment::lastID = 0;
#include <ncurses.h>
Environment::Environment(Player &player, int X, int Y,int lastid):playerEntity(player)
{
    Grid = new char *[X]; //Δεσμευση X δεικτών
    gridX = X; 
    gridY = Y;
    lastID = lastid; //Οταν δημιουργηθεί το Environment θα χρησιμοποιήσει την lastid ωστε να συνεχίσει να αυξάνει το ID των αντικειμένων.Δεν πρεπει να ξανααρχισει απο το 0 διοτι ετσι θα διαγραφονται 2 αντικειμενα.

    for (int i = 0; i < gridX; i++)
    {
        Grid[i] = new char[Y]; //Δεσμευση Y δεικτών
        
        for (int j = 0; j < gridY; j++)
        {
            Grid[i][j] = ' ';//Βάζω τον κενό χαρακτήρα στο κάθε κελί στην αρχή
            if (i == 0 || i == getmaxy(stdscr) - 1)
            {
                Grid[i][j] = '=';//Εαν προκειται για την 1η η τελευταια γραμμή τότε θέλω να υπάρχει =
            }
            else if (j == 0 || j == getmaxx(stdscr) - 1)
            {
                Grid[i][j] = '|';//Ομοια για αριστερα και δεξια
            }
            if (i == playerEntity.getPosition().x && j == playerEntity.getPosition().y)
            {
                Grid[i][j] = playerEntity.getName()[0];//Εαν πρόκεται για την θεση του χρήστη τότε βάζω τον 1ο χαρακτήρα του ονόματος του
            }
            else
            {
                for (auto x : groundItems) //Αλλιώς εμφανίζω το όνομα του αντικειμένου
                {
                    if (x.getPosition().x == i && x.getPosition().y == j)
                    {
                        Grid[i][j] = x.getName()[0];
                    }
                }
            }
        }
    }
}
Environment::Environment()
{
    //Ο default δημιουργεί ενα 5χ5 grid και το αρχικοποιεί με κενά
    int gridX = gridY = 5;
    Grid = new char *[5];

    for (int i = 0; i < 5; i++)
    {
        Grid[i] = new char[5];
        for (int j = 0; j < 5; j++)
        {
            Grid[i][j] = ' ';
        }
    }
}
DynamicArray<Item> Environment::getPlayerItems() { 
    return playerEntity.getItems(); //Επιστρέφει τα αντικείμενα του παίκτη

}

void Environment::addItemToInv(Item &itm)
{
    int index = 0;

    for (auto x = groundItems.begin(); x != groundItems.end(); ++x)
    {
        if ((*x).getId() == itm.getId())
        {
            //Για κάθε αντικείμενο που βρίσκεται στον πίνακα των αντικειμενων που βρισκονται στο πάτωμα
            //Εάν το αντικειμενο παραμέτρου έχει το ίδιο ID με το αντικείμενο x 
            itm.setisOnFloor(false);//Το αντικείμενο δεν θα βρίσκεται πλέον στο πάτωμα
            playerEntity.addToInventory(itm);//Προσθετουμε το αντικείμενο στον πίνακα αντικειμένων του χρήστη

            for (int k = (*x).getPosition().y; k <= (*x).getPosition().y + (*x).getName().length(); k++)
            {
                Grid[(*x).getPosition().x][k] = ' ';//καθαρίζουμε το Grid απο το όνομα του αντικειμένου
            }
            groundItems.erase(x);//Σβήνουμε το αντικείμενο x
            break;
        }
    }
}



vector<Item> Environment::getItemsNearPlayer()
{
    vector<Item> t;
    for (auto item : groundItems)
    {
        if (abs(item.getPosition().x - playerEntity.getPosition().x) == 1 || !abs(item.getPosition().x - playerEntity.getPosition().x))
        {
            //Εάν το αντικείμενο βρίσκεται κοντά στον χρήστη τότε το προσθέτω στον vector<Item> t 
            if ((playerEntity.getPosition().y + 1 == item.getPosition().y) || (playerEntity.getPosition().y <= item.getPosition().y + item.getName().length()) && !(playerEntity.getPosition().y < item.getPosition().y))
                t.push_back(item);
            clear();
        }
    }
    return t;//επιστρέφω τον vector
}
Item &Environment::getItemAt(int x, int y)
{
    Item ret;
    for (auto item : groundItems)
    {
        if (item.getPosition().x == x && item.getPosition().y == y)
        {
            return item;
        }
    }
    return ret;
}
Item &Environment::getPlayerItem(int index)
{
    return playerEntity.getItemAt(index);
}

void Environment::removeFromPlayerInv(Item &item)
{

    int index = 0;
    for (auto x : playerEntity.getInventory().getInventoryItems())
    {
        /*
            Με όμοιο αφαιρείται αντικείμενο απο τον πίνακα του παίκτη
        */
        if (x.getId() == item.getId())
        {
            //Εαν βρεθεί το αντικείμενο στον πίνακα του παίκτη
            item.setisOnFloor(true);//Το αντικείμενο πλέον βρίσκεται στο πάτωμα
            addItemToGround(item);//Προστίθεται το αντικείμενο στο πάτωμα
            int count = 0;
            for (int k = item.getPosition().y; k <= item.getPosition().y + item.getName().length(); k++)
            {
                Grid[item.getPosition().x][k] = item.getName()[count];
                count++;
                //Χρησιμοποιείται για να εμφανιστεί σωστά το όνομα του αντικειμένου
            }
            playerEntity.removeFromInventory(index);//Αφαίρεση απο τον πίνακα αντικειμένων με την χρήση της θεσης(index)
            break;
        }
        index++;
    }
}
/**
 * @brief Επιστρέφει τον τύπο του Enum με βάση το index.
 * Θυμίζω πως επειδή πρόκεται για Enum τότε οι τύποι ξεκινάνε με το 0 και αυξάνονται κατα 1
 * 
 * @param i Το index
 * @return itemType Ο τύποες πιστροφής
 */
itemType EnumOfIndex(int i)
{
    if (i >= 0 && i <= 4)//Τα βασικα αντικείμενα είναι τα εξής woodstick,rock,lighter,coconut,leafs.Έτσι δεν πρέπει να εμφανίστει παράγωγο αυτών.
        return static_cast<itemType>(i);
}
/**
 * @brief Δημιουργεί εναν τυχαίο ακέραιο αριθμό
 * 
 * @param min 
 * @param max 
 * @return int 
 */
int generateRandomInt(int min, int max)
{
    return min + (rand() % static_cast<int>(max - min + 1));//Το static_cast χρησιμοποιείται έτσι ώστε να μετατραπεί ο αριθμός σε ακέραιο
}

/**
 * @brief Επιστρέφει εναν τυχαίο τύπο αντικειμένου
 * 
 * @return itemType 
 */
itemType genRandomItemType()
{
    int randNum = generateRandomInt(0,4);//Δημιουργεί τυχαίο αριθμό μεταξύ του 0 και 4 
    return EnumOfIndex(randNum);//Καλει την EnumOfIndex για να επιστρέψει τύπο αντικειμένου με βάση τον τυχαίο αριθμό που δημιουργήθηκε
}

void Environment::generateGrid(int numberOfEntities)
{
    int i;
    for (i = 0; i < numberOfEntities; i++)
    {
        /*
            Επεξηγηματικά, αυτό που γίνεται είναι οτι επιλέγεται ενας τυχαίος τύπος αντικειμένου και στη συνέχεια 
            μια τυχαία θέση που είναι μικρότερη απο τα όρια του πλέγματος.Στη συνέχεια ανάλογα με τον τύπο που παράχθηκε
            δημιουργούντε τα αντίστοιχα αντικείμενα και προστίθεντε στο πάτωμα.
        */
        itemType typeOfItem = genRandomItemType();
        Vector2D<int> pos = Vector2D<int>(generateRandomInt(1, gridX - 1), generateRandomInt(1, gridY - 1));
        if (typeOfItem == coconut)
        {
            string id = "coc" + to_string(Environment::lastID);
            Coconut coc("coconut", id, pos);
            lastID++;
            addItemToGround(coc);
        }
        else if (typeOfItem == woodstick)
        {
            string id = "wod" + to_string(Environment::lastID);
            WoodStick wod("woodstick", id, pos);
            lastID++;
            addItemToGround(wod);
        }
        else if (typeOfItem == lighter)
        {
            string id = "lig" + to_string(Environment::lastID);
            Lighter lig("lighter", id, pos);
            lastID++;
            addItemToGround(lig);
        }
        else if (typeOfItem == leafs)
        {
            string id = "lea" + to_string(Environment::lastID);
            Leafs leaf("leafs", id, pos);
            lastID++;
            addItemToGround(leaf);
        }
        else if (typeOfItem == rock)
        {
            string id = "roc" + to_string(Environment::lastID);
            Rock rok("rock", id, pos);
            lastID++;
            addItemToGround(rok);
        }
    }
}


DynamicArray<Item> Environment::getPlayerCraft()
{
    return playerEntity.getCrafted();
    
}

void Environment::handleLoadedData(vector<Item> ldata, bool isStartup)
{
    
    if (isStartup == false)
    {
        //Εάν δεν διαβάζει απο το αρχείο για πρώτη φορά, δηλαδή δεν βρισκόμαστε στο Startup πρέπει να αφαιρεθούν όλα τα αντικείμενα
        playerEntity.removeAllFromPlayer();//Διαγράφονται τα αντικείμενα απο το inventory του παίκτη
        for (auto x : groundItems)
        {
            for (int k = x.getPosition().y; k <= x.getPosition().y + x.getName().length(); k++)
            {
                Grid[x.getPosition().x][k] = ' ';//Καθαρίζεται το Grid απο όλα τα αντικείμενα
            }
        }
        groundItems.clear();//Διαγράφονται τα αντικείμενα
    }
    for (auto item : ldata)
    {
        bool flag = true;//Ορισμός flag που θα χρησιμοποιηθεί για να καταλαβω εαν το αντικείμενο ειναι στο πατωμα.
        if (item.getIfOnFloor() == false)//Εαν το αρχείο αναφέρει οτι το αντικείμενο ΔΕΝ ειναι στο πατωμα τότε το flag = false
            flag = false;
        addItemToGround(item);//Στη συνέχεια το αντικέιμενο προστίθεται στο πάτωμα
        if (flag == false)
        {
            addItemToInv(item);//Εαν το flag == false (δηλαδη το αντικείμενο φορτώθηκε με προορισμο το inventory) τότε προστίθεται σε αυτο
        }
    }
}
void Environment::addItemToGround(Item &item)
{
    if (Grid[item.getPosition().x][item.getPosition().y] == ' ')
    {
        //Εάν ο πρώτος χαρακτήρας του αντικειμένου μπορεί να προστεθεί στο πλέγμα

        
        bool canBePlaced = true;//Χρησιμοποιείται για να καταλάβω εάν μπορεί να προστεθεί ο κάθε χαρακτήρας του ονοματος του αντικειμενου
        int count = 0;
        for (int k = item.getPosition().y; k <= item.getPosition().y + item.getName().length(); k++)
        {
            if (Grid[item.getPosition().x][k] != ' '){
                //Εαν εστω και ενας χαρακηρας του ονοματος δεν μπορεί να τοποθετηθεί τότε
                canBePlaced = false;//To canBePlaced flag γινεται false
                break; //Γίνεται break ωστε να μην συνεχίσει η επανάληψη
            }
            count++;
        }
        count = 0;//Αρχικοποίηση του count
        if (canBePlaced == true){
            //Εαν το αντικέιμενο μπορεί να προστεθεί τελικά
            groundItems.push_back(item);//Προσθήκη στον πίνακα
            item.setisOnFloor(true);//SET του flag για το εαν βρισκεται στο πάτωμα
            for (int k = item.getPosition().y; k <= item.getPosition().y + item.getName().length(); k++)
            {
                Grid[item.getPosition().x][k] = item.getName()[count];
                count++;
                //Προσθήκη του κάθε χαρακτήρα του ονόματος
            }
        }
            
    }
}

void Environment::removeItemFromGround(Item &itemptr)
{
    vector<Item>::iterator groundIt = groundItems.begin();
    for (; groundIt != groundItems.end();)
    {
        if ((*groundIt).getId() == itemptr.getId())
        {
            groundIt = groundItems.erase(groundIt);
        }
        else
        {
            groundIt++;
        }
    }
}
void Environment::movePlayer(int X, int Y)
{
    int maxX,maxY;
    getmaxyx(stdscr,maxY,maxX);
    if ((Grid[X][Y] == ' ' || Grid[X][Y] == '\0') && X < maxY - 1 && Y < maxX -1 && X > 0 && Y > 0)
    {
        Grid[playerEntity.getPosition().x][playerEntity.getPosition().y] = ' ';
        playerEntity.moveToCoordinates(X, Y);
        Grid[playerEntity.getPosition().x][playerEntity.getPosition().y] = playerEntity.getName()[0];
    }
}

Environment::~Environment()
{
    int i, j;
    /*
    for (i = 0; i < gridX; i++)
    {
        delete[] Grid[i];
    }
    delete[] Grid;
    */
}
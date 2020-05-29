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
Environment::Environment(Player &player, int X, int Y):playerEntity(player)
{
    Grid = new char *[X];
    gridX = X;
    gridY = Y;
    lastID = 6;
    groundItems = groundItems;
    for (int i = 0; i < gridX; i++)
    {
        Grid[i] = new char[Y];
        int playerNameCounter = 0;
        for (int j = 0; j < gridY; j++)
        {
            Grid[i][j] = ' ';
            if (i == 0 || i == getmaxy(stdscr) - 1)
            {
                Grid[i][j] = '=';
            }
            else if (j == 0 || j == getmaxx(stdscr) - 1)
            {
                Grid[i][j] = '|';
            }
            if (i == playerEntity.getPosition().x && j == playerEntity.getPosition().y)
            {
                Grid[i][j] = playerEntity.getName()[0];
            }
            else
            {
                for (auto x : groundItems)
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
vector<Item> Environment::getPlayerItems() { return playerEntity.getItems().toVector(); }
int Environment::checkOccurences(Item &item)
{
    int count = 0;
    for (auto x : groundItems)
    {
        if (x.getId() == item.getId())
            count++;
    }
    return count;
}
void Environment::addItemToInv(Item &itm)
{
    int index = 0;

    for (auto x = groundItems.begin(); x != groundItems.end(); ++x)
    {
        if ((*x).getId() == itm.getId())
        {
            itm.setisOnFloor(false);
            playerEntity.addToInventory(itm);

            for (int k = (*x).getPosition().y; k <= (*x).getPosition().y + (*x).getName().length(); k++)
            {
                Grid[(*x).getPosition().x][k] = ' ';
            }
            groundItems.erase(x);
            break;
        }
    }
}
int getIndexInWord(string str, char character)
{

    return str.find_last_of(character);
}

string getStringAt(char *str, int starting)
{
    string ret;
    string a;
    int i;
    for (i = starting; i >= 0; i--)
    {
        if (str[i] != ' ' && str[i] != '|')
            a.push_back(str[i]);
        if (str[i] == ' ')
            break;
    }
    string b;
    for (i = starting + 1; i <= strlen(str); i++)
    {
        if (str[i] != ' ' && str[i] != '|')
            b.push_back(str[i]);
        if (str[i] == ' ')
            break;
    }
    reverse(a.begin(), a.end());
    ret = a + b;
    return ret;
}
vector<Item> Environment::getItemsNearPlayer()
{
    vector<Item> t;
    for (auto item : groundItems)
    {
        if (abs(item.getPosition().x - playerEntity.getPosition().x) == 1 || !abs(item.getPosition().x - playerEntity.getPosition().x))
        {
            if ((playerEntity.getPosition().y + 1 == item.getPosition().y) || (playerEntity.getPosition().y <= item.getPosition().y + item.getName().length()) && !(playerEntity.getPosition().y < item.getPosition().y))
                t.push_back(item);
            clear();
        }
    }
    return t;
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
    for (auto x : playerEntity.getInventory().getInventoryItems().toVector())
    {
        if (x.getId() == item.getId())
        {
            item.setisOnFloor(true);
            addItemToGround(item);
            int count = 0;
            for (int k = item.getPosition().y; k <= item.getPosition().y + item.getName().length(); k++)
            {
                Grid[item.getPosition().x][k] = item.getName()[count];
                count++;
            }
            playerEntity.removeFromInventory(index);
            break;
        }
        index++;
    }
}
itemType EnumOfIndex(int i)
{
    if (i >= 0 && i <= 4)
        return static_cast<itemType>(i);
}
//coconut,leafs,lighter,rock,woodstick,axe,hut,lightedtorch,opencoconut
itemType genRandomItemType()
{
    int randNum = 0 + (rand() % static_cast<int>(4 - 0 + 1));
    return EnumOfIndex(randNum);
}
int generateRandomNumber(int min, int max)
{
    return min + (rand() % static_cast<int>(max - min + 1));
}
void Environment::generateGrid(int numberOfEntities)
{
    int i;
    for (i = 0; i < numberOfEntities; i++)
    {
        itemType typeOfItem = genRandomItemType();
        Vector2D<int> pos = Vector2D<int>(generateRandomNumber(1, gridX - 1), generateRandomNumber(1, gridY - 1));
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

void Environment::clearAll()
{

    int index = 0;
    bool deleted = false;
    playerEntity.removeAllFromPlayer();
    groundItems.clear();

    
}
DynamicArray Environment::getPlayerCraft()
{
    return playerEntity.getCrafted();
}

void Environment::handleLoadedData(vector<Item> ldata, bool isStartup)
{
    if (isStartup == false)
    {
        playerEntity.removeAllFromPlayer();
        for (auto x : groundItems)
        {
            for (int k = x.getPosition().y; k <= x.getPosition().y + x.getName().length(); k++)
            {
                Grid[x.getPosition().x][k] = ' ';
            }
        }
        groundItems.clear();
    }

    for (auto item : ldata)
    {
        bool flag = true;
        if (item.getIfOnFloor() == false)
            flag = false;
        addItemToGround(item);
        if (flag == false)
        {
            addItemToInv(item);
        }
    }
}
void Environment::addItemToGround(Item &item)
{

   groundItems.push_back(item);
    item.setisOnFloor(true);

    if (Grid[item.getPosition().x][item.getPosition().y] == ' ')
    {
        bool canBePlaced = true;

        int count = 0;
        for (int k = item.getPosition().y; k <= item.getPosition().y + item.getName().length(); k++)
        {
            if (Grid[item.getPosition().x][k] != ' ')
                canBePlaced = false;
            count++;
        }
        count = 0;
        if (canBePlaced == true)
            for (int k = item.getPosition().y; k <= item.getPosition().y + item.getName().length(); k++)
            {
                Grid[item.getPosition().x][k] = item.getName()[count];
                count++;
            }
    }
}

void Environment::removeItem(Item &itemptr)
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
    if ((Grid[X][Y] == ' ' || Grid[X][Y] == '\0') && X > 0 && Y > 0)
    {
        Grid[playerEntity.getPosition().x][playerEntity.getPosition().y] = ' ';
        playerEntity.moveToCoordinates(X, Y);
        Grid[playerEntity.getPosition().x][playerEntity.getPosition().y] = playerEntity.getName()[0];
    }
}

Environment::~Environment()
{
    int i, j;
    for (i = 0; i < gridX; i++)
    {
        delete[] Grid[i];
    }
    delete[] Grid;
}
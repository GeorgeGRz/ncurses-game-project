#include "IoClass.h"
#include <unistd.h>
#include "../DynamicArray/DynamicArray.h"
#include "../Environment/Environment.h"
#include "../CSVRow/CSVRow.h"
#include "../Items/Coconut/Coconut.h"
#include "../Items/Leafs/Leafs.h"
#include "../Items/Rock/Rock.h"
#include "../Items/Lighter/Lighter.h"
#include <menu.h>
#include "../Items/WoodStick/WoodStick.h"
#include <regex>
IoClass::IoClass()
{
    initscr();
    noecho();
    curs_set(2);
    cbreak();
    keypad(stdscr, TRUE);
}
IoClass::~IoClass()
{
    endwin();
}
std::istream &operator>>(std::istream &str, CSVRow &data)
{
    data.readNextRow(str);
    return str;
}

int IoClass::getMaxX()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    return x;
}

void IoClass::printPlayerStats(Player & pl)
{
    int Xloc = getmaxx(stdscr) - 25;
    string info = "Hunger: ";
    for(int i = 0; i < pl.getHunger(); i+=10){
        info+="#";
    }
    mvprintw(1,Xloc,info.c_str());
}
int IoClass::getMaxY()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    return y;
}

vector<Item> IoClass::loadFromFile(string filename,int & id)
{
    id = 0;
    std::ifstream file(filename);
    vector<Item> items;
    CSVRow row;
    while (file >> row)
    {
        
        if (Vector2D<int>(stoi(row[4]), stoi(row[5])).x >= getmaxy(stdscr) - 1 || Vector2D<int>(stoi(row[4]), stoi(row[5])).y >= getmaxx(stdscr))
            continue;
        bool floor = false;
        if (row[3] == "1")
        {
            floor = true;
        }
        if (row[2] == "0")
        {
            //coconut
            Coconut coconut_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(coconut_obj);
        }
        else if (row[2] == "1")
        {
            //leaf
            Leafs leafs_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(leafs_obj);
        }
        else if (row[2] == "2")
        {
            Lighter lighter_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(lighter_obj);
        }
        else if (row[2] == "3")
        {
            //rock
            Rock rock_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(rock_obj);
        }
        else
        {
            //wood
            WoodStick woodStick(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(woodStick);
        }
        id++;
    }
    return items;
}
string IoClass::readString()
{
    string input;
    echo();
    int ch = getch();

    while (ch != '\n')
    {
        input.push_back(ch);
        ch = getch();
    }

    noecho();
    return input;
}
fstream &operator<<(fstream &fs, Item &item)
{
    fs << item.getId() << ";" << item.getName() << ";" << item.getType() << ";" << item.getIfOnFloor() << ";" << item.getPosition().x << ";" << item.getPosition().y << endl;
    return fs;
}
void IoClass::saveToFile(string filename, Environment &env)
{
    fstream file;
    file.open(filename, ios_base::out);
    vector<Item> allItems;
    for (auto x : env.getGroundItems())
    {
        allItems.push_back(x);
    }
    for (auto y : env.getPlayerItems())
    {
        allItems.push_back(y);
    }
    if (file.good())
    {
        
        for (auto item : allItems)
        {
            file << item;
        }
    }
    file.close();
}
bool replace(std::string &str, const std::string &from, const std::string &to)
{
    size_t start_pos = str.find(from);
    if (start_pos == std::string::npos)
        return false;
    str.replace(start_pos, from.length(), to);
    return true;
}

int IoClass::getInput()
{
    return getch();
}
void IoClass::printToCoordsAnimated(int X, int Y, string str, std::initializer_list<string> a_args, int speed)
{
    int i;

    for (auto x : a_args)
    {
        replace(str, "%s", x);
        try{
            if(stoi(x))
                replace(str,"%d",x);
        }
        catch(exception & e){
            ;
        }
    }

    for (i = 0; i < str.length(); i++)
    {
        string s = "";
        s += str[i];
        mvprintw(X, Y + i, s.c_str());
        refresh();
        usleep(70000 * speed);
    }
}

void IoClass::printEnvironment(Environment &env)
{
    for (int i = 0; i < env.getX(); i++)
    {
        for (int j = 0; j < env.getY(); j++)
        {
            string s = "";
            s += env.getGrid()[i][j];
            mvprintw(i, j, s.c_str());
        }
    }
    printPlayerStats(env.getPlayer());
    refresh();
}

int IoClass::showMenu(std::vector<string> selections)
{
    ITEM **my_items;
    int c;
    MENU *my_menu;
    int n_choices;
    ITEM *cur_item;
    n_choices = selections.size();
    my_items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    int n = 0;
    for (auto i = selections.begin(); i != selections.end(); i++)
    {
        my_items[n] = new_item(i->c_str(), NULL);
        n++;
    }
    my_items[n_choices] = (ITEM *)NULL;

    my_menu = new_menu((ITEM **)my_items);

    post_menu(my_menu);
    refresh();

    while ((c = getch()))
    {
        switch (c)
        {
        case KEY_DOWN:
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM);
            break;
        case 10:
        {
            int ind = current_item(my_menu)->index;
            unpost_menu(my_menu);
            free_menu(my_menu);
            int j;
            for (j = 0; j < n_choices + 1; j++)
            {
                free_item(my_items[j]);
            }
            free(my_items);
            clear();
            return ind;
            break;
        }
        }
    }
    int j;
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (j = 0; j < n_choices + 1; j++)
    {
        free_item(my_items[j]);
    }
    free(my_items);
    return -1;
}
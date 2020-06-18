#include "IoClass.h"
#include "../CSVRow/CSVRow.h"
#include "../DynamicArray/DynamicArray.h"
#include "../Environment/Environment.h"
#include "../Items/Coconut/Coconut.h"
#include "../Items/Leafs/Leafs.h"
#include "../Items/Lighter/Lighter.h"
#include "../Items/Rock/Rock.h"
#include "../Items/WoodStick/WoodStick.h"
#include <menu.h>
#include <regex>
#include <unistd.h>

IoClass::IoClass()
{
    initscr(); //Βασική συνάρτηση της ncurses που κανει initialize/προετοιμάζει τν οθονη
    noecho(); //Δεν εμφανιζονται οι χαρακτηρες που πληκτρολογει ο χρήστης στην οθονη
    curs_set(2); //Ρυθμιση του κέρσορα ωστε να εμφανίζεται με υψηλή ορατότητα
    cbreak(); //απενεργοποιεί το buffering,κάνοντας τους χαρακτήρες που πληκτρολογούνται διαθέσιμους στο πρόγραμμα
    keypad(stdscr, TRUE); //ενεργοποιεί το keypad της stdscr (στανταρ οθόνης)
}
/**
 * @brief Destroy the Io Class:: Io Class object
 * 
 */
IoClass::~IoClass()
{
    endwin(); //Ομοια της initscr αλλα αυτη τη φορα για να το απενεργοποιησει και να
    //αλλαξει πίσω στην κανονική λειτουργία του τερματικού
}
/**
 * @brief Υπερφόρτωση τελεστή >> σε αντικείμενο istream με αντικείμενο CSVRow
 * Δηλαδή μπορεί να χρησιμοποιηθεί ως istream obj >> csvrow obj
 * 
 * @param str 
 * @param data 
 * @return std::istream& 
 */
std::istream& operator>>(std::istream& str, CSVRow& data)
{

    data.readNextRow(str);
    return str;
}

int IoClass::getMaxX()
{
    int x, y;
    getmaxyx(stdscr, y, x); //Επιστρέφει τις διαστασης της οθόνης stdscr
    return x;
}

void IoClass::printPlayerStats(Player& pl)
{
    int Xloc = getmaxx(stdscr) - 25; //Ξεκινάει πάντα απο μια συγκεκριμένη θέση. αυτη είναι 25 χαρακτήρες αριστερα απο το όριο της οθόνης στο Χ
    string info = "Hunger: ";
    for (int i = 0; i < pl.getHunger(); i += 10) {
        info += "#";
    }
    mvprintw(1, Xloc, info.c_str()); //Εμφάνιση του αλφαριθμητικού στη συγκεκριμένη θέση
}
int IoClass::getMaxY()
{
    int x, y;
    getmaxyx(stdscr, y, x);
    return y;
}

vector<Item> IoClass::loadFromFile(string filename, int& id)
{
    id = 0;
    std::ifstream file(filename); //Άνοιγμα του αρχείου με ονομα filename
    vector<Item> items;
    CSVRow row;
    if (!file.good()) {
        return items; //Εάν το αρχείο δεν ειναι ετοιμο(χρησιμοποιείται ήδη ή δεν υπαρχει) επιστρεφει κενο vector
    }
    while (file >> row) {
        //Στη συνεχεια με την χρηση του υπερφορτωμένου operator>> περνάμε την κάθε γραμμή στο row και διαβάζουμε τα δεδομένα
        if (Vector2D<int>(stoi(row[4]), stoi(row[5])).x >= getmaxy(stdscr) - 1 || Vector2D<int>(stoi(row[4]), stoi(row[5])).y >= getmaxx(stdscr))
            continue; //εάν το αντικείμενο ΔΕΝ μπορεί να εμφανισθεί στο πλεγμα διοτι η το Χ η το Υ είναι μεγαλύτερα απο τον μέγιστο αριθμο τότε δεν δημιουργείται το αντικείμενο
        //Εάν το αντικείμενο μπορει να προστεθεί στο πλεγμα τότε το δημιουργούμε
        bool floor = false;
        if (row[3] == "1") {
            floor = true;
        }
        if (row[2] == "0") {
            //coconut
            Coconut coconut_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(coconut_obj);
        } else if (row[2] == "1") {
            //leaf
            Leafs leafs_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(leafs_obj);
        } else if (row[2] == "2") {
            Lighter lighter_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(lighter_obj);
        } else if (row[2] == "3") {
            //rock
            Rock rock_obj(row[1], row[0], Vector2D<int>(stoi(row[4]), stoi(row[5])), floor);
            items.push_back(rock_obj);
        } else {
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
    echo(); //εμφανιση χαρακτηρων που πληκτρολογουνται
    int ch = getch();

    while (ch != '\n') {
        input.push_back(ch); //οσο ο χαρακτηρας ειναι δαιφορετικος του newline τον διαβαζει και τον προσθετει στο τελος του string
        ch = getch();
    }

    noecho();
    return input;
}
fstream& operator<<(fstream& fs, Item& item)
{
    fs << item.getId() << ";" << item.getName() << ";" << item.getType() << ";" << item.getIfOnFloor() << ";" << item.getPosition().x << ";" << item.getPosition().y << endl;
    return fs;
}
void IoClass::saveToFile(string filename, Environment& env)
{
    fstream file;
    file.open(filename, ios_base::out);
    vector<Item> allItems;
    for (auto x : env.getGroundItems()) {
        allItems.push_back(x);
    }
    for (auto y : env.getPlayerItems()) {
        allItems.push_back(y);
    }
    if (file.good()) {

        for (auto item : allItems) {
            file << item;
        }
    }
    file.close();
}

/**
 * @brief Χρησιμοποιείται για να αντικαταστήσει ενα μερος(from) του αρχικού string str με ενα αλλο string(to)
 * 
 * @param str string στο οποιο θα γινει η αλλαγή
 * @param from substring του str το οποιο θελουμε να αντικαταστήσουμε
 * @param to string με το οποιο θα γινει η αντικατασταση
 * @return 
 */
bool replace(std::string& str, const std::string& from, const std::string& to)
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

    for (auto x : a_args) {
        replace(str, "%s", x); //πηγαινει στο string str και αντικαθιστά  τα %s με το x
        try {
            if (stoi(x))
                replace(str, "%d", x); //Ομοίος για τα %d
        } catch (exception& e) {
            ;
        }
    }
    //Εμφανίζει στα Χ και Υ που δοθηκαν ως παράμετροι το αλφαριθμητικό που θέλει ο χρήστης
    for (i = 0; i < str.length(); i++) {
        string s = "";
        s += str[i];
        mvprintw(X, Y + i, s.c_str());
        refresh();
        usleep(70000 * speed);
    }
}

void IoClass::printEnvironment(Environment& env)
{
    //Εμφανιζει ολα τα αντικείμενα που υπαρχουν στο περιβάλλον, βασική μέθοδος που "ζωγραφίζει".
    for (int i = 0; i < env.getX(); i++) {
        for (int j = 0; j < env.getY(); j++) {
            string s = "";
            s += env.getGrid()[i][j];
            mvprintw(i, j, s.c_str());
        }
    }
    printPlayerStats(env.getPlayer()); //Εμφανίζει πληροφορίες για τον παικτη
    refresh();
}

int IoClass::showMenu(std::vector<string> selections)
{
    ITEM** my_items;
    int c;
    MENU* my_menu;
    int n_choices;
    ITEM* cur_item;
    n_choices = selections.size(); //πληθος επιλογών ίσο με το μέγεθος του vector
    my_items = (ITEM**)calloc(n_choices + 1, sizeof(ITEM*)); //Δεσμευση μνήμης για 2d array με struct ITEM. Δεσμευση n_choices  + 1 δεικτών σε ITEM*
    int n = 0;
    for (auto i = selections.begin(); i != selections.end(); i++) {
        my_items[n] = new_item(i->c_str(), NULL); //Δημιουργία του menu item μεσω της new_item() η οποια δεχεται 2 αλφαριθμητικά τα οποία θα χρησιμοποιηθούν ως text.Εαν πχ βαλω "Χ" θα εμφανιζεται το Χ σαν επιλογή
        n++;
    }
    my_items[n_choices] = (ITEM*)NULL;

    my_menu = new_menu((ITEM**)my_items); //Δημιουργία του μενου με την χρήση της new_menu(ITEM **) η οποια δεχεται  2d array με struct ITEM και δημιουργεί το μενού με τα αντικέιμενα που περιέχει το  2d array.

    post_menu(my_menu); //Εμφανιση του μενου
    refresh(); //refresh της κυριας οθόνης

    while ((c = getch())) {
        switch (c) {
        case KEY_DOWN: //εαν πατησει ο χρήστης το κάτω πλήκτρο(βελάκι) τότε αυτο που γίνεται είναι οτι μετακινείται η επιλογή του μενού προς τα κάτω
            menu_driver(my_menu, REQ_DOWN_ITEM);
            break;
        case KEY_UP:
            menu_driver(my_menu, REQ_UP_ITEM); //Ομοίως για το πάνω πλήκτρο(βελάκι)
            break;
        case 10: //εαν τώρα ο χρήστης πατήσει το enter
        {
            int ind = current_item(my_menu)->index; //Καταχωρώ το index με την χρήση της current_item(MENU *) η οποία δέχεται έναν δείκτη
            //σε MENU και επιστρέφει το αντικείμενο στο οποίο βρίσκεται εκκείνη τη στιγμή ο driver.Επειδή πρόκειται για δείκτη σε struct ITEM
            //Για να κρατήσω ενα πεδίο του struct και συγκεκριμένα του index πρέπει να κάνω dereference και να επιλέξω το συγκεκριμένο πεδίο που θέλω.
            //Γι αυτο κιολας χρησιμοποιώ το ->
            /*
                Ακολουθεί απελευθέρωση της μνήμης
            */
            unpost_menu(my_menu);
            free_menu(my_menu);
            int j;
            for (j = 0; j < n_choices + 1; j++) {
                free_item(my_items[j]);
            }
            free(my_items);
            clear();
            return ind; //επιστροφή της τιμής του index
            break;
        }
        }
    }
    int j;
    /*
        Ακολουθεί απελευθέρωση της μνήμης
    */
    unpost_menu(my_menu);
    free_menu(my_menu);
    for (j = 0; j < n_choices + 1; j++) {
        free_item(my_items[j]);
    }
    free(my_items);
    return -1;
}
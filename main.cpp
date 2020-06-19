#include <iostream>
using namespace std;
#include "Player/Player.h"
#include "Items/Item/Item.h"
#include "Inventory/Inventory.h"
#include "Items/Coconut/Coconut.h"
#include "Items/Rock/Rock.h"
#include "Environment/Environment.h"
#include "GameScene/GameScene.h"

/*! \mainpage Αρχική Σελίδα
 * \section intro_sec Εισαγωγή
 * \subsection step0 Λίγα λόγια για το project.
 * Πρόκειται για ένα project παιχνιδιού περιπέτειας που δημιουργήθηκε στα πλαίσια τελικής εργασίας στο μάθημα Αντικειμενοστρεφής Προγραμματισμός.
 * Το παιχνίδι τρέχει μόνο σε λειτουργικό σύστημα <b>Linux</b> η οποία είναι και η μοναδική απαίτηση.
 * \section install_sec Οδηγείες εγκατάστασης
 *
 * \subsection step1 Τι χρειάζεστε
 * <ul>
 *  <li><a href="https://invisible-mirror.net/archives/ncurses/">NCurses Library</a></li>
 *  <li><a href="https://packages.ubuntu.com/search?keywords=build-essential">Make(build-essential)</a></li>
 *  <li><a href="https://packages.ubuntu.com/search?keywords=g%2B%2B">C++11</a></li>
 * </ul>
 *  \subsection step2 Clone Repository
 * 
 *  \subsection step3 Μετακίνιση στον κατάλογο που εγινε clone
 *  Αφου μετακινιθείται στον κατάλογο όπου έγινε clone,παρακαλώ πληκτρολογείστε <b>"make all"</b> στο τερματικό.
 *  
 *  \subsection step4 Τρέξτε το παιχνίδι.
 *  Για να τρέξετε το παιχνίδι απλά πληκτρολογείστε "./adventureGame" στο τερματικό
 *  
 */
ostream & operator<<(ostream& s, Player p){
    s<< p.getName();
    return s;
}

int main(){
    
    GameScene * scene = new GameScene;
    
    delete scene;
    
    
    
    return 0;
}
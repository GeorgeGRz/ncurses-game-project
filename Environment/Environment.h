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
        vector<Item> groundItems; /*!< Τα αντικείμενα που βρίσκονται στο πάτωμα */
        Player  playerEntity; /*!< Αντικείμενο του παίκτη */
        char ** Grid; /*!< Δισδυάστατος πίνακας που περιέχει το Grid του παιχνιδιού */
        int gridX,gridY; /*!< Οι διαστάσεις του Grid */
    public:
        static int lastID; /*!< Χρησιμοποιείται για την "διευθυνσιοδότηση" των αντικειμένων ώστε να μην υπάρχουν αντικείμενα με το ίδιο ID  */
        
        /**
         * @brief Δημιουργεί ένα αντικείμενο Environment
         * 
         */
        Environment();
        
        /**
         * @brief Δημιουργεί ένα αντικείμενο Environment με την χρήση ενός άλλου αντικειμένου Environment
         * 
         * @param env Το αντικείμενο που θα χρησιμοποιηθεί στον copy constructor
         */
        Environment(const Environment & env);
        
        /**
         * @brief Δημιουργεί ένα αντικείμενο Environment
         * 
         * @param player Αναφορά σε αντικείμενο τύπου player
         * @param X Το μήκος του Grid
         * @param Y Το πλάτος του Grid
         * @param lastid Το ID τελευταιου αντικειμένου
         */
        Environment(Player &player, int X, int Y,int lastid);
        
        /**
         * @brief Destructor
         * 
         */
        ~Environment();

        
        
        /**
         * @brief Μετακινεί τον παίκτη στις συγκεκριμένες συντεταγμένες
         * 
         * @param x 
         * @param y 
         */
        void movePlayer(int x,int y);

        /**
         * @brief Προσθέτει το αντικείμενο στον πίνακα με τα αντικείμενα του χρήστη.
         * Σημαντική σημείωση : Το αφαιρεί απο το πάτωμα πρωτού το μετακινήσει.
         * 
         * @param itemPtr Αναφορά στο αντικείμενο
         */
        void addItemToInv(Item & itemPtr);
        
        /**
         * @brief Προσθέτει το αντικείμενο στον πίνακα με τα αντικείμενα που βρίσκονται στο πάτωμα
         * 
         * @param item Αναφορά στο αντικείμενο
         */
        void addItemToGround(Item & item);
        /**
         * @brief Προσθέτει τα αντικείμενα που βρίσκονται στον vector στον πίνακα με τα αντικείμενα του πατώματος
         * 
         * @param item Αναφορά στο αντικείμενο
         */
        void addItemToGround(vector<Item > items);

        /**
         * @brief Διαγράφει το αντικείμενο απο τον πίνακα με τα αντικείμενα του χρήστη.
         * 
         * @param itemptr Το αντικείμενο που θέλουμε να διαγραφεί.
         */
        void removeFromPlayerInv(Item & itemptr);
        /**
         * @brief Διαγράφει το αντικείμενο απο τον πίνακα με τα αντικείμενα που βρίσκονται στο πάτωμα
         * 
         * @param itemptr 
         */
        void removeItemFromGround(Item & itemptr);

        
        /**
         * @brief Δημιουργεί τυχαία αντικείμενα πλήθους ίσου με την παράμετρο numberOfEntities
         * 
         * @param numberOfEntities Το πλήθος των τυχαίων αντικειμένων που επιθυμεί ο χρήστης να δημιουργήσει
         */
        void generateGrid(int numberOfEntities);

        //Getters
        vector<Item> getGroundItems(){ return groundItems;}
        DynamicArray<Item> getPlayerItems();
        Player & getPlayer(){return this->playerEntity;}
        Item & getItemAt(int X, int Y);
        char ** getGrid(){return this->Grid;}
        int getX(){return this->gridX;}
        int getY(){return this->gridY;}

        /**
         * @brief Επιστρέφει αναφορά σε αντικείμενο που βρίσκεται σε συγκεκριμένο index.
         * 
         * @param index Το index του αντικειμένου στον πίνακα αντικειμένων.
         * @return Item& Αναφορα στο αντικείμενο.
         */
        Item & getPlayerItem(int index);
        /**
         * @brief Επιστρέφει vector με τα αντικείμενα που βρίσκονται 1 θέση πανω/κατω/δεξια/αριστερα και διαγώνια απο τον χρήστη
         * 
         * @return vector<Item> 
         */
        vector<Item> getItemsNearPlayer();
        /**
         * @brief Επιστρέφει δυναμικο πίνακα που περιέχει αντικείμενα που μπορεί να δημιουργήσει ο χρήστης
         * 
         * @return DynamicArray<Item> Δυναμικός πίνακας που έχει το περιεχόμενο
         */
        DynamicArray<Item> getPlayerCraft();
        
        /**
         * @brief Μέθοδος που διαχειρίζεται τα δεδομένα που φορτώθηκαν απο αρχείο
         * 
         * @param ldata vector που περιέχει τα δεδομένα που διαβάστηκαν
         * @param isStartup Flag που είναι 1 εαν πρόκειται για startup αλλιώς 0.
         */
        void handleLoadedData(vector<Item> ldata,bool isStartup);

        

        
};


#endif

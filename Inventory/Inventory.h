#ifndef INVENTORY_H
#define INVENTORY_H
#include <iostream>
using namespace std;
#include <vector>
#include "../Items/Item/Item.h"
#include "../DynamicArray/DynamicArray.h"
/**
 * @brief Κλάση που περιέχει τα αντικείμενα του χρήστη.
 * 
 */
class Inventory{
    private:
        DynamicArray<Item> invItems; 
    public:
        Inventory();

        Inventory(const Inventory & copy);
        ~Inventory();

        /**
         * @brief Προσθέτει ενα αντικείμενο στο τέλος του δυναμικού πίνακα που περιέχει τα αντικείμενα.
         * 
         * @param item 
         */
        void addItem(Item &item);
        
        /**
         * @brief Getter για τον δυναμικό πίνακα αντικειμένων
         * 
         * @return DynamicArray<Item> 
         */
        DynamicArray<Item> getInventoryItems();
        /**
         * @brief Getter για ενα συγκεκριμένο αντικείμενο
         * 
         * @param index το index του αντικειμένου
         * @return Item& αναφορά στο αντικείμενο που βρίσκεται στη συκγεκριμένη θέση
         */
        Item & getItemAt(int index);

        /**
         * @brief Διαγράφει αντικείμενο στη συγκεκριμένη θέση που προσδιορίζεται απο την παράμετρο index
         * 
         * @param index 
         */
        void removeItemAt(int index);
        
        /**
         * @brief Επιστρέφει δυναμικο πινακα που περιέχει το πλήθος των αντικειμένων του κάθε τύπου <br>
         * Για παράδειγμα εάν έχουμε 5 αντικείμενα τύπου woodstick τότε στην αντίστοιχη θέση του τύπου woodstick θα περιέχει 5.
         * 
         * @return DynamicArray<int> 
         */
        DynamicArray<int> itemTypeCount();

        size_t getSize(){return invItems.size();}

        Inventory& operator=( Inventory & inv);
        
        /**
         * @brief Διαγράφει όλα τα αντικείμενα που βρίσκονται στον δυναμικό πίνακα
         * 
         */
        void removeAll();

        /**
         * @brief Επιστρέφει δυναμικό πίνακα που περιέχει τα πρωτογενή αντικείμενα που διαγράφτηκαν για να κάνει craft ο χρήστης.<br>
         * Εαν ο χρηστης για παραδειγμα δημιουργήσει ενα Axe απο Rock και woodstick τότε θα προσθέσει τα 2 αντικείμενα αυτα στον δυναμικό πίνακα και μετά θα τα διαγράψει.Τέλος θα επιστεψει τον πίνακα.
         * 
         * @param itemCraftedType Τύπος του παράγωγου αντικειμένου που ο χρήστης έκανε craft
         * @return DynamicArray<Item> Δυναμικος Πίνακας που περιέχει τα πρωτογενή αντικείμενα που διαγράφτηκαν.
         */
        DynamicArray<Item> removeAfterCrafting(itemType itemCraftedType);
};


#endif

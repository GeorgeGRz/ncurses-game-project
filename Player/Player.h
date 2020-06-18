#ifndef PLAYER_H
#define PLAYER_H
#include <iostream>
using namespace std;
#include "../Inventory/Inventory.h"
#include "../Vector2D/Vector2D.h"
#include <vector>
class Inventory;

class Item;
/**
 * @brief Κλάση για τον παίκτη του παιχνιδιού
 * 
 */
class Player {
private:
    string playerName;
    Vector2D<int> playerPosition;
    Inventory playerItems;
    int hunger = 100;

public:
    /**
     * @brief Constructor της κλάσης Player
     * 
     * @param position Vector2D που χρησιμοποιείται για την αρχική θέση του χρήστη
     * @param inv Αντικέιμενο Inventory που αρχικοποιεί τον σάκο του παίκτη
     * @param name Το όνομα του παίκτη
     */
    Player(Vector2D<int> position, Inventory inv, string name = "P");
    Player(const Player& copy);
    Player();
    ~Player();

    /**
     * @brief Κάνει summarize τα αντικείμενα και επιστρέφει δυναμικό πίνακα με strings που έχει τα ονόματα και τις ποσότητες του κάθε αντικειμένου
     * 
     * @return DynamicArray<string> 
     */
    DynamicArray<string> summarizeItems();
    void setHunger(int h) { hunger = h; }
    /**
     * @brief Προσθέτει αντικείμενο στον σάκο του χρήστη
     * 
     * @param item 
     */
    void addToInventory(Item& item);

    /**
     * @brief Εμφανίζει σε o/p stream τα αντικείμενα του χρήστη
     * 
     * @param stream 
     */
    void showInventory(ostream& stream);

    /**
     * @brief Επιστρέφει το επίπεδο τροφής του παίκτη
     * 
     * @return int 
     */
    int getHunger() { return hunger; }
    /**
     * @brief Getter για το ονομα του χρήστη
     * 
     * @return string 
     */
    string getName() { return this->playerName; }
    /**
     * @brief Getter για την θέση του χρήστη
     * 
     * @return const Vector2D<int>& 
     */
    const Vector2D<int>& getPosition() { return playerPosition; }
    /**
     * @brief Getter για τον σάκο με τα αντικείμενα του χρήστη
     * 
     * @return Inventory& 
     */
    Inventory& getInventory() { return playerItems; }

    /**
     * @brief Επιστρέφει αντικείμενο σε συγκεκριμένη θέση
     * 
     * @param index Η θέση του αντικειμένου
     * @return Item& 
     */
    Item& getItemAt(int index);

    void setName(string newName) { this->playerName = newName; }

    /**
     * @brief Επιστρέφει δυναμικό πίνακα που περιέχει τα αντικείμενα του χρήστη
     * 
     * @return DynamicArray<Item> 
     */
    DynamicArray<Item> getItems();

    /**
     * @brief Μετακινεί τον χρήστη στις συντεταγμένες (Χ,Υ)
     * 
     * @param X 
     * @param Y 
     */
    void moveToCoordinates(int X, int Y);
    /**
     * @brief Αντίστοιχη με την moveToCoordinates(int X, int Y) μονο που χρησιμοποιεί Vector2D<int>
     * 
     * @param newPosition 
     */
    void moveToCoordinates(Vector2D<int> newPosition);

    /**
     * @brief Αφαιρεί αντικείμενο σε συγκεκριμένη θέση
     * 
     * @param index 
     */
    void removeFromInventory(int index);

    Player operator=(const Player& copy);

    /**
     * @brief Επιστρέφει δυναμικό πίνακα που περιέχει τα αντικείμενα που μπορεί ο χρήστης να κατασκευάσει
     * 
     * @return DynamicArray<Item> 
     */
    DynamicArray<Item> getCrafted();

    /**
     * @brief Καταστρεφει όλα τα αντικείμενα που βρίσκονται στον "σακο" του χρήστη
     * 
     */
    void removeAllFromPlayer();

    /**
     * @brief Αφαιρεί τα αντικείμενα που χρησιμοποίησε ο χρήστης για να δημιουργήσει ένα νέο αντικείμενο και επιστρέφει δυναμικό πίνακα που τα περιέχει.
     * 
     * @param itemCraftedType Τύπος αντικειμένου που δημιουργήθηκε
     * @return DynamicArray<Item> Δυναμικός πίνακας που περιέχει τα αντικείμενα που χρησιμοποίησε/κατέστρεψε ο χρήστης
     */
    DynamicArray<Item> removeAfterCrafting(itemType itemCraftedType);
};

#endif

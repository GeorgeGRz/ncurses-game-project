#ifndef ITEM_H
#define ITEM_H
#include <iostream>
using namespace std;
#include "../../Vector2D/Vector2D.h"
/**
 * @brief Enumeration που χρησιμοποιείται για ευκολότερη χρήση των αντικειμένων.Ιδιαίτερα χρήσιμο όταν πρόκειται για crafting.
 * 
 */
enum itemType
{
    coconut,
    leafs,
    lighter,
    rock,
    woodstick,
    axe,
    hut,
    lightedtorch,
    opencoconut
};
/**
 * @brief Κλάση που χρησιμοποιείται για το κάθε αντικείμενο του παιχνιδιού.
 * 
 */
class Item
{
private:
    string name;
    itemType typeOfItem;
    string id;
    bool isOnFloor;
    Vector2D<int> pos;
public:
    
    Item();
    Item(string name, string id, Vector2D<int> position, bool isOnFloor = true);
    Item(const Item &copy);

    /*GETTERS*/
    inline string getName() const { return name; }
    inline string getId() const { return id; }
    inline bool getIfOnFloor() const { return isOnFloor; }
    inline itemType getType() const { return typeOfItem; }
    inline Vector2D<int> getPosition() const { return this->pos; }
    /*SETTERS*/
    inline void setType(itemType type) { this->typeOfItem = type; }
    inline void setisOnFloor(bool value) { this->isOnFloor = value; }
    
    
    virtual ~Item();

    /**
     * @brief Χρησιμοποιείται για τον συνδιασμό/crafting δύο αντικειμένων σε ενα τρίτο αντικέιμενο(παράγωγο των άλλων 2) <br>
     * <span style="color:red">Σημείωση: Εάν αποτύχει τότε επιστρέφεται ένα αντικείμενο Axe με id = null </span><br>
     * Ένας πίνακας που τα συνοψίζει είναι ο εξής: <br>
     * | Item A    | Item B  | A + B        |
     * |-----------|---------|--------------|
     * | WoodStick | Leafs   | LightedTorch |
     * | Rock      | Coconut | OpenCoconut  |
     * | WoodStick | Rock    | Axe          |
     * @param item Το αντικείμενο στο δεξί μέλος
     * @return Item Το παράγωγο αντικείμενο που δημιουργήθηκε
     */
    Item operator+(Item &item);

    
};
#endif
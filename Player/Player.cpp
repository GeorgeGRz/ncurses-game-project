#include "Player.h"
#include "../DynamicArray/DynamicArray.h"
#include "../Inventory/Inventory.h"
#include "../Items/Axe/Axe.h"
#include "../Items/Item/Item.h"
#include "../Items/LightedTorch/LightedTorch.h"
#include "../Items/OpenCoconut/OpenCoconut.h"
#include "../Vector2D/Vector2D.h"

DynamicArray<string> Player::summarizeItems()
{
    return playerItems.summarizeItems();
}

/**
 * @brief Υπερφόρτωση τελεστη << ωστε να τυπόνονται πληροφορίες αντικειμένου Item οταν χρησιμοποιείται ως δεξί μέλος οποιουδήποτε oustput stream <br>
 * Για Παράδειγμα : cout << item1  <br>
 * Όπου item1 αντικείμενο κλάσης Item
 * @param os 
 * @param item 
 * @return ostream& 
 */
ostream& operator<<(ostream& os, Item item)
{
    os << item.getId() + ";" + item.getName() + ";" + to_string(item.getType()) + ";" + to_string(item.getIfOnFloor()) + ";" + to_string(item.getPosition().x) + ";" + to_string(item.getPosition().y);
    return os;
}
Player::Player()
{
    playerName = "null";
}
DynamicArray<Item> Player::getItems()
{
    return playerItems.getInventoryItems();
}
DynamicArray<Item> Player::getCrafted()
{
    DynamicArray<Item> ret; //Δυναμικός πίνακας που περιέχει τα αντικείμενα που μπορεί να φτιάξει ο χρήστης
    int i = 0;
    int j = 0;
    DynamicArray<Item> items = getItems();
    for (auto i : items) {
        for (auto j : items) {
            //Για κάθε αντικέιμενο στα αντικείμενα του χρήστη
            if (i.getId() == j.getId())
                continue;
            Item ptr = i + j; //Δημιουργία του αντικειμένου
            if (ptr.getId() != "null")
                ret.push_back(ptr); //Εάν το αντικείμενο δημιουργήθηκε επιτυχώς,τότε προστίθεται στον δυναμικό πίνακα αντικειμένων
        }
    }
    return ret;
}
void Player::removeAllFromPlayer()
{
    playerItems.removeAll(); //Καλείται η removeAll η οποία διαγράφει ΌΛΑ τα αντικείμενα που βρίσκονται στον πίνακα
}
Player::Player(Vector2D<int> position, Inventory inv, string name)
    : playerItems(inv)
    , playerPosition(position)
{
    this->playerName = name;
}
Player::Player(const Player& copy)
    : playerItems(copy.playerItems)
{
    this->playerPosition = copy.playerPosition;
    this->playerName = copy.playerName;
}
void Player::addToInventory(Item& itm)
{
    playerItems.addItem(itm);
}
void Player::moveToCoordinates(int X, int Y)
{
    this->playerPosition.x = X;
    this->playerPosition.y = Y;
}
Player Player::operator=(const Player& copy)
{
    if (this == &copy)
        return *this;
    else {
        this->playerName = copy.playerName;
        this->playerPosition = copy.playerPosition;
    }
    return *this;
}
void Player::showInventory(ostream& os)
{
    for (auto x : playerItems.getInventoryItems()) {
        cout << x; //Έχει υπερφορτωθεί παραπάνω
    }
}
void Player::removeFromInventory(int index)
{
    this->playerItems.removeItemAt(index); //Καλείται η removeItemAt η οποία αφαιρεί αντικείμενο σε συγκεκριμένο index
}

Item& Player::getItemAt(int index)
{
    return this->playerItems.getItemAt(index);
}

DynamicArray<Item> Player::removeAfterCrafting(itemType itemCraftedType)
{
    return playerItems.removeAfterCrafting(itemCraftedType);
}

Player::~Player()
{

    ;
}
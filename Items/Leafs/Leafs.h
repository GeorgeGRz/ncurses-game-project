#ifndef Leafs_H
#define Leafs_H
#include "../Item/Item.h"

/**
 * @brief Κλάση αντικειμένου Leafs <br>
 * Χρησιμοποιείται για τα συμβολίσει Φύλλο
 */
class Leafs : public Item{
    private:

    public:
        Leafs();
        Leafs(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        Leafs(const Leafs& copy);

        ~Leafs();
};
#endif
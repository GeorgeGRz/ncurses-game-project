#ifndef Lighter_H
#define Lighter_H
#include "../Item/Item.h"
/**
 * @brief Κλάση αντικειμένου Lighter <br>
 * Χρησιμοποιείται για τα συμβολίσει αναπτήρα.
 */
class Lighter : public Item{
    private:

    public:
        Lighter();
        Lighter(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        Lighter(const Lighter& copy);

        ~Lighter();
};
#endif
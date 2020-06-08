#ifndef Coconut_H
#define Coconut_H
#include "../Item/Item.h"

/**
 * @brief Κλάση αντικειμένου Coconut <br>
 * Χρησιμοποιείται για τα συμβολίσει Καρύδα
 */
class Coconut : public Item{
    private:

    public:
        Coconut();
        Coconut(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        Coconut(const Coconut& copy);

        ~Coconut();
};
#endif
#ifndef LightedTorch_H
#define LightedTorch_H
#include "../Item/Item.h"

/**
 * @brief Κλάση αντικειμένου LightedTorch <br>
 * Χρησιμοποιείται για τα συμβολίσει αναμμένο πυρσό.
 */
class LightedTorch : public Item{
    private:

    public:
        LightedTorch();
        LightedTorch(string name,string id, Vector2D<int>pos,bool isOnFloor=true);
        LightedTorch(const LightedTorch& copy);

        ~LightedTorch();
};
#endif
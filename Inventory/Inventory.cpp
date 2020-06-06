#include "Inventory.h"

Inventory::Inventory()
{
    ;
}

Inventory::Inventory(const Inventory &copy) : invItems(copy.invItems)
{
    ;
}

Item &Inventory::getItemAt(int index)
{
    return invItems[index];
}
Inventory &Inventory::operator=(Inventory &inv)
{
    invItems = inv.invItems;
    return *this;
}

void Inventory::addItem(Item &item)
{
    invItems.push_back(item);
}
void Inventory::removeAll()
{

    invItems.clear();
}
void Inventory::removeItemAt(int index)
{
    int i = 0;
    for (DynamicArray<Item>::iterator it = invItems.begin(); it != invItems.end();)
    {
        if (i == index)
        {
            it = invItems.erase(it);
        }
        else
        {
            it++;
        }
        i++;
    }
}
DynamicArray<int> Inventory::itemTypeCount()
{
    DynamicArray<int> dArray;
    dArray.push_back(0); //Θα χρησιμοποιηθεί για το πλήθος αντικειμένων lighter. Το ίδιο ισχύει και γι ατους άλλους τύπους
    dArray.push_back(0); //woodStick
    dArray.push_back(0); //Leafs
    dArray.push_back(0); //rock
    dArray.push_back(0); //coconut
    dArray.push_back(0); //axe
    dArray.push_back(0); //openCoconut
    dArray.push_back(0); //lightedTorch
    for (auto x : invItems)
    {
        //Για καθε αντικείμενο στη λίστα των αντικειμένων εάν ο τύπος του είναι πχ lighter τότε αυξάνουμε κατα 1 το περιεχόμενο της θέσης 0 του δυναμικού πίνακα dArray 
        //Εάν είναι woodstick τότε το περιεχόμενο της 1 κ.ο.κ
        if (x.getType() == lighter)
        {
            dArray[0]++;
        }
        else if (x.getType() == woodstick)
        {
            dArray[1]++;
        }
        else if (x.getType() == leafs)
        {
            dArray[2]++;
        }
        else if (x.getType() == rock)
        {
            dArray[3]++;
        }
        else if (x.getType() == coconut)
        {
            dArray[4]++;
        }
        else if (x.getType() == axe)
        {
            dArray[5]++;
        }
        else if (x.getType() == opencoconut)
        {
            dArray[6]++;
        }
        else if (x.getType() == lightedtorch)
        {
            dArray[7]++;
        }
    }
    return dArray;
}
DynamicArray<Item> Inventory::getInventoryItems()
{
    //Δημιουργείται και επιστρέφεται αντίγραφο των αντικειμένων που περιέχει η "τσαντα" του χρήστη
    DynamicArray<Item> cpArray;
    cpArray = invItems;
    return cpArray;
}
Inventory::~Inventory()
{
    ;
}
DynamicArray<Item> Inventory::removeAfterCrafting(itemType itemCraftedType)
{
    DynamicArray<Item> itemsRemoved;//ΔΥναμικος πινακας που περιεχει τα αντικειμενα τα οποια ο χρηστης χρησιμοποιησε για να φτιαξει το παράγωγο αντικείμενο

    int count = 0;
    /*Flags που χρησιμοποιούνται για να ξέρω εάν εχει ήδη διαγραφεί κάποιο αντικείμενο ενος συγκεκριμένου τύπου */
    bool rockFlag = false;
    bool cocFlag = false;
    bool leafFlag = false;
    bool woodFlag = false;

    int size = invItems.size();
    int count2 = 0;
    for (DynamicArray<Item>::iterator i = invItems.begin(); i != invItems.end();)
    {
        if (itemCraftedType == axe && (invItems[count2].getType() == rock && rockFlag == false))
        {
            /*Εάν ο χρήστης δημιούργησε τσεκούρι ΚΑΙ ο τυπος του αντικειμένου είναι Πετρα(rock) ΚΑΙ ΔΕΝ έχει διαγράψει αντικείμενο πέτρας πρίν
              Τότε προσθετει το αντικείμενο που βρισκεται στη θεση count2 στον πινακα διεγραμμένων αντικειμένων, διαγράφει το τορινό αντικείμενο στο οποιο δείχνει ο iterator i
              Στη συνέχεια βάζει το Flag rockFlag να είναι ΑΛΗΘΗΣ ωστε να μην ξαναδιαγράψει στις επόμενες επαναλήψεις αντικείμενο τύπου Πέτρα
              Τέλος αυξάνει το count κατα 1.
              Το count χρησιμοποιείται για να σταματάει η επανάληψη μόλις ο χρήστης έχει διαγράψει 2 αντικείμενα οποιουδήποτε τύπου.Αυτο γιατι ΟΛΑ τα παράγωγα παράγονται αυστηρώς απο 2 μόνο πρωτογενή αντικείμενα.
              Το ίδιο ακριβώς ισχύει για τους υπόλοιπους τύπους.
            */
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            rockFlag = true;
            count++;
        }
        else if (itemCraftedType == axe && (invItems[count2].getType() == woodstick && woodFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            woodFlag = true;
            count++;
        }
        else if (itemCraftedType == opencoconut && (invItems[count2].getType() == coconut && cocFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            cocFlag = true;
            count++;
        }
        else if (itemCraftedType == opencoconut && (invItems[count2].getType() == rock && rockFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            rockFlag = true;
            count++;
        }
        else if (itemCraftedType == lightedtorch && (invItems[count2].getType() == leafs && leafFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            leafFlag = true;
            count++;
        }
        else if (itemCraftedType == lightedtorch && (invItems[count2].getType() == woodstick && woodFlag == false))
        {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            woodFlag = true;
            count++;
        }
        else
        {
            i++;
            count2++;
        }
        if (count == 2)
            break;
    }

    return itemsRemoved;
}
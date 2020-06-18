#include "Inventory.h"

Inventory::Inventory()
{
    ;
}

Inventory::Inventory(const Inventory& copy)
    : invItems(copy.invItems)
{
    ;
}

Item& Inventory::getItemAt(int index)
{
    return invItems[index];
}
Inventory& Inventory::operator=(Inventory& inv)
{
    invItems = inv.invItems;
    return *this;
}

void Inventory::addItem(Item& item)
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
    for (DynamicArray<Item>::iterator it = invItems.begin(); it != invItems.end();) {
        if (i == index) {
            it = invItems.erase(it);
        } else {
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
    for (auto x : invItems) {
        //Για καθε αντικείμενο στη λίστα των αντικειμένων εάν ο τύπος του είναι πχ lighter τότε αυξάνουμε κατα 1 το περιεχόμενο της θέσης 0 του δυναμικού πίνακα dArray
        //Εάν είναι woodstick τότε το περιεχόμενο της 1 κ.ο.κ
        if (x.getType() == lighter) {
            dArray[0]++;
        } else if (x.getType() == woodstick) {
            dArray[1]++;
        } else if (x.getType() == leafs) {
            dArray[2]++;
        } else if (x.getType() == rock) {
            dArray[3]++;
        } else if (x.getType() == coconut) {
            dArray[4]++;
        } else if (x.getType() == axe) {
            dArray[5]++;
        } else if (x.getType() == opencoconut) {
            dArray[6]++;
        } else if (x.getType() == lightedtorch) {
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
DynamicArray<string> Inventory::summarizeItems()
{
    DynamicArray<string> items;
    DynamicArray<int> itemCount = itemTypeCount(); //Αποθηκεύεται το πλήθος αντικειμένων του κάθε τύπου
    DynamicArray<bool> flags({ false, false, false, false, false, false, false, false });
    DynamicArray<int> indexOfLast({0, 0, 0, 0, 0, 0, 0, 0});
    //Για κάθε τύπο αντικειμένων, δημιουργείται μια θέση σε δυναμικό πίνακα bool οπου είναι ΨΕΥΔΉΣ
    //Αυτο θα χρησιμοποιηθεί ωστε να ξέρουμε εάν έχει ξαναυπολογιστεί πλήθος αντικειμένων για τον συγκεκριμένο τύπο.
    //Έτσι αποφεύγεται να χρησιμοποιηθεί casting.
    for (auto x : invItems) {
        string print;
        if (x.getType() == lighter && flags[0] == false) {
            //Εαν ο τύπος είναι lighter και ΔΕΝ έχει ξαναυπολογιστεί και προστεθεί το print στον πίνακα items
            print = x.getName() + " x" + to_string(itemCount[0]);
            flags[0] = true;
            indexOfLast[0]++;
            items.push_back(print);
        } else if (x.getType() == woodstick && flags[1] == false) {
            //Ομοια για αντικείμενο woodstick
            print = x.getName() + " x" + to_string(itemCount[1]);
            flags[1] = true;
            indexOfLast[1]++;
            items.push_back(print);
        } else if (x.getType() == leafs && flags[2] == false) {
            print = x.getName() + " x" + to_string(itemCount[2]);
            flags[2] = true;
            indexOfLast[2]++;
            items.push_back(print);
        } else if (x.getType() == rock && flags[3] == false) {
            print = x.getName() + " x" + to_string(itemCount[3]);
            flags[3] = true;
            indexOfLast[3]++;
            items.push_back(print);
        } else if (x.getType() == coconut && flags[4] == false) {
            print = x.getName() + " x" + to_string(itemCount[4]);
            flags[4] = true;
            indexOfLast[4]++;
            items.push_back(print);
        } else if (x.getType() == axe && flags[5] == false) {
            print = x.getName() + " x" + to_string(itemCount[5]);
            flags[5] = true;
            indexOfLast[5]++;
            items.push_back(print);
        } else if (x.getType() == opencoconut && flags[6] == false) {
            print = x.getName() + " x" + to_string(itemCount[6]);
            flags[6] = true;
            indexOfLast[6]++;
            items.push_back(print);
        } else if (x.getType() == lightedtorch && flags[7] == false) {
            print = x.getName() + " x" + to_string(itemCount[7]);
            flags[7] = true;
            indexOfLast[7]++;
            items.push_back(print);
        }
    }
    return items;
}
DynamicArray<Item> Inventory::removeAfterCrafting(itemType itemCraftedType)
{
    DynamicArray<Item> itemsRemoved; //ΔΥναμικος πινακας που περιεχει τα αντικειμενα τα οποια ο χρηστης χρησιμοποιησε για να φτιαξει το παράγωγο αντικείμενο

    int count = 0;
    /*Flags που χρησιμοποιούνται για να ξέρω εάν εχει ήδη διαγραφεί κάποιο αντικείμενο ενος συγκεκριμένου τύπου */
    bool rockFlag = false;
    bool cocFlag = false;
    bool leafFlag = false;
    bool woodFlag = false;

    int size = invItems.size();
    int count2 = 0;
    for (DynamicArray<Item>::iterator i = invItems.begin(); i != invItems.end();) {
        if (itemCraftedType == axe && (invItems[count2].getType() == rock && rockFlag == false)) {
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
        } else if (itemCraftedType == axe && (invItems[count2].getType() == woodstick && woodFlag == false)) {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            woodFlag = true;
            count++;
        } else if (itemCraftedType == opencoconut && (invItems[count2].getType() == coconut && cocFlag == false)) {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            cocFlag = true;
            count++;
        } else if (itemCraftedType == opencoconut && (invItems[count2].getType() == rock && rockFlag == false)) {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            rockFlag = true;
            count++;
        } else if (itemCraftedType == lightedtorch && (invItems[count2].getType() == leafs && leafFlag == false)) {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            leafFlag = true;
            count++;
        } else if (itemCraftedType == lightedtorch && (invItems[count2].getType() == woodstick && woodFlag == false)) {
            itemsRemoved.push_back(invItems[count2]);
            invItems.erase(i);
            woodFlag = true;
            count++;
        } else {
            i++;
            count2++;
        }
        if (count == 2)
            break;
    }

    return itemsRemoved;
}
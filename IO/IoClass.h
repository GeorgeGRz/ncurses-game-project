#ifndef IOCLASS_H
#define IOCLASS_H
#include <ncurses.h>
#include <vector>
#include <iostream>
#include "../Player/Player.h"

using namespace std;
class Item;
class Environment;
/**
 * @brief Κλάση διαχείρησης εισοδου-εξόδου καθώς και διαχείρησης οθόνης.
 * 
 */
class IoClass{
    private:

    public:
        IoClass();
        /**
         * @brief Διαβάζει το αρχείο και στη συνέχεια φορτώνει τα αντικείμενα σε vector
         * 
         * @param fileName Το ονομα του αρχείου οπου θα προσπελάσει
         * @param id Αναφορά σε ακέραιο αριθμό,χρησιμοποιείται για να υπολογίσει το τελευταίο id
         * @return vector<Item> Container οπου περιέχει τα αντικείμενα που διαβάστηκαν
         */
        vector<Item> loadFromFile(string fileName,int & id);
        /**
         * @brief Αντίστοιχα αποθηκεύει τα αντικείμενα που υπάρχουν στο env <br>
         * Γενικά η γραμμογράφηση του αρχείου είναι ώς εξής: <br>
         * <b><itemId>;<itemName>;<itemTypeId>;<itemOnFloor>;<itemXpos>;<itemYpos></b>
         * 
         * | itemId                 | itemName                  | itemTypeId                       | itemOnFloor                          | item x position | item y position |
         * |------------------------|---------------------------|----------------------------------|--------------------------------------|-----------------|-----------------|
         * | Το ID του αντικειμένου | Το όνομα του αντικειμένου | Το ID του τύπου του αντικειμένου | Flag για το εαν βρισκεται στο πατωμα | Θέση Χ          | Θέση Υ          |
         * 
         * @param fileName Το ονομα του αρχείου οπου θα προσπελάσει
         * @param env Αναφορά σε μεταβλητή τύπου Environment
         */
        void saveToFile(string fileName,Environment & env);

        /**
         * @brief Διαβάζει string απο το πληκτρολόγιο
         * 
         * @return string Το string που διαβάστηκε
         */
        string readString();

        /**
         * @brief Εμφανίζει σε συγκεκριμένες συντεταγμένες της οθόνης ένα αλφαριθμητικό καθώς και με προκαθορισμένη ταχύτητα
         * 
         * @param x Η συντεταγμένη Χ
         * @param y Η συντενταγμένη Y
         * @param stringToPrint Το αλφαριθμητικό που θα εμφανιστεί
         * @param a_args Χρησιμοποιείται για να εμφανίζονται δυναμικά περιεχόμενα μεταβλητών(πχ οπως η printf εχει το %s και το %d) Οι μονες που υποστηρίζονται είναι οι %s και %d.
         * @param speed Χρησιμοποιείται για την ταχύτητα εμφάνισης των χαρακτήρων.
         */
        void printToCoordsAnimated(int x, int y,string stringToPrint,std::initializer_list<string> a_args,int speed);

        /**
         * @brief Δέχεται vector με string και εμφανίζει τα περιεχόμενα με μορφή μενού
         * 
         * @param selections 
         * @return int Το index της επιλογής που έγινε, 0 για την 1η επιλογή, 1 για την 2η επιλογή, 2 για την 3η κλπ..
         */
        int showMenu(std::vector<string> selections);

        /**
         * @brief Εμφανίζει το περιβάλλον(αντικείμενα, παίκτη κλπ)
         * 
         * @param env 
         */
        void printEnvironment(Environment& env);

        /**
         * @brief Εμφάνιση στατιστικών του παίκτη(Επίπεδο πείνας)
         * 
         * @param player Αναφορά σε αντικείμενο Player
         */
        void printPlayerStats(Player& player);

        /**
         * @brief Destroy the Io Class object
         * 
         */
        ~IoClass();

        /**
         * @brief Getter για το μέγιστο Χ της οθονης
         * 
         * @return int μέγιστο Χ της οθονης
         */
        int getMaxX();
        /**
         * @brief Getter για το μέγιστο Υ της οθονης
         * 
         * @return int μέγιστο Υ της οθονης
         */
        int getMaxY();

        /**
         * @brief Διαβάζει ένανα χαρακτήρα απο το πληκτρολόγιο και τον επιστεφει
         * 
         * @return int Χαρακτήρας που διαβάστηκε
         */
        int getInput();   


};

#endif
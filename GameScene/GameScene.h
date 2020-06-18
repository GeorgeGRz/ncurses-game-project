#ifndef GAMESCENE_H
#define GAMESCENE_H
#include <chrono>
#include <iostream>
using namespace std;

/**
 * @brief Τα states απο τα οποία "περνάει" το παιχνίδι.Προς το παρόν δεν χρησιμοποιείται κάπου,ωστόσο έχει προστεθεί για το μέλλον.
 * 
 */
enum GameState { initializing,
    waiting,
    running,
    saving,
    loading,
    exiting };

class Environment;
class IoClass;

/**
 * @brief Κλάση διαχείρησης κύριας σκηνής του παιχνιδιού
 * 
 */
class GameScene {
private:
    GameState state; /*!< Το state του παιχνιδιού */
    IoClass* ioManager; /*!< Διαχειριστής εισόδου-εξόδου */
    Environment* env; /*!< Δείκτης στο περιβάλλον του παιχνιδιού(περιέχει παίκτη,grid,αντικείμενα) */
    bool isOver = false; /*!< Flag που χρησιμοποιείται για τον τερματισμό του παιχνιδιού */
    bool continueAfterEnd = false; /*!< Flag που χρησιμοποιείται για την συνέχεια αφού τερματιστεί το παιχνίδι(ο χρήστης craftαρει ενα αντικείμενο) */
    bool endByMenu = false; /*!< Flag που χρησιμοποιείται για τον τερματισμό του παιχνιδιού απο το κύριως μενού */
public:
    GameScene();
    GameScene(IoClass* ioManager, Environment* env);
    GameScene(const GameScene& copy);

    GameState getState() { return state; }

    /**
         * @brief Ελέγχει το επίπεδο τροφής του παίκτη και κάθε λεπτό το μειώνει κατα 10.
         * 
         * @param timePassed Αναφορά σε αντικείμενο chrono::duration που χρησιμοποιείται για να κρατάει τον χρόνο που πέρασε απο τον προηγούμενο έλεγχο
         * @param start Αναφορά σε αντικείμενο std::chrono::time_point<std::chrono::system_clock> χρησιμοποιείται ώστε να κρατάει την τωρινή ώρα, δηλαδή την ώρα του ελέγχου.
         */
    void checkHunger(chrono::minutes::rep& timePassed, chrono::_V2::system_clock::time_point& start);
    void setState(GameState state) { this->state = state; }
    /**
         * @brief Εμφανίζει την αρχική οθόνη και αφού διαβάσει απο το πληκτρολόγιο το όνομα του χρήστη το επιστρέφει.
         * 
         * @return string Όνομα χρήστη
         */
    string startupScreen();
    /**
         * @brief Κύρια μέθοδος του παιχνιδιού
         * 
         */
    void Play();

    /**
         * @brief Κύρια μέθοδος που διαχειρίζεται τα πλήκτρα.
         * 
         * @param c Κωδικός πλήκτρου(ποίο πλήκτρο πατήθηκε)
         */
    void parseSelection(int c);

    /**
         * @brief Μέθοδος που διαχειρίζεται το κύριο μενού με βάση την επιλογή που έκανε ο χρήστης.
         * 
         * @param menuSelection Επιλογή του μενού που έκανε ο χρήστης.
         */
    void handleMainMenu(int menuSelection);

    /**
         * @brief Μέθοδος που διαχειρίζεται το μενού επιλογής αντικειμένου που θα αφήσει ο χρήστης στο περιβάλλον, αφου πρώτα ελέγξει εάν υπάρχει ελεύθερος χώρος.
         * 
         * @param menuSelection Index του αντικειμένου που θα αφήσει στο πάτωμα(1 για το 1ο, 2 για το 2ο, κ.ο.κ)
         */
    void handleInventoryMenu(int menuSelection);

    /**
         * @brief Μέθοδος που  διαχειρίζεται το crafting.
         * 
         * @param menuSelection Index του αντικειμένου που θα κάνει craft(1 για το 1ο, 2 για το 2ο, κ.ο.κ)
         */
    void handleCraftingMenu(int menuSelection);

    /**
         * @brief Μέθοδος που διαχειρίζεται το μενού τερματισμού
         * 
         * @param menuSelection Index της επιλογής του χρήστη.
         */
    void handleEndingMenu(int menuSelection);

    ~GameScene();
};

#endif

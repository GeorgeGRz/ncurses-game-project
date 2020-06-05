#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <stdexcept>
#include <algorithm>
#include <iostream>
using namespace std;
template <typename T>
/**
 * @class
 * @brief Κλάση δυναμικόυ πίνακα που χρησιμοποιεί templates.Για την υλοποίηση συμβουλεύθηκα το βιβλίο του Stroustroup "Προγραμματισμός με τη C++".
 * 
 * Μια πολύ βασική υλοποίηση δυναμικού πίνακα που έχει αρκετές ομοιότητες με το διάνυσμα της STL.
 */
class DynamicArray
{
private:
    T *m_data;              /*!< Ο ίδιος ο δείκτης των δεδομένων */
    size_t m_capacity = 10; /*!< Μεταβλητή που χρησιμοποιείται για να δεσμεύουμε παραπάνω δεδομένα απο τα πραγματικά του δυναμικου πίνακα */
    size_t m_size = 0;      /*!< Μεταβλητή που κρατάει το πραγματικό μέγεθος του πίνακα */
public:
    using size_type = size_t; /*!< Χρησιμοποιείται σαν ψευδώνυμο για το size_t */
    using iterator = T *;     /*!< Χρησιμοποιείται σαν ψευδώνυμο για το T* */
    using reference = T &;    /*!< Χρησιμοποιείται σαν ψευδώνυμο για το reference */

    friend void swap(DynamicArray<T> &lhs, DynamicArray<T> &rhs)
    {
        lhs.swap(rhs);
    }
    /**
     * @brief 
     * Χρησιμοποείται για να κάνει swap τα δεδομένα του αντικειμένου που το καλεί με τα δεδομένα της παραμέτρου.
     *
     * 
     * @param rhs Ο δυναμικός πίνακας με τον οποίον θα κάνει swap
     */
    void swap(DynamicArray<T> &rhs)
    {
        std::swap(m_size, rhs.m_size);
        std::swap(m_capacity, rhs.m_capacity);
        std::swap(m_data, rhs.m_data);
    }
    /**
     * @brief Δημιουργία ενός νέου αντικειμένου DynamicArray.Εάν κληθεί αυτός ο constructor τότε δεσμεύω χώρο χρησιμοποιόντας το m_capacity.
     * Δηλαδή δεσμεύει χώρο ακόμα και εάν ο δυναμικός πίνακας είναι κενός.
     * 
     */
    inline DynamicArray() noexcept
    {
        m_data = new T[m_capacity];
    }
    /**
     * @brief Δημιουργία ενός νέου αντικειμένου DynamicArray.Παίρνει ώς όρισμα ένα initializer_list και αυτό για να γίνεται initialize dynamicVector<int> a({1,3,2});
     * 
     * @param init Η initializer_list με την οποία θα γίνει η αρχικοποίηση
     */
    inline DynamicArray(std::initializer_list<T> init)
    {
        size_type count = init.size(); //Το μέγεθος πρέπει να είναι ίδιο με αυτό της initializer_list
        m_size = 0;                    //Αρχικοποίηση του m_size σε 0
        m_capacity = count + count / 2 + 1;
        m_data = new T[m_capacity]; //Δεσμεύω μνήμη για τα δεδομένα.Το πόσο θα δεσμευθεί έχει να κάνει με το m_capacity
        for (const T &elem : init)
            m_data[m_size++] = elem; //Για κάθε αντικείμενο στη λίστα αντιγράφω ένα προς ένα στον πίνακα
    }
    /**
     * @brief Υπερφόρτωση του τελεστή =.
     * 
     * @param origin Το αντικείμενο με το οποίο θα γίνει η υπερφόρτωση
     * @return DynamicArray<T>& 
     */
    inline DynamicArray<T> &operator=(const DynamicArray<T> &origin)
    {
        DynamicArray<T> cp(origin); //καλείται ο copy constructor
        swap(cp);                   //Καλείται η swap ώστε να αντιγραφούν τα δεδομένα του προσωρινού αντίγραφου στο αντικείμενο που την κάλεσε.
        return *this;               //Επιστρέφεται το αντικείμενο που περιέχει τα νέα δεδομένα.
    }
    /**
     * @brief Δημιουργία ενός νέου αντικειμένου DynamicArray χρησιμοποιόντας copy constructor.
     * 
     * @param origin Reference στο αντικείμενο απο το οποίο θα αντιγραφούν τα δεδομένα
     */
    inline DynamicArray(const DynamicArray<T> &origin)
    {
        m_size = origin.m_size;         //Το μέγεθος του πίνακα ισούται με το μέγεθος του πίνακα της παραμέτρου
        m_capacity = origin.m_capacity; //Ομοίως με τον δεσμευμένο κώδικα
        m_data = new T[m_capacity];     //Δεσμεύω εκ νέου χώρο
        for (size_t i = 0; i < m_size; i++)
            m_data[i] = origin.m_data[i]; //Αντιγραφή στοιχείο προς στοιχείο
    }
    /**
     * @brief Δημιουργία ενός νέου αντικειμένου DynamicArray χρησιμοποιόντας copy constructor.
     * 
     * @param origin Rvalue reference στο αντικείμενο απο το οποίο θα αντιγραφούν τα δεδομένα
     */
    inline DynamicArray(DynamicArray<T> &&origin) : m_data(origin.m_data), m_capacity(origin.m_capacity), m_size(origin.m_size)
    {
        /*
            Εάν κληθεί ο copy constructor ώς rvalue(προσωρινά), τότε δεν χρειάζεται να αντιγραφούν όλα τα δεδομένα ενα προς ένα, δεν χρειάζεται δηλαδή να γίνει deep copy
            Το μόνο που χρειάζεται ειναι να "κλεψουμε" τα δεδομένα αυτά.
        */
        origin.m_data = nullptr;
        origin.m_size = 0;
    }
    /**
     * @brief Χρησιμοποιείται για να αδειάσει ο δυναμικός πίνακας.Δεν είναι ο destructor.
     * 
     */
    inline void clear() noexcept
    {

        for (size_t i = 0; i < m_size; i++)
            m_data[i].~T(); //Καλείται ο destructor του κάθε στοιχείου.Θα μπορουσε να χρησιμοποιηθεί και το delete.
        m_size = 0;         //Ορισμός του μεγέθους(πραγματικού) σε 0.
    }
    /**
     * @brief Χρησιμοποιείται απο την push_back κυρίως για να προσθέτει αντικείμενα στο τέλος του πίνακα.
     * 
     * @tparam Args Ο τύπος των αντικειμένων που θα προστεθεί
     * @param args Αναφορά στα αντικείμενα που θα προστεθούν
     * @return DynamicArray<T>::reference Επιστρέφει αναφορά στον πίνακα
     */
    template <typename... Args>
    inline typename DynamicArray<T>::reference emplace_back(Args &&... args)
    {
        /*
            Πρωτού προχωρήσω στην ανάλυση του κώδικα, θα ήθελα να πώ λίγα πράγματα σχετικά με το διπλο reference η αλλιώς το && που υπάρχει σαν παράμετρος.Αυτο ονομάζεται rvalue reference.
            Η έκδοση της c++11 πρόσθεσε αυτο το feature το οποίο χρησιμοποιείται για να ελαχιστοποιήσει τα προβλήματα που δημιουργούν οι άσκοπες αντιγραφές των αντικειμένων χωρίς να
            χρειαστεί να αλλάξει η επικεφαλίδα της μεθόδου.Αυτοί οι μηχανισμοί ονομάζονται και move semantics και βασίζονται στο να μπορούμε να δούμε την διαφορά μεταξύ αντιγραφής 
            ενος αντικειμένου lvalue και αντιγραφής ενός αντικειμένου rvalue(προσωρινού). Χρησιμοποιείται δηλαδή για λόγους performance κατι που χρειάζεται να σκεφτούμε όταν γράφουμε κώδικα τέτοιου
            βεληνεκούς(όπως δηλαδή ένας δυναμικος πίνακας που περιέχει δεδομένα).
            Για καλύτερη κατανόηση μπορείτε να δείτε και τον copy constructor οπου πάλι χρησιμοποιείται &&.
            
        */
        if (m_size == m_capacity) //Εάν το πραγματικό μέγεθος του πίνακα φτάσει το extra μεγεθος τότε πρέπει να αυξηθεί το extra.
        {
            m_capacity += m_capacity / 2 + 1; //Αυξάνεται το extra
            reallocate();                     //Καλείται η reallocate που θα δεσμεύσει παραπάνω χώρο.
        }
        return m_data[m_size++] = std::move(T(std::forward<Args>(args)...));
        //Αρχικά γίνεται perfect forwarding.Δηλαδή αυτο σημαίνει οτι η template συνάρτηση μπορεί να περάσει
        //τις παραμέτρους της σε μία άλλη συνάρτηση χωρίς να χάσει την lvalue/rvalue "φυση" της και αυτό γίνεται χρησιμοποιόντας την
        //forward().Στη συνέχεια μέσω της move τη μετατρέπουμε σε rvalue.Τέλος εισάγουμε το αποτελεσμα αυτο στο m_data και αυξάνουμε το μέγεθος των δεδομένων κατα 1.
    }
    /**
     * @brief Προσθέτει ένα αντικείμενο στο τέλος του πίνακα
     * 
     * @param val Το αντικείμενο που θέλουμε να προστεθεί.
     */
    inline void push_back(const T &val)
    {
        emplace_back(val);
    }
    /**
     * @brief Διαγράφω ένα συγκεκριμένο αντικείμενο χρησιμοποιόντας iterator(T*)
     * 
     * @param iter Ο iterator που θα χρησιμοποιηθεί για να διαγραφεί το αντικείμενο απο τον πίνακα.
     * @return DynamicArray<T>::iterator Επιστρέφει iterator όπως ακριβώς γίνεται και στον vector της STL
     */
    DynamicArray<T>::iterator erase(DynamicArray<T>::iterator iter)
    {
        iterator itt = &m_data[iter - m_data]; //Ο iterator επιστροφής. Στην αρχή τον αρχικοποιόυμε με την διεύθυνση του αντικειμένου
        //που βρίσκεται στη θέση iter - m_data
        itt->~T();            //καλείται ο destructor
        if (itt + 1 != end()) //Εάν το επόμενο είναι διάφορο του end (δηλαδή δεν πρόκειται για το τελευταίο προσπελάσημο αντικείμενο)
        {
            move_storage(itt, itt + 1, m_size - (itt - m_data));
            m_size -= 1;
        }
        else //Εάν πρόκεται για το τελευταίο
        {
            itt = &m_data[m_size - 2]; //Εισαγωγή της διεύθυνσης του τελευταίου προσπελάσημου αντικειμένου στον itt
            pop_back();                //καλούμε την pop_back
        }

        return itt; //Επιστροφή του itt
    }
    /**
     * @brief Χρησιμοποιείται απο την ίδια την κλάση για να δεσμεύσει περισσότερο χώρο.
     * 
     */
    inline void reallocate()
    {
        T *new_storage = new T[m_capacity];        //Το m_capacity θα πρέπει να έχει αλλάξει πρωτού κληθεί
        move_storage(new_storage, m_data, m_size); //Καλείται η move_storage(βλ παρακάτω για την λειτουργία και τον σκοπό)
        delete[] m_data;                           //απελευθερώνεται η παλιά μνήμη που είχε δεσμευθεί για να μην γίνει memory leak
        m_data = new_storage;                      //Ο δείκτης των δεδομένων αλλάζει και τώρα δείχνει στην νέα μνήμη
    }
    /**
     * @brief Χρησιμοποιείται για να "μεταφέρει" δεδομένα χρησιμοποιόντας την move.
     * 
     * @param dest Διεύθυνση προορισμόυ
     * @param from Διεύθυνση πηγής
     * @param n Πλήθος/Μέγεθος 
     */
    void move_storage(T *dest, T *from, size_type n)
    {
        if (dest < from)
        {
            //Εάν ο προορισμός είναι μικρότερος απο την πηγή(μιλάμε για δείκτες οπότε θέλει λίγο προσοχή αυτη η έννοια)
            T *_dest = dest, *_from = from; //Δημιουργία δυό νέων δεικτών που δείχνουν ακριβώς στην ίδια διεύθυνση με τους dest και from
            for (size_t i = 0; i < n - 1; i++)
                *_dest++ = std::move(*_from++); //Καλείται η move η οποία "μεταφέρει" τους πόρους απο την from στην dest και στη συνέχεια τις αυξάνει και τις δύο.
                                                //Η move επίσης παράγει μια  xvalue έκφραση η οποία σηματοδοτεί την παράμετρο t.Μοιάζει αρκετά με static_cast σε μια αναφορά rvalue.
        }
        else if (dest > from)
        { //Ακριβώς η ίδια λειτουργία μόνο που αυτή τη φορά λειτουργεί κάπως ανάποδα.
            T *_dest = dest + n - 1, *_from = from + n - 1;
            for (size_t i = n; i > 0; i--)
                *_dest-- = std::move(*_from--);
        }
        else
            return;
    }
    /**
     * @brief Επιστρέφει iterator του πρώτου αντικειμένου
     * 
     * @return DynamicArray<T>::iterator iterator που δείχνει στο πρώτο αντικείμενο
     */
    inline typename DynamicArray<T>::iterator begin() noexcept
    {
        return m_data;
    }

    /**
     * @brief Επιστρέφει iterator του τελευταίου αντικειμένου
     * 
     * @return DynamicArray<T>::iterator iterator που δείχνει στο τελευταίο αντικείμενο
     */
    inline typename DynamicArray<T>::iterator end() const noexcept
    {
        return m_data + m_size;
    }
    /**
     * @brief Getter μεγέθους(πραγματικού)
     * 
     * @return size_t Το πραγματικό μέγεθος
     */
    size_t size()
    {
        return this->m_size;
    }

    /**
     * @brief Getter μεγέθους(extra)
     * 
     * @return size_t Το extra μέγεθος.
     */
    size_t capacity()
    {
        return this->m_capacity;
    }
    /**
     * @brief Υπερφόρτωση του τελεστή [].
     * 
     * @param N Ο αριθμός/index του αντικειμένου που θέλουμε να πάρουμε
     * @return T& Το αντικείμενο που βρίσκεται στο συγκεκριμένο index
     */
    T &operator[](size_t N)
    {
        return this->m_data[N];
    }
    /**
     * @brief Αντίστοιχη της pop_back του STL Vector
     * 
     * @return T Το αντικείμενο που έγινε pop
     */
    T pop_back()
    {
        int prev_size = m_size - 1; //Το μέγεθος αφού αφαιρέσουμε 1
        T itm = m_data[prev_size];  //Το αντικείμενο οπου βρίσκεται σε εκκείνη την θέση
        m_data[--m_size].~T();      //Καλείται ο destructor το υαντικειμένου αφόυ πρώτα μειωθεί το μέγεθος m_size.Δηλαδή με αυτη τη γραμμή γινεται destruct το τελευταίο αντικείμενο
        return itm;                 //Επιστροφή αντικειμένου
    }
    /**
     * @brief destructor
     * 
     */
    ~DynamicArray<T>()
    {
        delete[] m_data;
    }
};
#endif

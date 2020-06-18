#ifndef __Vector2D_H__
#define __Vector2D_H__

#include <cmath>

template <class T>
/**
 * @brief Κλάση για διάνυσμα δυσδιάστατου χώρου που είχα σχεδιάσει στο παρελθόν στα πλαίσια εξάσκησης για τα templates
 * 
 */
class Vector2D {
public:
    T x, y;

    /**
	 * @brief Default Constructor αρχικοποιεί το Χ και Y σε 0,0
	 * 
	 */
    Vector2D()
        : x(0)
        , y(0)
    {
    }
    /**
	 * @brief Constructor που αρχικοποιεί τα  Χ και Y με συγκεκριμένες τιμές
	 * 
	 * @param x 
	 * @param y 
	 */
    Vector2D(T x, T y)
        : x(x)
        , y(y)
    {
    }
    /**
	 * @brief Copy Constructor
	 * 
	 * @param v 
	 */
    Vector2D(const Vector2D& v)
        : x(v.x)
        , y(v.y)
    {
    }

    /**
	 * @brief Υπερφόρτωση τελεστή =
	 * 
	 * @param v Το διάνυσμα απο το οποίο θα αντιγραφούν τα δεδομένα
	 * @return Vector2D& 
	 */
    Vector2D& operator=(const Vector2D& v)
    {
        x = v.x;
        y = v.y;
        return *this;
    }
    /**
	 * @brief Υπερφόρτωση τελεστή + ώστε να προσθέτει τα χ και τα y των δύο αντικειμένων και επιστρέφει ενα καινούργιο που περιέχει αυτές τις τιμές
	 * 
	 * @param v 
	 * @return Vector2D 
	 */
    Vector2D operator+(Vector2D& v)
    {
        return Vector2D(x + v.x, y + v.y);
    }
    /**
	 * @brief Υπερφόρτωση τελεστή - αντιστοιχη του + ωστε να αφαιρεί
	 * 
	 * @param v 
	 * @return Vector2D 
	 */
    Vector2D operator-(Vector2D& v)
    {
        return Vector2D(x - v.x, y - v.y);
    }
    /**
	 * @brief Υπερφόρτωση τελεστή += 
	 * 
	 * @param v 
	 * @return Vector2D& 
	 */
    Vector2D& operator+=(Vector2D& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    }
    /**
	 * @brief Υπερφόρτωση τελεστή -=
	 * 
	 * @param v 
	 * @return Vector2D& 
	 */
    Vector2D& operator-=(Vector2D& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    }
    /**
	 * @brief Υπερφόρτωση τελεστη + με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα προστεθεί στα Χ και Y
	 * @return Vector2D Αντικείμενο με τις νέες τιμές
	 */
    Vector2D operator+(double s)
    {
        return Vector2D(x + s, y + s);
    }
    /**
	 * @brief Υπερφόρτωση τελεστη - με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα αφαιρεθεί απο τα Χ και Y
	 * @return Vector2D Αντικείμενο με τις νέες τιμές
	 */
    Vector2D operator-(double s)
    {
        return Vector2D(x - s, y - s);
    }
    /**
	 * @brief Υπερφόρτωση τελεστη * με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα πολλαπλασιαστεί με τα Χ και Y
	 * @return Vector2D Αντικείμενο με τις νέες τιμές
	 */
    Vector2D operator*(double s)
    {
        return Vector2D(x * s, y * s);
    }
    /**
	 * @brief Υπερφόρτωση τελεστη / με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα διαιρεθεί απο τα Χ και Y
	 * @return Vector2D Αντικείμενο με τις νέες τιμές
	 */
    Vector2D operator/(double s)
    {
        return Vector2D(x / s, y / s);
    }
    /**
	 * @brief Υπερφόρτωση τελεστη += με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα προστεθεί στα Χ και Y
	 * @return Vector2D& 
	 */
    Vector2D& operator+=(double s)
    {
        x += s;
        y += s;
        return *this;
    }
    /**
	 * @brief Υπερφόρτωση τελεστη -= με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα αφαιρεθεί απο τα Χ και Y
	 * @return Vector2D& 
	 */
    Vector2D& operator-=(double s)
    {
        x -= s;
        y -= s;
        return *this;
    }
    /**
	 * @brief Υπερφόρτωση τελεστη * με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα πολλαπλασιαστεί με τα Χ και Y
	 * @return Vector2D Αντικείμενο με τις νέες τιμές
	 */
    Vector2D& operator*=(double s)
    {
        x *= s;
        y *= s;
        return *this;
    }
    /**
	 * @brief Υπερφόρτωση τελεστη * με δεξί μέλος εναν αριθμό double
	 * 
	 * @param s Ο αριθμος που θα διαιρεθεί απο τα Χ και Y
	 * @return Vector2D Αντικείμενο με τις νέες τιμές
	 */
    Vector2D& operator/=(double s)
    {
        x /= s;
        y /= s;
        return *this;
    }
    /**
	 * @brief Setter και των δυο παραμετρων
	 * 
	 * @param x 
	 * @param y 
	 */
    void set(T x, T y)
    {
        this->x = x;
        this->y = y;
    }
    /**
	 * @brief Χρησιμοποιείται για περιστροφή του διανύσματος κατα συγκεκριμένες μοίρες
	 * Ο υπολογισμός των Χ και Y γίνεται με βάση γνωστό θεώρημα.
	 * 
	 * @param deg Μοίρες
	 */
    void rotate(double deg)
    {
        double theta = deg / 180.0 * M_PI;
        double c = cos(theta);
        double s = sin(theta);
        double tx = x * c - y * s;
        double ty = x * s + y * c;
        x = tx;
        y = ty;
    }

    /**
	 * @brief Μεθοδος κανονικοποίησης διανύσματος
	 * Για να κανονικοποιηθεί ενα διάνυσμα διαρείται το διάνυσμα με το μέτρο του.Έτσι προκύπτει ένα μοναδιαίο διάνυσμα.Δηλαδή δημιουργείται ενα διάνυσμα με μήκος ίσο με 1
	 * 
	 * 
	 * @return Vector2D& Το διάνυσμα κανονικοποιημένο
	 */
    Vector2D& normalize()
    {
        if (length() == 0)
            return *this;
        *this *= (1.0 / length());
        return *this;
    }

    /**
	 * @brief Επιστρέφει το μέτρο του διανύσματος
	 * 
	 * @return float Το μέτρο του διανύσματος
	 */
    float length() const
    {
        return std::sqrt(x * x + y * y);
    }
};

typedef Vector2D<int> Vector2Di;
typedef Vector2D<double> Vector2Dd;

#endif
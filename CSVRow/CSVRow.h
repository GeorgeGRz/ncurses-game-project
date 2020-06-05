#ifndef CSVROW_H
#define CSVROW_H

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
/**
 * \class
 * @brief Κλάση CSVRow χρησιμοποιείται για την προσπέλαση και ανάγνωση δεδομένων απο csv αρχεία
 * 
 */
class CSVRow
{
    public:
        /**
         * @brief Επιστρέφει string που βρίσκεται στο συγκεκριμένο index
         * 
         * @param index Η θέση του string
         * @return std::string const& 
         */
        std::string const& operator[](std::size_t index) const
        {
            return m_data[index];
        }
        /**
         * @brief Επιστρέφει το μέγεθος του vector που περιέχει τις γραμμές
         * 
         * @return std::size_t 
         */
        std::size_t size() const
        {
            return m_data.size();
        }
        /**
         * @brief Διαβάζει την επόμενη γραμμή απο istream str
         * 
         * @param str Το input stream απο το οποίο θα διαβάσει
         */
        void readNextRow(std::istream& str)
        {
            std::string         line; //χρησιμοποιείται για καθε γραμμη
            std::getline(str, line);//Διαβαζει την γραμμή απο το istream str και αντιγραφει το περιεχόμενο στη line

            std::stringstream   lineStream(line);//Χρησιμοποιείται stringstream για να προσπελαστεί η γραμμή
            std::string         cell;
            m_data.clear();//Καθαρίζεται το περιεχόμενο του διανύσματος
            while(std::getline(lineStream, cell, ';'))
            {
                //Η getline βγάζει τους χαρακτήρες απο το lineStream και τους αποθηκεύει στο cell μέχρι να συναντήσει τον χαρακτηρα ";"
                m_data.push_back(cell);
            }
        
            //Εάν υπάρχει ; και δεν έχει δεδομένα μετά
            if (!lineStream && cell.empty())
            {
                //Εαν υπάρχει ; μετά, τότε πρόσθεσε ένα κενό στοιχείο
                m_data.push_back("");
            }
        }
    private:
        std::vector<std::string>    m_data;
};

#endif
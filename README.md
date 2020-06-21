! \mainpage Αρχική Σελίδα
  \section intro_sec Εισαγωγή
  \subsection projInfo Λίγα λόγια για το project.
  Πρόκειται για ένα project παιχνιδιού περιπέτειας που δημιουργήθηκε στα πλαίσια τελικής εργασίας στο μάθημα Αντικειμενοστρεφής Προγραμματισμός.
  Το παιχνίδι τρέχει μόνο σε λειτουργικό σύστημα <b>Linux</b> η οποία είναι και η μοναδική απαίτηση.
  \section install_prereq_sec Πριν την εγκατάσταση
 
  \subsection projPreq Τι χρειάζεστε
  <ul>
   <li><a href="https://invisible-mirror.net/archives/ncurses/">NCurses Library</a></li>
   <li><a href="https://packages.ubuntu.com/search?keywords=build-essential">Make(build-essential)</a></li>
   <li><a href="https://packages.ubuntu.com/search?keywords=g%2B%2B">C++11</a></li>
  </ul>
  \section install_sec Οδηγίες εγκατάστασης
   \subsection step1 (A) Repository
   Μετακινηθείτε στον κατάλογο οπου επιθυμείτε να κάνετε clone και πληκτρολογηστε στο τερματικο @code git clone https://github.com/GeorgeGRz/ncurses-game-project.git @endcode
   \subsection step2 (B) Συμπιεσμένο αρχείο
   Αποσυμπιέστε το αρχείο στον επιθυμητό κατάλογο με το command @code tar -xzvf ncurses-game-project.tar.gz @endcode
  \subsection step3 Μετακίνηση στον κατάλογο που εγινε clone
   Στη συνέχεια πληκτρολογηστε @code cd ncurses-game-project/ && make all @endcode
   
   \subsection step4 Τρέξτε το παιχνίδι.
   Για να τρέξετε το παιχνίδι απλά πληκτρολογηστε ενώ βρίσκεστε στον ίδιο κατάλογο @code ./adventureGame @endcode
  
 
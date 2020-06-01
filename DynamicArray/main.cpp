#include "DynamicArray.h"
#include <iostream>
using namespace std;


class Person{
    private:
        string name,surname;
    public:
        Person(){;}
        Person(string n, string s):name(n),surname(s){;};
        inline string getString(){return name;}
        inline string getSurname(){return surname;}
};

int main(){
    DynamicArray<Person> p;
    p.push_back(Person("b","b"));
    for(auto x : p){
        cout<< x.getString();
    }
}
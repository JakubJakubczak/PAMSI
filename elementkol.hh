#ifndef ELEMENTKOL_HH
#define ELEMENTKOL_HH
#include <string>
#include <iostream>
// klasa przechowujaca podzielony tekst, klucz i wskaznik do nastepnego elementu jesli taki istnieje
class elementkol{
    public:
int klucz;
std::string pakiet;
elementkol* next;
elementkol(int k, std::string p);
elementkol(int k);
elementkol();
};


#endif
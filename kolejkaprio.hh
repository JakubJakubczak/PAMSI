#ifndef KOLEJKAPRIO_HH
#define KOLEJKAPRIO_HH
#include "elementkol.hh"
#include <string>
 // klasa  tworzaca kolejke 
class kolejkaprio{
private:
elementkol* pierwszy;
public:
int size();
bool isEmpty();
void insert(int KLUCZ, std::string PAKIET);
elementkol removeMin();
elementkol Min();
void WyswietlKolejke();
kolejkaprio();
};

#endif
#include "elementkol.hh"

// konstruktor 
elementkol::elementkol(int k, std::string p)
{
    klucz=k;
    pakiet=p;
    next=0;
}

elementkol::elementkol(int k)
{
    klucz=k;
    next=0;
}
elementkol::elementkol()
{
    next=0;
};
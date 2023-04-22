#include "elementkol.hh"
#include "kolejkaprio.hh"
#include <cstdlib>
#include <ctime>
#include <string>
#include <iostream>







void mixarray(elementkol* tab[], int count)
{
    for (int i = 0; i < count; i++)
    {
        int j= rand() % count;
        std::swap(tab[i],tab[j]);
    }
   // return tab;
}   

int main()
{
    std::string wiadomosc;
    std::string wiadomoscposortowaniu;
    int dlugoscwiadomosci;
    int dlugoscpakietumin;
    elementkol* pakiet1 = new elementkol(1);
    elementkol* pakiet2 = new elementkol(2);
    elementkol* pakiet3 = new elementkol(3);
    elementkol* pakiet4 = new elementkol(4);
    elementkol* pakiet5 = new elementkol(5);
    kolejkaprio kolejka;
    std::string pakiet[5];
    srand( time( NULL ) ); // czas do zmiennej losowej

    getline(std::cin,wiadomosc);

    dlugoscwiadomosci=wiadomosc.length();
    dlugoscpakietumin=dlugoscwiadomosci/5;

    pakiet1->pakiet=wiadomosc.substr(0,dlugoscpakietumin);
    pakiet2->pakiet=wiadomosc.substr(dlugoscpakietumin,dlugoscpakietumin);
    pakiet3->pakiet=wiadomosc.substr(dlugoscpakietumin*2,dlugoscpakietumin);
    pakiet4->pakiet=wiadomosc.substr(dlugoscpakietumin*3,dlugoscpakietumin);
    pakiet5->pakiet=wiadomosc.substr(dlugoscpakietumin*4);

    elementkol* pakiety[]={pakiet1,pakiet2,pakiet3,pakiet4,pakiet5};
    
    mixarray(pakiety,5);
    std::cout<<"Wiadomosc podzielona i polosowana: ";
     for (int i = 0; i < 5; i++)
    {
        std::cout<<pakiety[i]->pakiet<<" ";
    }

    // dodawanie elementow do kolejki priorytetowej
    for ( int i = 0; i < 5; i++)
    {
        kolejka.insert(pakiety[i]->klucz, pakiety[i]->pakiet);
    }
    
    // usuwanie elementow do kolejki priorytetowej i zapisywanie ich do stringow
    for (int i = 0; i < 5; i++)
    {
        pakiet[i]=kolejka.removeMin().pakiet;
    }

    // laczenie posortowanych pakietow w wiadomosc

    for (int i = 0; i < 5; i++)
    {
        wiadomoscposortowaniu=wiadomoscposortowaniu+pakiet[i];
    }
    
    // wypisanie wiadomosci po sortowaniu

    std::cout<<std::endl;
    std::cout<<"Wiadomosc po sortowaniu "<<wiadomoscposortowaniu<<std::endl;
    
    
    

    delete pakiet1;
    delete pakiet2;
    delete pakiet3;
    delete pakiet4;
    delete pakiet5;

    return 0;
}
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

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

// klasa  tworzaca kolejke 
class kolejkaprio{
public:
elementkol* pierwszy;
 
int size();
bool isEmpty();
void insert(int KLUCZ, std::string PAKIET);
elementkol removeMin();
elementkol Min();
void WyswietlKolejke();
kolejkaprio();
};

// konstruktor ustawiajacy pierwszy elemnt za 0 przy inicjalizacji
kolejkaprio::kolejkaprio()
{
    pierwszy=0;
}

bool kolejkaprio::isEmpty()
{
    if(pierwszy==0) return true;
    else return false;
}

// metoda dodajaca element do kolejki
void kolejkaprio::insert(int KLUCZ, std::string PAKIET)
{
    elementkol* nowa = new elementkol;
    nowa->klucz=KLUCZ;
    nowa->pakiet=PAKIET;
    
    if(this->isEmpty())
        {
            pierwszy=nowa;
        }
    else
        {
            elementkol* temp = pierwszy;
            while(temp->next)
                {
                    temp=temp->next;
                }
            temp->next=nowa;
            nowa->next=0;
        }
}

void kolejkaprio::WyswietlKolejke()
{
    elementkol* temp = pierwszy;
     if(this->isEmpty())
        {
            std::cout<<"W kolejce nie ma zadnych elemtnow do wypisania"<<std::endl;
        }
     else   
        { 
         while((temp))
            {
                std::cout<<temp->pakiet<<" "<<temp->klucz<<std::endl;
                temp=temp->next;
            }
        }
        delete (temp);
}

int kolejkaprio::size()
{
    int size=0;
    if(this->isEmpty()) return size;
    else
    {
        elementkol* temp=pierwszy;
        while(temp!=0)
        {
            size++;
            temp=temp->next;
        }
        return size;
        delete (temp);
    }
    
    
}
elementkol kolejkaprio::Min()
{
    elementkol* temp=pierwszy;
    elementkol* min = pierwszy;

    if(isEmpty()) 
    {
        std::cout<<"Nie ma nic w kolejce"<<std::endl;
        return *min;
    }

    while(temp)
    {
        if(temp->next==0) return *min;
        temp=temp->next;
        if(temp->klucz<min->klucz) min=temp;
    }
    
    delete (temp);
    return *min;
}

elementkol kolejkaprio::removeMin()
{
    elementkol* temp=pierwszy;
    elementkol* min = pierwszy;
    int nr=1;
    int nr_min=1;

    if(isEmpty()) 
    {
        std::cout<<"Nie ma nic w kolejce"<<std::endl;
        return *min;
    }
    while(temp)
    {
        if(temp->next==0) break;
        temp=temp->next;
        nr++;
        if(temp->klucz<min->klucz) 
        {
            min=temp;
            nr_min=nr;
        }
      
    }

    // usuwanie pierwszego elementu
    if(nr_min==1)
    {
        elementkol* usuwany=pierwszy;
        pierwszy=pierwszy->next;
        usuwany->next=0;
    }

    // usuwanie elementu ostatniego
    if(nr_min==this->size())
    {
        temp=pierwszy;
        for ( int i = 1; i < this->size()-1; i++)
        {
            temp=temp->next;
        }  
        temp->next=0;

    }

    // usuwanie elementu w srodku
    if(nr_min>1 && nr_min<this->size())
    {
        temp=pierwszy;
        for ( int i = 1; i < nr_min-1; i++)
        {
            temp=temp->next;
        }  
        elementkol* usuwany=temp->next;
        temp->next=temp->next->next;
        usuwany=0;
    }

    return *min;



}

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
    int j=0;
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
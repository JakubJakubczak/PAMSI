#include "kolejkaprio.hh"
#include <iostream>
#include <string>

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
        temp->next=temp->next->next;
      
    }

    return *min;



}

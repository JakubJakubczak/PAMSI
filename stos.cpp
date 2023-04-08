#include <iostream>

//Implementacja stosu za pomocą tablicy
template  <typename Object>
class stosTAB{
    public:
    Object tablica[100];
    public:
    int size=0;

    public:
    int getsize();
    bool IsEmpty();
    void push(Object O);
    Object pop();
    Object& top();
    void WyswietlStos();
};

//pobieranie rozmiaru stosu
template  <typename Object>
int stosTAB<Object>::getsize()
{
    return size;
}
//sprawdzanie czy stos jest pusty
template  <typename Object>
bool stosTAB<Object>::IsEmpty()
{
    if(this->getsize()==0) return true;
    else return false;
}

//funkcja push dla stosu
template  <typename Object>
void stosTAB<Object>::push(Object O)
{
    //poszerzanie tablicy o 100
    // if(this->getsize()==sizeof(this->tablica)/sizeof(this->tablica[0]))
    // {   
    //     Object tablica2[sizeof(this->tablica)/(sizeof(this->tablica[0]))];
    //     for (int i = 0; i < sizeof(this->tablica)/sizeof(this->tablica[0]); i++)
    //     {
    //         tablica2[i]=this->tablica[i];
    //     }
    //     delete[] this->tablica;
    //     this->tablica=tablica2;
    // }
    size++;
    this->tablica[size-1]=O;
}
// funkcja pop dla stosu, ktora zwraca element usuwany
template  <typename Object>
Object stosTAB<Object>::pop()
{
    if(this->IsEmpty()==true)
    {
        std::cout<<"Stos jest pusty"<<std::endl;
        return 0;
    }
    size--;
    return this->tablica[size+1];
}


template  <typename Object>
Object& stosTAB<Object>::top()
{
     return this->tablica[size];
}

template  <typename Object>
void stosTAB<Object>::WyswietlStos()
{
    for (int i = 0; i < size; i++)
    {
      std::cout<<this->tablica[i]<<" ";
    }
}

int main() {
   
    stosTAB<int> stos;
    char znak;
    int liczba;
    

    std::cout<<"Menu stosu"<<std::endl;
    std::cout<<"Dodaj element do stosu - d"<<std::endl;
    std::cout<<"Usun element ze stosu - u"<<std::endl;
    std::cout<<"Wyswietl stos - w"<<std::endl;

    for (;;)
    {
        std::cin>>znak;
        switch(znak)
        {
            case 'd':
              std::cin>>liczba;
              stos.push(liczba);
                break;
            case 'u':
              stos.pop();
                break;
            case 'w':
              stos.WyswietlStos();
                break;
            default:
                std::cout<<"Nie ma takiej opcji"<<std::endl;
        }
            
    }
    

    return 0;
}


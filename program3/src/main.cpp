#include <iostream>
#include <cstdlib>

#include "AI.hpp"
#include "plansza.hpp"

int main()
{
    std::string odp;
    int rozmiar;
    int doWygranej;
    char znak;
    while(odp!="k")
    {
        // system("cls");
        std::cout<<"Gra w kolko i krzyzyk"<<std::endl;
        std::cout<<"Podaj rozmiar tablicy(kwadratowej): "<<std::endl;
        std::cin>>rozmiar;
        if(!(rozmiar>2 && rozmiar<=10)) 
        {   
             while(!(rozmiar>2 && rozmiar<=10))  // rozmiar miedzy 3x3 a 10x10 
                {
                std::cout<<"Rozmiar wybierz z zakresu 3 do 10"<<std::endl;
                std::cin>>rozmiar;
                }
        }
        
        std::cout<<"Podaj ilosc w rzedzie do wygranej: "<<std::endl;
        std::cin>>doWygranej;
        if(!(doWygranej>2 && doWygranej<=rozmiar)) 
        {   
             while(!(doWygranej>2 && doWygranej<=rozmiar))  // doWygranej miedzy 3 a rozmiarem tablicy
                {
                std::cout<<"Ilosc w rzedzie do wygranej wybierz z zakresu 3 do rozmiaru, ktory wybrales"<<std::endl;    
                std::cin>>doWygranej;
                }
        }

        std::cout<<"Podaj jakim znakiem chcesz grac(X lub O): "<<std::endl;
        std::cin>>znak;
        if(!(znak == 'o' || znak == 'O' || znak == 'x' || znak == 'X')) 
        {     
             while(!(znak == 'o' || znak == 'O' || znak == 'x' || znak == 'X'))  
                {
                std::cout<<"Zly znak, wybierz X lub O"<<std::endl;
                std::cin>>znak;
                }
        }
       
        plansza Plansza(rozmiar,doWygranej);  // inicjowanie planszy z wpisanym przez uzytkownika rozmiarem i iloscia w rzedzie do wygranej
        if(znak=='o' || znak=='O') 
        {
            Plansza.znakGracza='O';
            Plansza.znakAI='X';
        }
         if(znak=='x' || znak=='X') 
        {
            Plansza.znakGracza='X';
            Plansza.znakAI='O';
        }
        while(Plansza.StanGry()==0 && !Plansza.CzyJestPelna()  )
        {
        Plansza.Rysuj();
        std::cout<<"Wpisz ruch(np. B2): ";
        std::cin>>odp;
        if( !( int(odp[0])-65 >= 0 && int(odp[0])-65 < rozmiar  && odp[1]-48>0 && odp[1]-48<=rozmiar )) // sprawdzenie czy ruch miesci sie w tablicy
        {   
            while(!((int(odp[0])-65) >= 0 && (int(odp[0])-65) < rozmiar  && odp[1]-48>0 && odp[1]-48<=rozmiar ))
            {
            std::cout<<"Taki ruch jest niemozliwy. Wpisz ponownie poprawny. "<<std::endl;
            std::cin>>odp;
            }
        }
        if( Plansza.CzyJestZajete( odp[1]-49, int(odp[0])-65 ) ) 
        {
            while(Plansza.CzyJestZajete(odp[1]-49,int(odp[0])-65))
            {
                std::cout<<"To miejsce jest zajete. Wpisz ponownie "<<std::endl;
                std::cin>>odp;
            }
        }
        Plansza.Ustaw( odp[1]-49,int(odp[0])-65);
        Plansza.ZmienTure();
        }
        Plansza.Rysuj();
        if(Plansza.StanGry()==1) std::cout<<"Brawo wygrales!"<<std::endl;
        if(Plansza.StanGry()==-1) std::cout<<"Niestety przegrales :("<<std::endl;
        if(Plansza.StanGry()==0) std::cout<<"Remis. Sprobuj jeszcze raz!"<<std::endl;

        std::cout<<"Czy chcesz zagrac jeszcze raz?(t/n)"<<std::endl;
        std::cin>>odp;
        if(odp=="t") continue;
        else exit(0);

    } 
    return 0;
}
#pragma once

#include <iomanip>
#include <iostream>
#include <vector>

class plansza
{
    public:
    // zmienne
    std::vector<std::vector<char>> pozycja; // tablia kwadratowa okreslajaca pozycje
    char znakAI;  // znak kolko lub krzyzyk
    char znakGracza;
    int doWygrania; // ciag tego samego znaku do wygrania gry
    int wymiar;
    int tura;
    // funkcje
    int StanGry() const;  // zwraca 1 jesli wygrana, -1 gdy przegrana i 0 gdy nie ma rozstrzygniecia lub jest remis
    void Rysuj() const;   // rysuje gre
    bool CzyJestPelna() const;   // sprawdza czy wszystkie pola sa zajete
    bool CzyJestZajete(int x, int y) const;  // sprawdza czy wybrane pole jest zajete 
    void Resetuj(); // Resteuje plansze
    bool CzyTuraGracza() const;
    void ZmienTure();
    void Ustaw(int x, int y); // ustawia dany znak na polu (x,y)
    void Usun(int x, int y); // usuwa dany znak na polu (x,y) 
    // konstruktor
    plansza(int Wymiar, int DoWygrania);
};

plansza::plansza(int Wymiar, int DoWygrania): pozycja(Wymiar, std::vector<char>(Wymiar))
{
    for(int i=0; i<Wymiar; i++) // zerowanie pozycji
    {
        for(int j=0; j<Wymiar; j++)
        {
            pozycja[i][j]=0;
        }
    }

    znakAI=0;
    znakGracza=0;
    doWygrania=DoWygrania;
    wymiar=Wymiar;
    tura=1;
}

bool plansza::CzyJestPelna() const
{
     for(int i=0; i<wymiar; i++) // zerowanie pozycji
    {
        for(int j=0; j<wymiar; j++)
        {
            if(pozycja[i][j]==0) return 0; // jesli ktoras pozycja jest rowna 0 to zwracamy 0, czyli ze nie jest pelna
        }
    }
    return 1; // jesli kazda pozycja jest rozna od 0 to znaczy ze tablica jest pelna
}

bool plansza::CzyJestZajete(int x, int y) const
{
    if(pozycja[x][y]==0) return 0;
    else return 1;
}

void plansza::Resetuj()
{
    for(int i=0; i<wymiar; i++) // zerowanie pozycji
    {
        for(int j=0; j<wymiar; j++)
        {
            pozycja[i][j]=0;
        }
    }
}

bool plansza::CzyTuraGracza() const
{
    if(tura==1) return 1; // gdy tura jest gracza to tura=1
    else return 0; 
}

void plansza::ZmienTure()
{
    if(tura==1) tura=0;
    else tura=1;
}

void plansza::Ustaw(int x, int y)
{
    if(CzyTuraGracza()) pozycja[x][y] = znakGracza;
    else pozycja[x][y] = znakAI;
}

void plansza::Usun(int x, int y)
{
    pozycja[x][y] = 0;
}

void plansza::Rysuj() const
{
    // oznaczenia kolumn jako A B C D E itd.
    std::cout << std::string(5, ' '); // 5 spacji
    for (char x = 'A'; x < 'A' + wymiar; x++) {
        if (x < 'A' +9)
            std::cout << std::setw(1) << char(x)  << "   ";
    }
     std::cout << '\n';
     // linia pozioma gorna
    std::cout << std::string(3, ' ') << '.' << std::string(4 * wymiar - 1, '-') << ".\n";

     for (int y = 0; y < wymiar; y++) {
        // oznaczenia wierszy, linie pionowe i znaki
        std::cout << std::setw(2) << y + 1 << " | ";
        for (int x = 0; x < wymiar; x++) {
            if (pozycja[y][x] == 0)
                std::cout << ' ';
            else
                std::cout << pozycja[y][x];
            if (x < wymiar - 1)
                std::cout << " | ";
        }
         std::cout << " | ";

        // linie poziome
        if (y < wymiar - 1) {
            std::cout << "\n   |";
            for (int i = 0; i < wymiar - 1; i++)
                std::cout << std::string(3, '-') << '-';
            std::cout << std::string(3, '-') << "|";
        }
        std::cout << '\n';
    }

     // linia pozioma dolna
    std::cout << std::string(3, ' ') << '\'' << std::string(4 * wymiar - 1, '-') << "\'\n";
}

int plansza::StanGry() const
{
    int licznik=1;

    // sprawdzanie pionowo
    for(int j=0; j<wymiar; j++)   
    {
       licznik=1;
       for(int i=0; i<wymiar-1; i++)   
       {
        if(pozycja[i][j]==pozycja[i+1][j]) licznik++;
        else licznik=1;

        if(licznik==doWygrania)
        {
            if(pozycja[i][j]==znakGracza) return 1; // wygrana gracza
            if(pozycja[i][j]==znakAI) return -1; // wygrana AI
        }
       }  
    }


    // sprawdzanie poziomo
    for(int i=0; i<wymiar; i++)   
    {
       licznik=1;
       for(int j=0; j<wymiar-1; j++)   
       {
        if(pozycja[i][j]==pozycja[i][j+1]) licznik++;
        else licznik=1;

        if(licznik==doWygrania)
        {
            if(pozycja[i][j]==znakGracza) return 1; // wygrana gracza
            if(pozycja[i][j]==znakAI) return -1; // wygrana AI
        }
       }  
    }


    // sprawdzanie na skosy

    // do gory i w lewo
    int zm=0; // zmienna pomocnicza do petli
    int pom=0;;
    for(int i=0; i<wymiar-doWygrania+1; i++)   
    {
       licznik=1;
       zm=0;
       pom=i;
       for( int j=0; j<wymiar-doWygrania-i+2; j++)   
       {    
        if(pozycja[pom][zm]==pozycja[pom+1][zm+1]) licznik++;
        else licznik=1;

        if(licznik==doWygrania)
        {
            if(pozycja[pom][zm]==znakGracza) return 1; // wygrana gracza
            if(pozycja[pom][zm]==znakAI) return -1; // wygrana AI
        }
        zm++;
        pom++;
       }  
    }

    // do gory i w prawo
    zm=0;
    pom=0;
    for(int i=0; i<wymiar-doWygrania+1; i++)   
    {
       licznik=1;
       zm=i;
       pom=0;
       for( int j=0; j<wymiar-doWygrania-i+2; j++)   
       {    
        if(pozycja[pom][zm]==pozycja[pom+1][zm+1]) licznik++;
        else licznik=1;

        if(licznik==doWygrania)
        {
            if(pozycja[pom][zm]==znakGracza) return 1; // wygrana gracza
            if(pozycja[pom][zm]==znakAI) return -1; // wygrana AI
        }
        zm++;
        pom++;
       }  
    }

     // do dolu i w prawo
    zm=wymiar-1;
    pom=0;
    for(int i=0; i<wymiar-doWygrania+1; i++)   
    {
       licznik=1;
       zm=wymiar-1 -i;
       pom=0;
       for( int j=0; j<wymiar-doWygrania-i+2; j++)   
       {    
        if(pozycja[pom][zm]==pozycja[pom+1][zm-1]) licznik++;
        else licznik=1;

        if(licznik==doWygrania)
        {
            if(pozycja[pom][zm]==znakGracza) return 1; // wygrana gracza
            if(pozycja[pom][zm]==znakAI) return -1; // wygrana AI
        }
        zm--;
        pom++;
       }  
    }

     // do dolu i w lewo
    zm=wymiar-1;
    pom=0;
    for(int i=0; i<wymiar-doWygrania+1; i++)   
    {
       licznik=1;
       zm=wymiar-1;
       pom=i;
       for( int j=0; j<wymiar-doWygrania-i+2; j++)   
       {    
        if(pozycja[pom][zm]==pozycja[pom+1][zm-1]) licznik++;
        else licznik=1;

        if(licznik==doWygrania)
        {
            if(pozycja[pom][zm]==znakGracza) return 1; // wygrana gracza
            if(pozycja[pom][zm]==znakAI) return -1; // wygrana AI
        }
        zm--;
        pom++;
       }  
    }
    
    return 0;
}
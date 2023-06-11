#include <iostream>
#include <chrono>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iterator>


#include "sortscal.hpp"
#include "quicksort.hpp"
#include "introsort.hpp"



struct film {
    std::string nazwa;  // nazwa filmu
    int ocena;      // ocena filmu od 0 do 10
    bool operator<(film porow) { return (ocena < porow.ocena); }
    bool operator>(film porow) { return (ocena > porow.ocena); }
};

int main() 
{
  
    // pliki
    std::ifstream BazaFilmow;  // baza filmow (wczytywany plik)
    std::string NazwaBazyFilmow = "projekt2_dane.csv";
    std::ofstream PosortowanaBazaFilmow;  // posortowana baza  filmow (zapisywany plik)
    std::string NazwaPosortowanejBazyFilmow="PosortowanaBazaFilmow";

    // zmienne pomocnicze do przeszukiwania pliku
    std::string temp,linia;  // pojedynczy wpis w bazie
    char znak;         // , lub "
    int rozmiar = 405366; // ilość danych w bazie filmów 
  
    int nieocenione;
    float srednia;
    float mediana;
    float suma;
    std::string sortowania[] = {"merge", "quick", "intro"};

    film* Przeszukiwanie = new film[rozmiar]; // struktura pozwalajaca przeszukac BazeFilmow
    nieocenione = 0; 
    BazaFilmow.open(NazwaBazyFilmow); // otwieranie bazy z filmami
    
        if (!BazaFilmow.is_open()) {
            std::cout << "Nie otworzono pliku BazaFilmow";
            exit(1);
        }
        
        std::getline(BazaFilmow, linia);  // pominiecie headera
        for (int i = 0; i < rozmiar; i++) {
            std::getline(BazaFilmow, linia);  // Pobieranie kolejnych linii z pliku
            std::stringstream split(linia);
            // wczytywanie numeru filmu i przecinka
            std::getline(split, temp, ',');
            // wczytywanie nazwy, odzielonej przecinkiem, jesli w nazwie jest przecinek to film jest objety ""
            std::stringstream::pos_type pos = split.tellg();
            split >> znak;
            if (znak == '"') {
                std::getline(split, Przeszukiwanie[i].nazwa, '"');
                split >> znak;  // wczytujemy przecinek
            }
            else {
                split.seekg(pos);  // wracamy do miejsca, w ktorym byl strumien zapisany w split.tellg()
                std::getline(split, Przeszukiwanie[i].nazwa, ',');
            }
            // wczytywanie oceny
            if (!(split >> Przeszukiwanie[i].ocena)) {
                nieocenione++;
                Przeszukiwanie[i].ocena = -1;   // ustawiamy ranking na -1, by podczas filtrowania mozna bylo latwo te wpisy usunac
            }
        }
        BazaFilmow.close();

        // Wypisywanie liczby nieocenionych filmow jesli takie istnieja
        if (nieocenione > 0) {
            std::cout << "Liczba filmow bez oceny: " << nieocenione << '\n';
            std::cout << "Filtrowanie danych\n";
        }
        else 
            std::cout << " Wszystkie filmy sa ocenione. \n";

        film* PrzefiltrowanaBazaFilmow = new film[rozmiar - nieocenione];
        int i = 0, j = 0;

        auto start = std::chrono::high_resolution_clock::now();  // start mierzenia czasu
        while (j < rozmiar)
        {
            if (Przeszukiwanie[j].ocena != -1)
                PrzefiltrowanaBazaFilmow[i++] = Przeszukiwanie[j++];
            else
                j++;
        }
        auto koniec = std::chrono::high_resolution_clock::now();  // koniec mierzenia czasu
        auto czas = std::chrono::duration<double, std::milli>(koniec - start).count();
        delete[] Przeszukiwanie;
       

        // Wypisywanie obliczonego czasu i liczby wpisow
        if (nieocenione > 0)
            {
            std::cout << "Po przefiltrowaniu: " << rozmiar - nieocenione << '\n'
            << "Czas filtrowania:   " << czas << " ms\n";
            }
        // sortowanie 
        // zmienne przechowujace wyniki
        film* merge = new film[rozmiar-nieocenione];
        film* quick = new film[rozmiar-nieocenione];
        film* intro = new film[rozmiar-nieocenione];

        film* tabsort[3] = {merge,quick,intro};

        // Przepisanie wartosci
        for(int i=0; i<std::size(tabsort);i++)
        {
        for(int j=0; j<(rozmiar - nieocenione);j++)
        {
            tabsort[i][j].ocena=PrzefiltrowanaBazaFilmow[j].ocena;
            tabsort[i][j].nazwa=PrzefiltrowanaBazaFilmow[j].nazwa;
        }
        }
        delete [] PrzefiltrowanaBazaFilmow;
        // petla dla 3 sortowan
        for(int i=0; i<std::size(sortowania); i++)
    {
        std::cout<<"Sortowanie "<<sortowania[i]<<std::endl;
        auto start_sort = std::chrono::high_resolution_clock::now();
        if(sortowania[i]=="merge") mergeSort(merge, 0, rozmiar - nieocenione - 1);
        else if(sortowania[i]=="quick") quickSort(quick, 0, rozmiar - nieocenione - 1);
        else if(sortowania[i]=="intro") hybridIntroSort(intro, 0, rozmiar - nieocenione - 1);
        auto koniec_sort = std::chrono::high_resolution_clock::now();
        auto czas_sortowania= std::chrono::duration<double, std::milli>(koniec_sort- start_sort).count();  

        // liczenie sredniej wartosci
        suma=0;
        for(int j=0;j<(rozmiar-nieocenione);j++)
        {
            suma=suma+tabsort[i][j].ocena;
        }
        srednia=suma/(rozmiar-nieocenione);

        // liczenie mediany
        if( (rozmiar-nieocenione)%2==0)
            {
            mediana =  ( tabsort[i][ (rozmiar-nieocenione)/2].ocena  + tabsort[i][ (rozmiar-nieocenione)/2 -1].ocena    )/2;
            }
        else
            {
            mediana=tabsort[i][ (rozmiar-nieocenione)/2].ocena;
            }
        
        // wypisywanie wynikow mediany i sredniej oraz czasu sortowania
        std::cout<<"Srednia wynosi: "<<srednia<<std::endl;
        std::cout<<"Mediana wynosi: "<<mediana<<std::endl;
        std::cout<<"Czas sortowania wynosi: "<<czas_sortowania<<"ms"<<std::endl;

        // wypisanie posortowanej bazy do pliku
            
        // otwieranie pliku do zapisu
            PosortowanaBazaFilmow.open(NazwaPosortowanejBazyFilmow + "_"+sortowania[i]+".csv");
        // Wypisywanie juz przesortowane
            PosortowanaBazaFilmow<<",movie,rating"<<std::endl;

            for(int j=0; j<rozmiar-nieocenione; j++)
            {
                PosortowanaBazaFilmow<<i<<",\""<<tabsort[i][j].nazwa
                <<"\","<<tabsort[i][j].ocena<<"\n";
            }
             PosortowanaBazaFilmow.close();
    }
            std::cout<<"Posortowano baze i zapisano do pliku\n";
            
            
            delete [] merge;
            delete [] quick;
            delete [] intro;
        // w drugiej czesci programu zostanie sprawdzona efektywnosc sortowania oraz bedzie liczona  srednia i mediana zestawu danych.
        // dane zostaly wygenerowane za pomoca strony numbergenerator.org i jest to 4 miliony losowych liczb z zakresu 1 - 1000000.
        // testy zostana przeprowadzone na roznej ilosci danych: 10 000, 100 000, 500 000, 1 000 000, 4 000 000

        // Przygotowanie strumieni, ktore beda wykorzystywane
        std::ifstream DaneWej;  
        std::string NazwaDaneWej = "dane.csv";
        std::ofstream PosortowaneDaneWej;  
        std::string NazwaPosortowanychDaneWej="PosortowanaBaza";


        int ntab[] = { 10000, 100000, 500000, 1000000, 2000000 };
        std::string liczby[] = {"10000", "100000", "500000", "1000000", "2000000" };
   
        for(int i=0; i<std::size(ntab);i++)
        {
            DaneWej.open(NazwaDaneWej);
            std::cout<<"Test na danych o rozmiarze: "<<ntab[i]<<std::endl;
            int* Dane = new int[ntab[i]];
            for(int j=0; j<ntab[i];j++)  // zczytywanie liczb
            {
                DaneWej>>Dane[j];
                
            }
            DaneWej.close();

        int* merge = new int[ntab[i]];
        int* quick = new int[ntab[i]];
        int* intro = new int[ntab[i]];

        int* tabsort[3] = {merge,quick,intro};

        // Przepisanie wartosci
            for(int j=0; j<std::size(tabsort);j++)
             {
                for(int k=0; k<ntab[i];k++)
                 {
            tabsort[j][k]=Dane[k];
                 }
             }
             delete [] Dane;

        std::cout<<"Dalej sortowania beda wykonywane na przygotowanych danych "<<std::endl;
         // petla dla 3 sortowan
            for(int j=0; j<std::size(sortowania); j++)
            {
        std::cout<<"Sortowanie "<<sortowania[j]<<" "<<ntab[i]<<std::endl;
        // mergesort
        auto start_sort = std::chrono::high_resolution_clock::now();
        if(sortowania[j]=="merge") mergeSort(merge, 0, ntab[i]- 1);
        else if(sortowania[j]=="quick") quickSort(quick, 0, ntab[i]- 1);
        else if(sortowania[j]=="intro") hybridIntroSort(intro, 0, ntab[i] - 1);
        auto koniec_sort = std::chrono::high_resolution_clock::now();
        auto czas_sortowania= std::chrono::duration<double, std::milli>(koniec_sort- start_sort).count();  

        // liczenie sredniej wartosci
        suma=0;
                for(int k=0;k<(ntab[i]);k++)
                 {
            suma=suma+tabsort[j][k];
                 }
        srednia=suma/ntab[i];
        // liczenie mediany
        if( (ntab[i])%2==0)
            {
            mediana =  ( tabsort[j][ (ntab[i])/2]  + tabsort[j][ (ntab[i])/2 -1]   )/2;
            }
        else
            {
            mediana=tabsort[j][ (ntab[i])/2];
            }
        
        // wypisywanie wynikow mediany i sredniej oraz czasu sortowania
        std::cout<<"Srednia wynosi: "<<srednia<<std::endl;
        std::cout<<"Mediana wynosi: "<<mediana<<std::endl;
        std::cout<<"Czas sortowania wynosi: "<<czas_sortowania<<"ms"<<std::endl;

        // wypisanie posortowanej bazy do pliku
            
        // otwieranie pliku do zapisu
            PosortowaneDaneWej.open(NazwaPosortowanychDaneWej + "_"+sortowania[j]+liczby[i]+".csv");
        // Wypisywanie juz przesortowane

                for(int k=0; k<ntab[i]; k++)
                {
                PosortowaneDaneWej<<tabsort[j][k]<<"\n";
                }
             PosortowaneDaneWej.close();
    }
            std::cout<<"Posortowano baze i zapisano do pliku\n";
                       
            delete [] merge;
            delete [] quick;
            delete [] intro;          
        }
           
    return 0;
        
}
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
};

int main() 
{
  
    // pliki
    std::ifstream BazaFilmow;  // baza filmow (wczytywany plik)
    std::string NazwaBazyFilmow = "projekt2_dane.csv";
    std::ofstream PosortowanaBazaFilmow;  // posortowana baza  filmow (zapisywany plik)
    std::string NazwaPosortowanejBazyFilmow="PosortowanaBazaFilmow.csv";

    std::ofstream SPrzefiltrowanaBaza;  // posortowana baza  filmow (zapisywany plik)
    std::string SNazwaPrzefiltrowanejBazy="PrzefiltrowanaBazaFilmow.csv";


    // sortowania
    std::string sorts[3] = { "merge", "quick", "intro" };

    // zmienne pomocnicze do przeszukiwania pliku
    std::string temp,linia;  // pojedynczy wpis w bazie
    char znak;         // , lub "
    int rozmiar = 405366; // ilość danych w bazie filmów 
  

    int nieocenione;


    // // testy
    // unsigned int test = 0;    // numer testu
    // unsigned int nlimit = 0;  // limit n dla zapisu na sorted_dataset
    // unsigned int ntab[] = { 10000, 100000, 500000, 1000000, 1010292 };
    // unsigned int unrated, median;  // ilosc nieocenionych filmow, mediana ocen
    // float average;                 // srednia ocen


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
        // otwieranie pliku do zapisu
            SPrzefiltrowanaBaza.open(SNazwaPrzefiltrowanejBazy);
        // Wypisywanie przefiltrowanej listy bez pustych wpisow
            SPrzefiltrowanaBaza<<",movie,rating"<<std::endl;

            for(int i=0; i<rozmiar-nieocenione; i++)
            {
                SPrzefiltrowanaBaza<<i<<",\""<<PrzefiltrowanaBazaFilmow[i].nazwa
                <<"\","<<PrzefiltrowanaBazaFilmow[i].ocena<<"\n";
            }
            SPrzefiltrowanaBaza.close();
            delete [] PrzefiltrowanaBazaFilmow;
            
            std::cout<<"Przefiltrowano baze i zapisano do pliku\n";


    return 0;
        
}
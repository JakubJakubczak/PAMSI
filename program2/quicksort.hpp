#pragma once

template <typename T>
int partition(T* tab, int start, int koniec) {
    T temp, pivot = tab[(start + koniec) / 2];  // piwot wybieramy jako srodek
    int l = start, r = koniec;                   
    while (1) {
        while (tab[l] < pivot) l++;  //  iteruje  lewa strone dopoki element jest mniejszy od pivota
        while (tab[r] > pivot) r--;  // inkrementuje prawa strone dopoki element jest wiekszy od pivota

        if (l >= r)
            return r;  // jesli l dojdzie do r to zwraca ten element

        // zamien elementy 
        temp = tab[l];
        tab[l++] = tab[r];
        tab[r--] = temp;
    }
}

template <typename T>
void quickSort(T* tab, int start, int koniec) {
    // rekurencyjne dzielenie na 2 podtablice  do momentu uzyskania jednoelementowych
    if (start >= 0 && start < koniec) {
        int pivot = partition(tab, start, koniec);  
        quickSort(tab, start, pivot);            // lewa podtablica
        quickSort(tab, pivot + 1, koniec);          // prawa podtablica
    }
}
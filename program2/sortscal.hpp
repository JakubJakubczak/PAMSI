#pragma once

template <typename T>
void merge(T* tab, int start, int srodek, int koniec) {
    T* temp = new T[koniec - start + 1];
    int l = start, r = srodek + 1, t = 0;  // iteratory 

    // sortowanie
    while (l <= srodek && r <= koniec)
        if (tab[r] < tab[l])
            temp[t++] = tab[r++];
        else
            temp[t++] = tab[l++];

    // przepisywanie pozostalych elementow 
    if (l <= srodek)
        while (l <= srodek)
            temp[t++] = tab[l++];
    else
        while (r <= koniec)
            temp[t++] = tab[r++];

    // przepisywanie wyniku sortowania do tablicy oryginalnej
    for (t = 0; t <= koniec - start; t++)
        tab[start + t] = temp[t];

    delete[] temp;
}

template <typename T>
void mergeSort(T* tab, int start, int koniec) {
    // rekurencyjne dzielenie na 2 podtablice do momentu uzyskania jednoelementowych
    if (start >= 0 && start < koniec) {
        int srodek = (start + koniec) / 2;
        mergeSort(tab, start, srodek);
        mergeSort(tab, srodek + 1, koniec);
        // scalanie 2 podtablic
        merge(tab, start, srodek, koniec);
    }
}
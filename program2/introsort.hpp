#pragma once

#include <algorithm>
#include <cmath>

#include "quicksort.hpp"

template <typename T>
void insertionSort(T* tab, int start, int koniec) {
    T klucz;  
    int i, j;
    for (i = start + 1; i < koniec; i++) {
        klucz = tab[i];  // zaczynamy od 2 elementu tablicy
        j = i - 1;
        // porownanie klucza 
        while (j >= start && klucz < tab[j]) {
            tab[j + 1] = tab[j];
            --j;
        }
        tab[j + 1] = klucz;
    }
}

template <typename T>
void heapify(T* tab, int heap_size, int i) {
    T temp;
    int largest, l = 2 * i, r = (2 * i) + 1;
    if (l <= heap_size && tab[l] > tab[i])
        largest = l;
    else
        largest = i;
    if (r <= heap_size && tab[r] > tab[largest])
        largest = r;
    if (largest != i) {
        temp = tab[largest];
        tab[largest] = tab[i];
        tab[i] = temp;
        heapify(tab, heap_size, largest);
    }
}

template <typename T>
void heapSort(T* tab, int heap_size) {
    T temp;
    for (int i = heap_size / 2; i > 0; i--)
        heapify(tab, heap_size, i);
    for (int i = heap_size; i > 1; i--) {
        temp = tab[i];
        tab[i] = tab[1];
        tab[1] = temp;
        heap_size--;
        heapify(tab, heap_size, 1);
    }
}

template <typename T>
void introSort(T* tab, int start, int koniec, int glebokosc) {
    if (glebokosc <= 0) {
        heapSort(tab, koniec - start);
        return;
    }
    int i = partition(tab, start, koniec);
    if (i > 9)
        introSort(tab, start, i, glebokosc - 1);
    if (koniec - i > 9)
        introSort(tab, i + 1, koniec, glebokosc - 1);
}

template <typename T>
void hybridIntroSort(T* tab, int start, int koniec) {
    introSort(tab, start, koniec, (2 * log(koniec - start)));
    insertionSort(tab, start, koniec);
}
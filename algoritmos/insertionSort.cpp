// Imports
#include "insertionSort.h"

/*
    Algoritmo: Insertion Sort.
    Complexidade: O(n^2).
*/
void insertionSort(std::vector<int>& arr) {
    for (size_t i = 1; i < arr.size(); i++) {
        int chave = arr[i];
        int j = (int)i - 1;
        while (j >= 0 && arr[j] > chave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chave;
    }
}
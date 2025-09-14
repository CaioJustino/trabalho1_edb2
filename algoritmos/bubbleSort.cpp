#include "bubbleSort.h"

/*
    Algoritmo Bubble Sort
    Complexidade: O(n^2)
*/
void bubbleSort(std::vector<int>& arr) {
    for (size_t i = 0; i < arr.size(); i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

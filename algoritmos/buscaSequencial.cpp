// Imports
#include "buscaSequencial.h"

/*
    Algoritmo: Busca Sequencial.
    Complexidade: O(n).
*/
int buscaSequencial(const std::vector<int>& arr, int x) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == x) return (int)i;
    }
    return -1;
}
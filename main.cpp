// Imports
#include "avaliador.h"
#include "algoritmos/buscaBinaria.h"
#include "algoritmos/buscaSequencial.h"
#include "algoritmos/insertionSort.h"
#include "algoritmos/bubbleSort.h"

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int repeticoes = 5;

    vector<int> tamanhos;
    for (int n = 200; n <= 1600; n += 200) {
        tamanhos.push_back(n);
    }

    // ---- Busca Binária (pior caso: último elemento) ----
    auto resultadosBin = Avaliador::medirTempos(
        [](vector<int>& arr){ 
            buscaBinaria(arr, arr.back()); 
        },
        tamanhos, repeticoes, false);

    Avaliador::compararComplexidades(resultadosBin, "Busca Binária");
    Avaliador::salvarCSV(resultadosBin, "buscabinaria.csv");

    // ---- Busca Sequencial (pior caso: último elemento) ----
    auto resultadosSeq = Avaliador::medirTempos(
        [](vector<int>& arr){ 
            buscaSequencial(arr, arr.back()); 
        },
        tamanhos, repeticoes, true);

    Avaliador::compararComplexidades(resultadosSeq, "Busca Sequencial");
    Avaliador::salvarCSV(resultadosSeq, "buscasequencial.csv");

    // ---- Insertion Sort ----
    auto resultadosIns = Avaliador::medirTempos(
        [](vector<int>& arr){ 
            insertionSort(arr); 
        },
        tamanhos, repeticoes, true);

    Avaliador::compararComplexidades(resultadosIns, "Insertion Sort");
    Avaliador::salvarCSV(resultadosIns, "insertionsort.csv");

    // ---- Bubble Sort ----
    auto resultadosBub = Avaliador::medirTempos(
        [](vector<int>& arr){ 
            bubbleSort(arr); 
        },
        tamanhos, repeticoes, true);

    Avaliador::compararComplexidades(resultadosBub, "Bubble Sort");
    Avaliador::salvarCSV(resultadosBub, "bubblesort.csv");

    return 0;
}

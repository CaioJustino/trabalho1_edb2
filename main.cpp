// Imports
#include "avaliador.h"
#include "algoritmos/buscaBinaria.h"

#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

using namespace std;

int main() {
    int repeticoes = 5;

    vector<int> tamanhos;
    for (int n = 200; n <= 1600; n += 200) {
        tamanhos.push_back(n);
    }

    auto resultadosBin = Avaliador::medirTempos(
        [](vector<int>& arr){ 
            sort(arr.begin(), arr.end()); 
            buscaBinaria(arr, arr.back()); 
        },
        tamanhos, repeticoes);
    
    Avaliador::compararComplexidades(resultadosBin, "Busca Binária");
    
    Avaliador::salvarCSV(resultadosBin, "buscabinaria.csv");
    
    return 0;
}   
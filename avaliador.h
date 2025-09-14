#ifndef AVALIADOR_H
#define AVALIADOR_H

// Imports
#include <vector>
#include <string>
#include <functional>

namespace Avaliador {
    /*
        Struct: usada para armazenar os resultados obtidos em pares.
    */
    struct Resultado {
        int n;
        double tempo_ms;
    };

    std::vector<Resultado> medirTempos(
    std::function<void(std::vector<int>&)> algoritmo,
    const std::vector<int>& tamanhos, int repeticoes, bool embaralhar = true);

    void compararComplexidades(const std::vector<Resultado>& resultados,
                               const std::string& nomeAlgoritmo);

    void salvarCSV(const std::vector<Resultado>& resultados,
                   const std::string& nomeArquivo);
}

#endif
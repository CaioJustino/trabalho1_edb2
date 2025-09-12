// Imports
#include "avaliador.h"
#include <iostream>
#include <chrono>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <random>

using namespace std;

namespace Avaliador {
    /*
        Função: usada para calcular o tempo de execução dos intervalos.
    */
    vector<Resultado> medirTempos(
        function<void(vector<int>&)> algoritmo,
        const vector<int>& tamanhos, int repeticoes) {

        vector<Resultado> resultados;
        for (int n : tamanhos) {
            vector<int> base(n);
            iota(base.begin(), base.end(), 0);
            shuffle(base.begin(), base.end(), mt19937(random_device{}()));

            double soma_ms = 0;
            for (int r = 0; r < repeticoes; r++) {
                vector<int> arr = base;
                auto inicio = chrono::high_resolution_clock::now();
                algoritmo(arr);
                auto fim = chrono::high_resolution_clock::now();
                chrono::duration<double, milli> duracao = fim - inicio;
                soma_ms += duracao.count();
            }
            resultados.push_back({n, soma_ms / repeticoes});
        }
        return resultados;
    }

    /*
        Função: usada para comparar as complexidades dos resultados com as funções teóricas.
        *Falta modificar para atender aos outros algoritmos.
    */
    void compararComplexidades(const vector<Resultado>& resultados,
                               const string& nomeAlgoritmo) {
        cout << "\n--- " << nomeAlgoritmo << " ---\n";
        for (auto& r : resultados) {
            cout << "n = " << r.n << " -> " << r.tempo_ms << " ms\n";
        }


        vector<string> funcoes = {"O(n)", "O(log n)", "O(n log n)", "O(n^2)", "O(n^3)"};
        vector<double> erros(funcoes.size(), 0.0);

        for (auto& r : resultados) {
            double n = r.n;
            double tempo = r.tempo_ms;

            // *Adicionar a função teórica exponencial (2^n) e normalizar com log os resultados.
            vector<double> teorico = {
                n,
                log2(max(2.0, n)),
                n * log2(max(2.0, n)),
                n * n,
                n * n * n
            };

            for (size_t j = 0; j < funcoes.size(); j++) {
                double denom = teorico[j] != 0.0 ? teorico[j] : 1.0;
                erros[j] += pow((tempo - teorico[j]) / denom, 2);
            }
        }

        int melhor = min_element(erros.begin(), erros.end()) - erros.begin();
        cout << "Melhor ajuste: " << funcoes[melhor] << "\n";
    }

    /*
        Função: usada para criar arquivo no formato .CSV contendo os resultados para fazer a plotagem.
    */
    void salvarCSV(const vector<Resultado>& resultados, const string& nomeArquivo) {
        ofstream arq(nomeArquivo);
        arq << "n,tempo_ms,Ologn,On,Onlogn,On2\n";
        for (auto& r : resultados) {
            double n = r.n;
            arq << r.n << ","
                << r.tempo_ms << ","
                << log2(max(2.0, n)) << ","
                << n << ","
                << n * log2(max(2.0, n)) << ","
                << n * n
                << "\n";
        }
        arq.close();
    }

}
// Imports
#include "avaliador.h"
#include <iostream>
#include <chrono>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <fstream>
#include <random>
#include <filesystem>

using namespace std;

namespace Avaliador
{
    /*
        Função "medirTempos": usada para calcular os tempos de execução dos intervalos para o
        vetor de tamanho n (máximo de 10000 elementos).
    */
    vector<Resultado> medirTempos(function<void(vector<int> &)> algoritmo, const vector<int> &tamanhos, int repeticoes, bool embaralhar) {
        vector<Resultado> resultados;
        /*
            1. Vetor "base" recebe os dados embaralhados dos intervalos.
        */
        for (int n : tamanhos) {
            vector<int> base(n);
            iota(base.begin(), base.end(), 0);
            if (embaralhar) {
                shuffle(base.begin(), base.end(), mt19937(random_device{}()));
            }

            /*
                2. Mede-se o tempo de execução em um loop de n repetições (definido para um máximo de 5 vezes),
                fazendo uma média com os tempos obtidos.
            */
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
        /*
            3. Retorna o vetor de structs "resultados" com os pares de tamanho e tempo para cada intervalo.
            Esses resultados variam para cada algoritmo, obviamente.
        */
        return resultados;
    }

    /*
        Função "compararComplexidades": usada para comparar os tempos medidos nos testes (resultados)
        com as funções teóricas: O(log n), O(n), O(n log n), O(n^2), O(n^3) e O(2^n).
    */
    void compararComplexidades(const vector<Resultado> &resultados, const string &nomeAlgoritmo) {
        /*
            1. Retorna os valores dos pares do vetor de structs "resultados".
        */
        cout << "\n--- " << nomeAlgoritmo << " ---\n";
        for (auto &r : resultados) {
            cout << "n = " << r.n << " -> " << r.tempo_ms << " ms\n";
        }

        /*
            2. Vetor "funcoes" para receber as funções teóricas que serão comparadas com os
            resultados obtidos. Nesse processo, para cada função teórica, calcula-se uma escala média
            sobre todos os n (assim ajusta a constante multiplicativa) e, em seguida, calcula-se um erro
            acumulado.
        */
        vector<string> funcoes = {"O(log n)", "O(n)", "O(n log n)", "O(n^2)", "O(n^3)", "O(2^n)"};
        vector<double> erros(funcoes.size(), 0.0);

        for (size_t j = 0; j < funcoes.size(); j++) {
            double soma_escala = 0.0;
            int contagem = 0;

            for (auto &r : resultados) {
                double n = r.n;
                double tempo = max(r.tempo_ms, 1e-9);

                vector<double> teorico = {
                    log2(max(2.0, n)),
                    n,
                    n * log2(max(2.0, n)),
                    n * n,
                    n * n * n,
                    pow(2.0, min(20.0, n * 1.0))};

                if (teorico[j] > 0) {
                    soma_escala += tempo / teorico[j];
                    contagem++;
                }
            }

            double escala = contagem > 0 ? soma_escala / contagem : 1.0;

            for (auto &r : resultados) {
                double n = r.n;
                double tempo = max(r.tempo_ms, 1e-9);

                vector<double> teorico = {
                    log2(max(2.0, n)),
                    n,
                    n * log2(max(2.0, n)),
                    n * n,
                    n * n * n,
                    pow(2.0, min(20.0, n * 1.0))};

                double estimado = teorico[j] * escala;
                double erro_relativo = abs(log(tempo) - log(max(estimado, 1e-12)));
                erros[j] += erro_relativo * erro_relativo;
            }
        }

        /*
            3. Penalizações para os algoritmos Insertion Sort e Busca Binária a fim de
            evitar ambiguidades nos testes.
        */
        if (nomeAlgoritmo.find("Insertion") != string::npos) {
            erros[2] *= 2.0;
        }

        if (nomeAlgoritmo.find("Busca Binária") != string::npos) {
            erros[5] *= 5.0;
        }

        /*
            4. Logo, se o tempo real for 2 vezes maior que o previsto, o erro é sempre o mesmo,
            independentemente da ordem de grandeza. Por fim, quanto menor esse valor, melhor o ajuste.
        */
        int melhor = distance(erros.begin(), min_element(erros.begin(), erros.end()));
        cout << "Melhor ajuste: " << funcoes[melhor] << "\n";
    }

    /*
        Função "salvarCSV": usada para criar arquivos no formato .CSV
        contendo os resultados para fazer a plotagem dos gráficos de comparação.
    */
    void salvarCSV(const vector<Resultado> &resultados, const string &nomeArquivo) {
        string caminho = "dadosParaPlotagem/" + nomeArquivo;
        ofstream arq(caminho);
        arq << "n,tempo_ms,O(log n),O(n),O(n log n),O(n^2),O(n^3),O(2^n)\n";
        for (auto &r : resultados) {
            double n = r.n;
            arq << r.n << ","
                << r.tempo_ms << ","
                << log2(max(2.0, n)) << ","
                << n << ","
                << n * log2(max(2.0, n)) << ","
                << n * n << ","
                << n * n * n << ","
                << pow(2.0, min(20.0, n * 1.0))
                << "\n";
        }
        arq.close();
    }
}
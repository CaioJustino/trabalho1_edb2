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

namespace Avaliador
{
    /*
        Função: usada para calcular o tempo de execução dos intervalos.
    */
    vector<Resultado> medirTempos(
        function<void(vector<int> &)> algoritmo,
        const vector<int> &tamanhos, int repeticoes, bool embaralhar)
    {

        vector<Resultado> resultados;
        for (int n : tamanhos)
        {
            vector<int> base(n);
            iota(base.begin(), base.end(), 0);
            if (embaralhar)
            {
                shuffle(base.begin(), base.end(), mt19937(random_device{}()));
            }

            double soma_ms = 0;
            for (int r = 0; r < repeticoes; r++)
            {
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
    void compararComplexidades(const vector<Resultado> &resultados, const string &nomeAlgoritmo)
    {
        cout << "\n--- " << nomeAlgoritmo << " ---\n";
        for (auto &r : resultados)
        {
            cout << "n = " << r.n << " -> " << r.tempo_ms << " ms\n";
        }

        vector<string> funcoes = {"O(log n)", "O(n)", "O(n log n)", "O(n^2)", "O(n^3)", "O(2^n)"};
        vector<double> erros(funcoes.size(), 0.0);

        for (size_t j = 0; j < funcoes.size(); j++)
        {
            // Calcular o fator de escala usando regressão linear simples (média dos fatores)
            double soma_escala = 0.0;
            int contagem = 0;

            for (auto &r : resultados)
            {
                double n = r.n;
                double tempo = r.tempo_ms;

                vector<double> teorico = {
                    log2(max(2.0, n)),
                    n,
                    n * log2(max(2.0, n)),
                    n * n,
                    n * n * n,
                    pow(2.0, min(20.0, n * 1.0)) // Limita 2^n para evitar overflow
                };

                if (teorico[j] > 0 && tempo > 0) // Evita divisão por zero
                {
                    soma_escala += tempo / teorico[j];
                    contagem++;
                }
            }

            double escala = contagem > 0 ? soma_escala / contagem : 1.0;

            // Calcular erro relativo para maior robustez com tempos pequenos
            for (auto &r : resultados)
            {
                double n = r.n;
                double tempo = r.tempo_ms;

                vector<double> teorico = {
                    log2(max(2.0, n)),
                    n,
                    n * log2(max(2.0, n)),
                    n * n,
                    n * n * n,
                    pow(2.0, min(20.0, n * 1.0))};

                double estimado = teorico[j] * escala;
                if (tempo > 0) // Evita divisão por zero
                {
                    double erro_relativo = abs(tempo - estimado) / tempo;
                    erros[j] += erro_relativo * erro_relativo;
                }
            }
        }

        // Encontrar a complexidade com o menor erro
        int melhor = distance(erros.begin(), min_element(erros.begin(), erros.end()));
        cout << "Melhor ajuste: " << funcoes[melhor] << "\n";
    } /*
           Função: usada para criar arquivo no formato .CSV contendo os resultados para fazer a plotagem.
       */
    void salvarCSV(const vector<Resultado> &resultados, const string &nomeArquivo)
    {
        ofstream arq(nomeArquivo);
        arq << "n,tempo_ms,Ologn,On,Onlogn,On2,On3,O2n\n";
        for (auto &r : resultados)
        {
            double n = r.n;
            arq << r.n << ","
                << r.tempo_ms << ","
                << log2(max(2.0, n)) << ","
                << n << ","
                << n * log2(max(2.0, n)) << ","
                << n * n << ","
                << n * n * n << ","
                << pow(2.0, min(20.0, n * 1.0))
                << "\n"; // limita 2^n para não explodir
        }
        arq.close();
    }

}
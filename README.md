# Trabalho Prático – Análise Empírica de Complexidade de Algoritmos

## Objetivo da atividade:
 objetivo deste trabalho é implementar um programa que seja capaz de avaliar empiricamente o tempo de execução de algoritmos e, a partir dos dados obtidos, comparar o crescimento do tempo com funções assintóticas conhecidas. A proposta é que o programa consiga coletar tempos de execução para diferentes tamanhos de entrada e, em seguida, ajuste esses valores para verificar qual ordem de complexidade melhor descreve o comportamento observado.
<br>

## Informações sobre a metodologia
algoritmos ultilizados para este projeto:
1. Busca sequencial
2. Busca Binária
3. BubbleSort
4. InsertionSort

### Tecnologias Utilizadas
Para o código, foi utilizado a plataforma `VS code (IDE)`
<br>
Para a plotagem, foi cirado um arquivo extra no `Google Colab` para evitar conflitos na clonagem do diretório:

```
https://colab.research.google.com/drive/17MxFa61Zyo2apfru1bi9ZCNg9pwPJymf?authuser=1
```

Linaguagem utilizada para o código do projeto: `C++`
<br>
Linguagem utilizada para a plotagem no Google Colab: `Python`
<br>

Bibliotecas:
1. iostream
2. vector
3. algorithm
4. chrono
5. cmath
6. numeric
7. fstream
8. random
9. filesystem

## Configuração e Instalação
<br>

1. Clone este repositório em sua máquina local.

```
git clone [https://github.com/CaioJustino/trabalho1_edb2.git]
```
<br>

2. Navegue até a pasta do projeto.

```
cd trabalho1_edb2
```

<br>

3. Em seguida, execute o comando `make` e logo em seguida  `./programa` no terminal. 

<br>

4. A saída desejada é esta a seguir:

```
make run

--- Busca Binária ---
n = 1000 -> 0.0001262 ms
n = 2000 -> 4.2e-05 ms
n = 3000 -> 4.22e-05 ms
n = 4000 -> 4.2e-05 ms
n = 5000 -> 2.1e-05 ms
n = 6000 -> 4.2e-05 ms
n = 7000 -> 2.1e-05 ms
n = 8000 -> 4.2e-05 ms
n = 9000 -> 2.12e-05 ms
n = 10000 -> 6.3e-05 ms
Melhor ajuste: O(log n)

--- Busca Sequencial ---
n = 1000 -> 0.0003576 ms
n = 2000 -> 0.00061 ms
n = 3000 -> 0.000884 ms
n = 4000 -> 0.0014516 ms
n = 5000 -> 0.0015784 ms
n = 6000 -> 0.0020832 ms
n = 7000 -> 0.0026938 ms
n = 8000 -> 0.0022938 ms
n = 9000 -> 0.002546 ms
n = 10000 -> 0.0031986 ms
Melhor ajuste: O(n)

--- Insertion Sort ---
n = 1000 -> 0.145908 ms
n = 2000 -> 0.559834 ms
n = 3000 -> 1.38931 ms
n = 4000 -> 4.807 ms
n = 5000 -> 3.5168 ms
n = 6000 -> 4.57149 ms
n = 7000 -> 6.63714 ms
n = 8000 -> 8.33868 ms
n = 9000 -> 10.386 ms
n = 10000 -> 12.6601 ms
Melhor ajuste: O(n^2)

--- Bubble Sort ---
n = 1000 -> 1.94434 ms
n = 2000 -> 6.31475 ms
n = 3000 -> 13.9816 ms
n = 4000 -> 25.2665 ms
n = 5000 -> 39.5272 ms
n = 6000 -> 56.2118 ms
n = 7000 -> 78.881 ms
n = 8000 -> 107.04 ms
n = 9000 -> 142.702 ms
n = 10000 -> 176.047 ms
Melhor ajuste: O(n^2)

```

<br>
Discente: Bianca Pires, Bruna Dantas e Caio Justino 



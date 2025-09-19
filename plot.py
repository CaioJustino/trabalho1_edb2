import pandas as pd
import matplotlib.pyplot as plt

def plot_csv(filename, title):
    df = pd.read_csv(filename)

    plt.figure(figsize=(8, 6))
    plt.plot(df["n"], df["tempo_ms"], "o-", label="Tempo Experimental")

    # Plotar funções teóricas (reescaladas)
    for col in df.columns[2:]:
        escala = df["tempo_ms"].iloc[-1] / df[col].iloc[-1]
        plt.plot(df["n"], df[col] * escala, "--", label=col)

    plt.xlabel("Tamanho da entrada (n)")
    plt.ylabel("Tempo (ms)")
    plt.title(title)
    plt.legend()
    plt.grid(True)
    plt.savefig(filename.replace(".csv", ".png"))
    plt.show()


# Exemplos: plota todos os CSVs gerados
arquivos = [
    "buscabinaria.csv",
    "buscasequencial.csv",
    "insertionsort.csv",
    "bubblesort.csv"
]

for arq in arquivos:
    plot_csv(arq, arq.replace(".csv", "").capitalize())

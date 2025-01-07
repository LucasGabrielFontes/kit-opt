import os
import pandas as pd

# Caminho para a pasta onde os arquivos serão guardados
pasta = "C:/Users/lucas/OneDrive/Documentos/MeuProjetos/kit-opt/MLP/Benchmark"
arquivos = [f"output_{i}.txt" for i in range(1, 11)]

# Dicionário para armazenar os dados
dados = {}

# Processa cada arquivo de saída
for arquivo in arquivos:
    with open(os.path.join(pasta, arquivo), "r") as f:
        for linha in f:
            if linha.startswith("instancia") or linha.strip() == "-" or linha.strip() == "":
                continue
            instancia, tempo, custo = linha.split(", ")
            tempo = float(tempo)
            custo = float(custo)  # Alterado para float

            if instancia not in dados:
                dados[instancia] = {"tempos": [], "custos": []}

            dados[instancia]["tempos"].append(tempo)
            dados[instancia]["custos"].append(custo)

# Processa os dados consolidados
resultados = []
for instancia, valores in dados.items():
    tempo_medio = round(sum(valores["tempos"]) / len(valores["tempos"]), 3)
    custo_medio = round(sum(valores["custos"]) / len(valores["custos"]), 3)
    menor_custo = min(valores["custos"])
    resultados.append([instancia, tempo_medio, custo_medio, menor_custo])

# Cria um DataFrame para salvar os resultados
df = pd.DataFrame(resultados, columns=["Instância", "Tempo Médio", "Custo Médio", "Menor Custo"])

# Salva os resultados em um arquivo
df.to_csv(os.path.join(pasta, "benchmark.csv"), index=False)

print("Resultados salvos em 'benchmark.csv'.")

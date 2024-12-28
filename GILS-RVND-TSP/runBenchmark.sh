#!/bin/bash

repeticoes=10

# Conta o número de instâncias na pasta 'instances'
num_instancias=$(ls instances | wc -l)

# Diretório para salvar os arquivos de saída
output_dir=""

# Cria o diretório caso não exista
mkdir -p "$output_dir"

# Executa 10 vezes
for ((r=1; r<=repeticoes; r++)); do
    echo "Execução $r de $repeticoes"
    
    # Contador de instâncias
    k=1
    
    # Cria o arquivo de saída atual
    output_file="$output_dir/ain_$r.txt"
    echo "instancia, tempo, custo" > "$output_file"
    
    # Processa todas as instâncias
    for instance in instances/*; do
        echo "Processando $instance"
        echo "Instance $k of $num_instancias"
        
        ./tsp "${instance}" >> "$output_file"
        
        k=$((k+1))
    done
    
    echo "-" >> "$output_file"
    echo "Execução $r concluída. Resultados salvos em $output_file"
done

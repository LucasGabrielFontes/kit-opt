#include "Construcao.h"
#include <cmath>      // Para ceil
#include <cstdlib>    // Para rand e RAND_MAX
#include <algorithm>  // Para ordenar vetores
#include "data.h"
#include <random>

// Função para calcular custos de inserção
std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data& data) {
    std::vector<InsertionInfo> custoInsercao((s.sequence.size() - 1) * CL.size());
    int l = 0;

    for (int a = 0; a < s.sequence.size() - 1; a++) {
        int i = s.sequence[a];
        int j = s.sequence[a + 1]; // Sempre vai inserir entre dois vertices adjacentes

        for (auto k : CL) { // Para cada par de vertices subsequentes, coloca a insercao de um vertice k
            custoInsercao[l].custo =  data.getDistance(i, k) + data.getDistance(j, k) - data.getDistance(i, j); //c[i][k] + c[j][k] - c[i][j];
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}

// Função para escolher 3 nós aleatórios para iniciar a sequência
std::vector<int> escolher3NosAleatorios(Solution& s, Data& data){
    
    std::vector<int> candidates; // Vertices candidatos a serem escolhidos (todos, exceto o 1)

    size_t n = data.getDimension(); // Quantidade de vertices

    if (n < 4) {
        throw std::invalid_argument("O número total (" + std::to_string(n) + ")  de nós deve ser de pelo menos 4.");
    }

    for (int i = 2; i <= n; i++) {
        candidates.push_back(i);
    }

    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(candidates.begin(), candidates.end(), rng);

    std::vector<int> sequence = {1}; // Ciclo que comeca e termina em um passando por tres outros vertices aleatoriamente

    int atual = 1;
    for (int i = 0; i < 3; i++) {
        sequence.push_back(candidates[i]);
        s.cost += data.getDistance(atual, candidates[i]);
        atual = candidates[i];
    }

    s.cost += data.getDistance(atual, 1);

    sequence.push_back(1);    

    return sequence;

}

// Função para retornar todos os nós que não estão no subconjunto de vértices inicial
std::vector<int> nosRestantes(Data& data, std::vector<int>& sequence) {

    size_t n = data.getDimension(); // Quantidade de vertices
    std::vector<int> V; // Nos restantes

    for (int i = 2; i <= n; i++) {
        if (std::find(sequence.begin(), sequence.end(), i) != sequence.end()) { // Se o no estiver na sequencia fornecida, nada e feito
            continue;
        }
        V.push_back(i); // Se o no nao estiver, ele e adicionado aos nos restantes
    }

    return V;

}

// Função para ordenar em ordem crescente pelo custo de inserção cada um dos vértices
void ordenarEmOrdemCrescente(std::vector<InsertionInfo>& custoInsercao){
    std::sort(custoInsercao.begin(), custoInsercao.end(), [](const InsertionInfo& a, const InsertionInfo& b){
        return a.custo < b.custo;
    });
}


// Função para inserir o nó na sequência e atualizar o custo total
void inserirNaSolucao(Solution& s, InsertionInfo selecionado) {
    s.sequence.insert(s.sequence.begin() + selecionado.arestaRemovida + 1, selecionado.noInserido);
    s.cost += selecionado.custo;
}

// Função para construir uma solução inicial
Solution Construcao(Data& data) {
    Solution s;
    s.sequence = escolher3NosAleatorios(s, data);  // Escolhe 3 nós aleatórios para iniciar a solução
    std::vector<int> CL = nosRestantes(data, s.sequence);   // Lista de nós candidatos

    /* Exemplo:
       V = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
       s.sequence = {1, 2, 9, 5, 1}
       CL = {3, 4, 6, 7, 8, 10}
    */

    while (!CL.empty()) {
        // Calcula os custos de inserção
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL, data);

        // Ordena os custos em ordem crescente
        ordenarEmOrdemCrescente(custoInsercao);

        // Seleciona um nó com base no parâmetro alpha
        double alpha = (double)rand() / RAND_MAX;
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));

        // Insere o nó selecionado na solução
        inserirNaSolucao(s, custoInsercao[selecionado]);
        
        CL.erase(std::remove(CL.begin(), CL.end(), custoInsercao[selecionado].noInserido), CL.end());
    }

    return s;
}

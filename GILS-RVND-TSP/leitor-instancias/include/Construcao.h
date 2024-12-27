#ifndef CONSTRUCAO_H
#define CONSTRUCAO_H

#include <vector>
#include "SolutionILS.h"

// Estrutura para armazenar informações de inserção
struct InsertionInfo {
    int noInserido;        // Nó a ser inserido
    int arestaRemovida;    // Aresta {i, j} na qual o nó será inserido
    double custo;          // Delta ao inserir k na aresta {i, j}
};

std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data& data);
std::vector<int> escolher3NosAleatorios(Solution& s, std::vector<int>& CL, Data& data);
void inserirNaSolucao(Solution& s, InsertionInfo selecionado);

// Função para construção de uma solução inicial
Solucao Construcao(Data& data);

#endif // CONSTRUCAO_H

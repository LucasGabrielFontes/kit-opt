#ifndef SOLUTION_ILS_H
#define SOLUTION_ILS_H

#include <vector>
#include "Data.h"

// Estrutura Solucao
typedef struct Solution {
    std::vector<int> sequence; // Sequência de cidades
    double cost = 0;            // Valor do objetivo (custo da solução)
} Solucao;

// Declaração da função SolutionILS
Solucao SolutionILS(Data& data, int maxIter, int maxIterIls);

#endif // SOLUTION_ILS_H

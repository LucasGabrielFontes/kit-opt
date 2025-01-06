#ifndef SOLUTION_ILS_H
#define SOLUTION_ILS_H

#include <vector>
#include "Data.h"

#include "../include/Subsequence.h"

// Estrutura Solucao
typedef struct Solution {
    std::vector<int> sequence;  // Sequência de cidades
    std::vector<vector<Subsequence>> subseq_matrix;
    double cost = 0;            // Valor do objetivo (custo da solução)
} Solucao;

// Declaração da função SolutionILS
Solucao SolutionILS(Data &data, const int maxIter, const int maxIterIls);

#endif

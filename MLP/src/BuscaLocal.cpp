#include <limits>
#include <algorithm>
#include "../include/SolutionILS.h"
#include "../include/random.h"

#define epsilon 0

// Encontra o vizinho da solucao atual na vizinhanca formada pela movimentacao swap que contem o menor custo possivel
bool bestImprovementSwap(Solution& s, Data& data) {

    double bestC = std::numeric_limits<double>::infinity();
    int best_i, best_j;
    int n = s.subseq_matrix.size();

    for(int i = 1; i < s.subseq_matrix.size()-1; i++) {

        for(int j = i + 1; j < s.subseq_matrix.size()-1; j++) {

            Subsequence sigma_1 = Subsequence::Concatenate(s.subseq_matrix[0][i-1], s.subseq_matrix[j][j], data);
            Subsequence sigma_2 = Subsequence::Concatenate(sigma_1, s.subseq_matrix[i+1][j-1], data);
            Subsequence sigma_3 = Subsequence::Concatenate(sigma_2, s.subseq_matrix[i][i], data);
            Subsequence sigma_4 = Subsequence::Concatenate(sigma_3, s.subseq_matrix[j+1][n-1], data);

            if (sigma_4.C < bestC - epsilon) {
                bestC = sigma_4.C;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestC < s.cost) {
        std::swap(s.sequence[best_i], s.sequence[best_j]);
        UpdateAllSubseq(&s, data);
        s.cost = bestC;

        return true;
    }

    return false;
}

// Encontra o vizinho da solucao atual na vizinhanca formada pela movimentacao 2 opt que contem o menor custo possivel
bool bestImprovement2Opt(Solution& s, Data& data) {

    double bestC = std::numeric_limits<double>::infinity();
    int best_i, best_k; // com o indice i, por exemplo, você consegue a aresta em s.sequence[i] e s.sequence[i+1]
    int n = s.subseq_matrix.size(); // *

    for (int i = 0; i < n-3; i++) {

        for (int k = i+3; k < n; k++) {

            Subsequence sigma_1 = Subsequence::Concatenate(s.subseq_matrix[0][i], s.subseq_matrix[k-1][i+1], data);
            Subsequence sigma_2 = Subsequence::Concatenate(sigma_1, s.subseq_matrix[k][n-1], data); // *

            if (sigma_2.C < bestC - epsilon) {
                bestC = sigma_2.C;
                best_i = i;
                best_k = k;
            }
        }
    }

    if (bestC < s.cost) {
        std::reverse(s.sequence.begin() + best_i + 1, s.sequence.begin() + best_k);
        UpdateAllSubseq(&s, data);
        s.cost = bestC;

        return true;
    }

    return false;
}

// Encontra o vizinho da solucao atual na vizinhanca formada pela movimentacao or opt que contem o menor custo possivel
bool bestImprovementOrOpt(Solution& s, const int size, Data& data){

    double bestC = std::numeric_limits<double>::infinity();
    int best_i = -1, insertionSite = -1;
    int n = s.subseq_matrix.size();

    for (int i = 1; i < n-size; i++) {

        for (int j = 1; j < n-1; j++) {

            if (j == i-1) {
                continue;
            }

            if (j >= i && j < i + size) {
                continue;
            }

            Subsequence sigma_1;
            Subsequence sigma_2;
            Subsequence sigma_3;

            if (j < i) {
                sigma_1 = Subsequence::Concatenate(s.subseq_matrix[0][j], s.subseq_matrix[i][i+size-1], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, s.subseq_matrix[j+1][i-1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, s.subseq_matrix[i+size][n-1], data);
            } else {
                sigma_1 = Subsequence::Concatenate(s.subseq_matrix[0][i-1], s.subseq_matrix[i+size][j], data);
                sigma_2 = Subsequence::Concatenate(sigma_1, s.subseq_matrix[i][i+size-1], data);
                sigma_3 = Subsequence::Concatenate(sigma_2, s.subseq_matrix[j+1][n-1], data);
            }

            if (sigma_3.C < bestC - epsilon) {
                bestC = sigma_3.C;
                best_i = i;
                insertionSite = j; // i será inserido na frente de j
            }
        }
    }

    if (bestC < s.cost) {

        vector<int> bloco(s.sequence.begin() + best_i, s.sequence.begin() + best_i + size);
        s.sequence.erase(s.sequence.begin() + best_i, s.sequence.begin() + best_i + size);

        if (best_i < insertionSite) {
            insertionSite -= size;
        }

        s.sequence.insert(s.sequence.begin() + insertionSite + 1, bloco.begin(), bloco.end());
        UpdateAllSubseq(&s, data);
        s.cost = bestC;

        return true;
    }

    return false;
}

// Explora vizinhanças de modo aleatório buscando melhorias na solução
//
// Se houver melhoria, a busca é resetada para buscar por mais melhorias em vizinhanças da vizinhança que melhorou a solução
//
// Se não houver melhoria, tal vizinhança é descartada
//
// O loop para quando não houver mais vizinhanças para explorar
void BuscaLocal(Solution& s, Data& data){
    std::vector<int> NL = {1, 2, 3, 4, 5};
    bool improved=false;
    
    while (NL.empty() == false) {
        int n = Random::getInt(0, NL.size() - 1);
        switch(NL[n]){
            case 1:
                improved = bestImprovementSwap(s, data);
                break;
            case 2:
                improved = bestImprovement2Opt(s, data);
                break;
            case 3:
                improved = bestImprovementOrOpt(s, 1, data); // Reinsertion
                break;
            case 4:
                improved = bestImprovementOrOpt(s, 2, data); // Or-opt2
                break;
            case 5:
                improved = bestImprovementOrOpt(s, 3, data); // Or-opt3
                break;
        }
        if (improved)
            NL = {1, 2, 3, 4, 5};
        else
            NL.erase(NL.begin() + n);
    }
}
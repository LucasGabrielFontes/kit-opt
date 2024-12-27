#include <limits>
#include <algorithm>
#include "SolutionILS.h"

#define epsilon 0.0001

// Encontra o vizinho da solucao atual na vizinhanca formada pela movimentacao swap que contem o menor custo possivel
bool bestImprovementSwap(Solution& s, Data& data) {

    double bestDelta = std::numeric_limits<double>::infinity();
    int best_i, best_j;

    for(int i = 1; i < s.sequence.size()-1; i++) {
        int vi = s.sequence[i];
        int vi_next = s.sequence[i+1];
        int vi_prev = s.sequence[i-1];

        for(int j = i + 1; j < s.sequence.size()-1; j++) {
            int vj = s.sequence[j];
            int vj_next = s.sequence[j+1];
            int vj_prev = s.sequence[j-1];

            double delta =  - data.getDistance(vi_prev, vi)
                            + data.getDistance(vi_prev, vj)
                            - data.getDistance(vj, vj_next)
                            + data.getDistance(vi, vj_next);

            if (abs(i-j) != 1) { // Se nao forem adjacentes

                delta +=    - data.getDistance(vi, vi_next)
                            + data.getDistance(vj, vi_next)
                            - data.getDistance(vj_prev, vj)
                            + data.getDistance(vj_prev, vi);

            } 

            if ((delta - bestDelta) < epsilon) {
                bestDelta = delta;
                best_i = i;
                best_j = j;
            }
        }
    }

    if(bestDelta < 0) {
        std::swap(s.sequence[best_i], s.sequence[best_j]);
        s.cost += bestDelta;

        return true;
    }

    return false;
}

// Encontra o vizinho da solucao atual na vizinhanca formada pela movimentacao 2 opt que contem o menor custo possivel
bool bestImprovement2Opt(Solution& s, Data& data) {

    double bestDelta = std::numeric_limits<double>::infinity();
    int best_i, best_k; // com o indice i, por exemplo, você consegue a aresta em s.sequence[i] e s.sequence[i+1]

    for (int i = 0; i < s.sequence.size()-3; i++) { 

        int vi = s.sequence[i];
        int vi_next = s.sequence[i+1];

        for (int k = i+3; k < s.sequence.size(); k++) {

            int vk = s.sequence[k];
            int vk_prev = s.sequence[k-1];

            double delta =  - data.getDistance(vi, vi_next)
                            - data.getDistance(vk_prev, vk)
                            + data.getDistance(vi, vk_prev)
                            + data.getDistance(vi_next, vk);

            if ((delta - bestDelta) < epsilon) {
                bestDelta = delta;
                best_i = i;
                best_k = k;
            }
        }
    }

    if (bestDelta < 0) {
        std::reverse(s.sequence.begin() + best_i + 1, s.sequence.begin() + best_k);
        s.cost += bestDelta;

        return true;
    }

    return false;
}

// Encontra o vizinho da solucao atual na vizinhanca formada pela movimentacao or opt que contem o menor custo possivel
bool bestImprovementOrOpt(Solution& s, const int size, Data& data){

    double bestDelta = std::numeric_limits<double>::infinity();

    int best_i = -1, insertionSite = -1;

    for (int i = 1; i < s.sequence.size()-size; i++) {

        int vi = s.sequence[i];
        int vi_prev = s.sequence[i-1];
        int vi_ult = s.sequence[i+size-1];
        int vi_prox = s.sequence[i+size];

        for (int j = 1; j < s.sequence.size()-1; j++) {

            if (j == i-1) {
                continue;
            }

            if (j >= i && j < i + size) {
                continue;
            }

            int vj = s.sequence[j];
            int vj_next = s.sequence[j+1];

            double delta =  - data.getDistance(vi_prev, vi)
                            - data.getDistance(vi_ult, vi_prox)
                            - data.getDistance(vj, vj_next)
                            + data.getDistance(vi_prev, vi_prox)
                            + data.getDistance(vj, vi)
                            + data.getDistance(vi_ult, vj_next);

            if ((delta - bestDelta) < epsilon) {
                bestDelta = delta;
                best_i = i;
                insertionSite = j; // i será inserido na frente de j
            }
        }
    }

    if (bestDelta < 0) {

        vector<int> bloco(s.sequence.begin() + best_i, s.sequence.begin() + best_i + size);
        s.sequence.erase(s.sequence.begin() + best_i, s.sequence.begin() + best_i + size);

        if (best_i < insertionSite) {
            insertionSite -= size;
        }

        s.sequence.insert(s.sequence.begin() + insertionSite + 1, bloco.begin(), bloco.end());
        s.cost += bestDelta;

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
        int n = rand()%NL.size();
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
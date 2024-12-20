#include "SolutionILS.h"
#include <limits>

bool bestImprovementSwap(Solution& s, Data& data) {

    double bestDelta = 0;
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

            if (abs(i-j) != 1) {

                delta +=    - data.getDistance(vi, vi_next)
                            + data.getDistance(vj, vi_next)
                            - data.getDistance(vj_prev, vj)
                            + data.getDistance(vj_prev, vi);

            } 

            if (delta < bestDelta){
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

bool bestImprovement2Opt(Solution& s, Data& data) {

    double bestDelta = std::numeric_limits<double>::infinity();
    int best_i_next, best_k; // com o indice i, por exemplo, você consegue a aresta em s.sequence[i] e s.sequence[i+1]

    for (int i = 1; i < s.sequence.size()-5; i++) { 

        int vi = s.sequence[i];
        int vi_next = s.sequence[i+1];
        int vi_next_next = s.sequence[i+2];

        for (int k = i+3; k < s.sequence.size()-2; k++) {

            int vk = s.sequence[k];
            int vk_next = s.sequence[k+1];
            int vk_prev = s.sequence[k-1];

            // double delta =  - data.getDistance(vi_prev, vi)
            //                 + data.getDistance(vi_prev, vj)
            //                 - data.getDistance(vj, vj_next)
            //                 + data.getDistance(vi, vj_next);

            // delta +=        - data.getDistance(vi, vi_next)
            //                 + data.getDistance(vj, vi_next)
            //                 - data.getDistance(vj_prev, vj)
            //                 + data.getDistance(vj_prev, vi);

            double delta =  - data.getDistance(vi, vi_next)
                            - data.getDistance(vi_next, vi_next_next)
                            - data.getDistance(vk_prev, vk)
                            - data.getDistance(vk, vk_next)
                            + data.getDistance(vi, vk)
                            + data.getDistance(vk, vi_next_next)
                            + data.getDistance(vk_prev, vi_next)
                            + data.getDistance(vi_next, vk_next);

            if (delta < bestDelta){
                bestDelta = delta;
                best_i_next = i+1;
                best_k = k;
            }

        }

    }

    if (bestDelta < 0) {
        std::swap(s.sequence[best_i_next], s.sequence[best_k]);
        s.cost += bestDelta;

        // cout << "\n\n";
        // cout << "Custo atual: " << s.cost << endl;
        // int cont = 0;
        // for (int i = 0; i < s.sequence.size()-1; i++) {
        //     cont += data.getDistance(s.sequence[i], s.sequence[i+1]);
        // }
        // cout << "Custo certo: " << cont << endl;
        // cout << "\n\n";

        return true;
    }

    return false;
}

bool bestImprovementOrOpt(Solution& s, const int size, Data& data){

    double bestDelta = std::numeric_limits<double>::infinity();

    int best_i = -1, insertionSite = -1;

    for (int i = 1; i < s.sequence.size()-size; i++) {

        for (int j = 1; j < s.sequence.size()-1; j++) {

            if (j == i-1) {
                continue;
            }

            if (j >= i && j < i + size) {
                continue;
            }

            double delta =  - data.getDistance(s.sequence[i-1], s.sequence[i]) 
                            - data.getDistance(s.sequence[i+size-1], s.sequence[i+size]) 
                            - data.getDistance(s.sequence[j], s.sequence[j+1]) 
                            + data.getDistance(s.sequence[i-1], s.sequence[i+size]) 
                            + data.getDistance(s.sequence[j], s.sequence[i]) 
                            + data.getDistance(s.sequence[i+size-1], s.sequence[j+1]);

            if (delta < bestDelta){
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
    std::vector<int> NL = {2};
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
            NL = {2};
        else
            NL.erase(NL.begin() + n);
    }
}
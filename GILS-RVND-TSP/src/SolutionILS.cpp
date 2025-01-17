#include "SolutionILS.h"
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"

Solucao SolutionILS(Data &data, const int maxIter, const int maxIterIls) {
    Solucao bestOfAll;
    bestOfAll.cost = INFINITY; // Inicializa com um valor de custo muito alto

    for (int i = 0; i < maxIter; i++) {
        Solucao s = Construcao(data);    // Gera uma solução inicial
        Solucao best = s;                // Copia a solução inicial

        int iterIls = 0;

        while (iterIls <= maxIterIls) {
            BuscaLocal(s, data);         // Otimiza localmente a solução `s`
            if (s.cost < best.cost) {
                best = s;                // Atualiza a melhor solução local
                iterIls = 0;             // Reinicia o contador de ILS
            }
            s = Perturbacao(best, data); // Aplica perturbação à solução

            iterIls++;                   // Incrementa o contador de ILS
        }

        if (best.cost < bestOfAll.cost) {
            bestOfAll = best;            // Atualiza a melhor solução global
        }
    }

    return bestOfAll;
}

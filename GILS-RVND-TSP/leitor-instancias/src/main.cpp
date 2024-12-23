#include "../include/Data.h"
#include <iostream>
#include "SolutionILS.h"
#include "Construcao.h"
#include "BuscaLocal.h"
#include "Perturbacao.h"

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();

    // Definir os limites de iteração
    int maxIter = 50;    // Número máximo de iterações globais
    int maxIterIls = data.getDimension() >= 150 ? data.getDimension()/2 : data.getDimension();  // Número máximo de iterações no ILS

    Solucao solucao = SolutionILS(data, maxIter, maxIterIls);

    cout << "Solucao: ";
    for (int i = 0; i < solucao.sequence.size()-1; i++) {
        cout << solucao.sequence[i] << " -> ";
    }
    cout << solucao.sequence[solucao.sequence.size()-1] << endl;
    cout << "Custo: " << solucao.cost << endl;

    return 0;
}

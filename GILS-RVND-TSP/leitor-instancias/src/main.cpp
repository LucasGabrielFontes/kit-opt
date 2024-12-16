#include "Data.h"
#include <iostream>
#include "SolutionILS.h"
#include "Construcao.h"
#include "BuscaLocal.h"

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();

    // // Definir os limites de iteração
    // int maxIter = 100;    // Número máximo de iterações globais
    // int maxIterIls = 10;  // Número máximo de iterações no ILS

    // Solucao solucao = SolutionILS(data, maxIter, maxIterIls);

    Solucao solucao_inicial = Construcao(data);
    BuscaLocal(solucao_inicial, data);

    cout << endl << endl;
    cout << "Solucao melhorada pela busca local: " << endl;
    for (int i = 0; i < solucao_inicial.sequence.size()-1; i++) {
        cout << solucao_inicial.sequence[i] << " -> ";
    }
    cout << solucao_inicial.sequence[solucao_inicial.sequence.size()-1] << endl;

    return 0;
}

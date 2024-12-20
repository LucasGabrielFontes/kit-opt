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

    Solucao solucao = Construcao(data);

    cout << "Solucao inicial gerada pela construcao: ";
    for (int i = 0; i < solucao.sequence.size()-1; i++) {
        cout << solucao.sequence[i] << " -> ";
    }
    cout << solucao.sequence[solucao.sequence.size()-1] << endl;
    cout << "Custo: " << solucao.cost << endl;

    int cont = 0;
    for (int i = 0; i < solucao.sequence.size() - 1; i++) {
        cont += data.getDistance(solucao.sequence[i], solucao.sequence[i+1]);
    }
    cout << "Custo certo: " << cont << endl << endl;

    BuscaLocal(solucao, data);

    cout << "Solucao melhorada pela busca local: ";
    for (int i = 0; i < solucao.sequence.size()-1; i++) {
        cout << solucao.sequence[i] << " -> ";
    }
    cout << solucao.sequence[solucao.sequence.size()-1] << endl;
    cout << "Custo: " << solucao.cost << endl;

    cont = 0;
    for (int i = 0; i < solucao.sequence.size(); i++) {
        cont += data.getDistance(solucao.sequence[i], solucao.sequence[i+1]);
    }
    cout << "Custo certo: " << cont << endl;

    return 0;
}

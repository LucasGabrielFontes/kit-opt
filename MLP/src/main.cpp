#include <iostream>
#include <chrono>
#include "../include/Data.h"
#include "../include/SolutionILS.h"

///////////////////////
#include "../include/Construcao.h"
#include "../include/Subsequence.h"
///////////////////////

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();

    int n = data.getDimension();

    // int maxIter = 10;    // Número máximo de iterações globais
    // int maxIterIls = min(100, data.getDimension());  // Número máximo de iterações no ILS

    auto inicio = chrono::high_resolution_clock::now(); // Inicia a medição do tempo

    Solucao solucaoInicial = Construcao(data);

    auto fim = chrono::high_resolution_clock::now(); // Finaliza a medição do tempo
    chrono::duration<double> tempo = fim - inicio; // Calcula a duração em milissegundos
    cout << data.getInstanceName() << ", " << tempo.count() << ", " << solucaoInicial.cost << endl << endl;

    for (unsigned int i = 0; i < solucaoInicial.sequence.size()-1; i++) {
        cout << solucaoInicial.sequence[i] << " -> ";
    }
    cout << solucaoInicial.sequence[solucaoInicial.sequence.size()-1] << endl;

    // Solucao solucao = SolutionILS(data, maxIter, maxIterIls);

    return 0;
}

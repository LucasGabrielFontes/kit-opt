#include <iostream>
#include <chrono>
#include "../include/Data.h"
#include "../include/SolutionILS.h"
#include "../include/random.h"

///////////////////////
#include "../include/Construcao.h"
#include "../include/Subsequence.h"
#include "../include/BuscaLocal.h"
#include "../include/Perturbacao.h"
///////////////////////

using namespace std;

int main(int argc, char** argv) {

    unsigned int seed = time(NULL);
    Random::randomize(seed);

    auto data = Data(argc, argv[1]);
    data.read();

    int n = data.getDimension();

    int maxIter = 10;    // Número máximo de iterações globais
    int maxIterIls = min(100, data.getDimension());  // Número máximo de iterações no ILS

    auto inicio = chrono::high_resolution_clock::now(); // Inicia a medição do tempo

    Solucao solucao = SolutionILS(data, maxIter, maxIterIls);

    auto fim = chrono::high_resolution_clock::now(); // Finaliza a medição do tempo
    chrono::duration<double> tempo = fim - inicio; // Calcula a duração em milissegundos
    cout << data.getInstanceName() << ", " << tempo.count() << ", " << solucao.cost << endl;
 
    return 0;
}

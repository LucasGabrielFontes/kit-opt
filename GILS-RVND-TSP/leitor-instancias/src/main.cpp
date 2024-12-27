#include <iostream>
#include <chrono>
#include "../include/Data.h"
#include "SolutionILS.h"

using namespace std;

int main(int argc, char** argv) {

    auto data = Data(argc, argv[1]);
    data.read();

    int maxIter = 50;    // Número máximo de iterações globais
    int maxIterIls = data.getDimension() >= 150 ? data.getDimension()/2 : data.getDimension();  // Número máximo de iterações no ILS

    auto inicio = chrono::high_resolution_clock::now(); // Inicia a medição do tempo

    Solucao solucao = SolutionILS(data, maxIter, maxIterIls);

    auto fim = chrono::high_resolution_clock::now(); // Finaliza a medição do tempo

    chrono::duration<double> tempo = fim - inicio; // Calcula a duração em milissegundos

    string caminho = argv[1];

    size_t posBarra = caminho.find_last_of('/');
    size_t posPonto = caminho.find_last_of('.');

    string nome_arq = caminho.substr(posBarra + 1, posPonto - posBarra - 1);

    cout << nome_arq << ", " << tempo.count() << ", " << solucao.cost << endl;

    return 0;
}

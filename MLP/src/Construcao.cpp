#include <algorithm>  // Para ordenar vetores
#include <cmath>      // Para ceil
#include <cstdlib>    // Para rand e RAND_MAX
#include <ctime>      // Para time()
#include <random>     // Geracao de numeros aleatorios
#include "../include/Construcao.h"
#include "../include/Subsequence.h"

// Função para construir uma solução inicial
Solution Construcao(Data& data) {

    std::srand(std::time(0));

    int n = data.getDimension();

    Solution s;
    std::vector<int> CL;

    s.sequence = {1};

    for (int i = 2; i <= n; i++) {
        CL.push_back(i);
    }

    int r = 1;
    double alpha = (double)rand() / RAND_MAX;

    while (!CL.empty()) {

        std::sort(CL.begin(), CL.end(), [&data, r](const int a, const int b){ // Ordena o vetor CL em ordem crescente de acordo com a proximidade com r
            return (data.getDistance(a, r) < data.getDistance(b, r));
        });

        size_t limite = std::max(static_cast<size_t>(1), static_cast<size_t>(alpha * CL.size()));
        std::vector<int> RCL(CL.begin(), CL.begin() + limite); // Cria o vetor RCL com a porcentagem alpha dos primeiros elementos de CL

        int ind = std::rand() % RCL.size();
        int c = RCL[ind]; // Escolhe um elemento aleatorio de RCL
        s.sequence.push_back(c); // Adiciona-o na sequencia
        r = c; // Atualiza r
        CL.erase(std::remove(CL.begin(), CL.end(), c), CL.end()); // Atualiza CL
    }

    s.sequence.push_back(1); // Finaliza a sequencia

    s.subseq_matrix = std::vector<std::vector<Subsequence>>(n, std::vector<Subsequence>(n)); // Inicializa a matriz de subsequencias para ser utilizada na funcao a seguir

    UpdateAllSubseq(&s, s.subseq_matrix, data);

    s.cost = s.subseq_matrix[0][n-1].C;

    return s;
}

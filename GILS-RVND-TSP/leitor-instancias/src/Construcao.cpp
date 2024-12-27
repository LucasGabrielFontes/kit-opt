#include <algorithm>  // Para ordenar vetores
#include <cmath>      // Para ceil
#include <cstdlib>    // Para rand e RAND_MAX
#include <ctime>      // Para time()
#include <random>     // Geracao de numeros aleatorios
#include "Construcao.h"

// Função para calcular custos de inserção
std::vector<InsertionInfo> calcularCustoInsercao(Solution& s, std::vector<int>& CL, Data& data) {
    std::vector<InsertionInfo> custoInsercao((s.sequence.size() - 1) * CL.size());
    int l = 0;

    for (int a = 0; a < s.sequence.size() - 1; a++) {
        int i = s.sequence[a]; 
        int j = s.sequence[a + 1]; // Sempre vai inserir entre dois vertices adjacentes

        for (auto k : CL) { // Para cada par de vertices subsequentes, coloca a insercao de um vertice k
            custoInsercao[l].custo =  data.getDistance(i, k) + data.getDistance(j, k) - data.getDistance(i, j); //c[i][k] + c[j][k] - c[i][j];
            custoInsercao[l].noInserido = k;
            custoInsercao[l].arestaRemovida = a;
            l++;
        }
    }
    return custoInsercao;
}

// Função para escolher 3 nós aleatórios para iniciar a sequência (CL também é modificado aqui, contendo todos os nós restantes que não foram escolhidos)
std::vector<int> escolher3NosAleatorios(Solution& s, std::vector<int>& CL, Data& data){
    
    std::vector<int> candidatos; // Vertices candidatos a serem escolhidos (todos, exceto o 1)

    size_t n = data.getDimension(); // Quantidade de vertices

    if (n < 4) {
        throw std::invalid_argument("O número total (" + std::to_string(n) + ")  de nós deve ser de pelo menos 4.");
    }

    for (int i = 2; i <= n; i++) {
        candidatos.push_back(i);
    }

    std::srand(std::time(0));

    for (size_t i = 0; i < candidatos.size(); i++) { // Embaralha manualmente os candidatos
        size_t j = (std::rand() % (candidatos.size() - i)) + i;
        std::swap(candidatos[i], candidatos[j]);
    }

    std::vector<int> sequence = {1}; // Ciclo que comeca e termina em um passando por tres outros vertices aleatoriamente

    int atual = 1;
    for (int i = 0; i < 3; i++) { // Escolhe os tres nos aleatorios
        sequence.push_back(candidatos[i]);
        s.cost += data.getDistance(atual, candidatos[i]);
        atual = candidatos[i];
    }

    candidatos.erase(candidatos.begin(), candidatos.begin()+3);
    CL = candidatos;

    s.cost += data.getDistance(atual, 1);

    sequence.push_back(1);    

    return sequence;
}

// Função para inserir o nó na sequência e atualizar o custo total
void inserirNaSolucao(Solution& s, InsertionInfo selecionado) {
    s.sequence.insert(s.sequence.begin() + selecionado.arestaRemovida + 1, selecionado.noInserido);
    s.cost += selecionado.custo;
}

// Função para construir uma solução inicial
Solution Construcao(Data& data) {
    Solution s;
    std::vector<int> CL;
    s.sequence = escolher3NosAleatorios(s, CL, data);  // Escolhe 3 nós aleatórios para iniciar a solução

    /* Exemplo:
       V = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10}
       s.sequence = {1, 2, 9, 5, 1}
       CL = {3, 4, 6, 7, 8, 10}
    */

    while (!CL.empty()) {
        // Calcula os custos de inserção
        std::vector<InsertionInfo> custoInsercao = calcularCustoInsercao(s, CL, data);

        // Ordena os custos em ordem crescente
        std::sort(custoInsercao.begin(), custoInsercao.end(), [](const InsertionInfo& a, const InsertionInfo& b){
            return a.custo < b.custo;
        });

        // Seleciona um nó com base no parâmetro alpha
        double alpha = (double)rand() / RAND_MAX;
        int selecionado = rand() % ((int)ceil(alpha * custoInsercao.size()));

        // Insere o nó selecionado na solução
        inserirNaSolucao(s, custoInsercao[selecionado]);
        
        // Ao inserir o nó na solução, ele é removido de CL
        CL.erase(std::remove(CL.begin(), CL.end(), custoInsercao[selecionado].noInserido), CL.end());
    }

    return s;
}

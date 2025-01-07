#include <random>
#include "../include/SolutionILS.h"
#include "../include/random.h"

using namespace std;

// Retorna uma perturbacao na solucao atual: troca dois segmentos de tamanhos aleatorios de local
Solucao Perturbacao(Solution s, Data& data) {
    
    int n = s.subseq_matrix.size();

    int tam1 = Random::getInt(2, ceil(n/10.0));
    int tam2 = Random::getInt(2, ceil(n/10.0));

    int i1 = Random::getInt(1, n - (tam1+1) - tam2 - 2);
    int i2 = Random::getInt(i1+tam1, n - tam2+1 - 2);

    vector<int> segmento1(s.sequence.begin() + i1, s.sequence.begin() + i1 + tam1);
    vector<int> segmento2(s.sequence.begin() + i2, s.sequence.begin() + i2 + tam2);

    Subsequence sigma_1;
    Subsequence sigma_2;
    Subsequence sigma_3;
    Subsequence sigma_end;

    if ((i1+tam1) == (i2)) { // Segmentos adjacentes

        sigma_1 = Subsequence::Concatenate(s.subseq_matrix[0][i1-1], s.subseq_matrix[i2][i2+tam2-1], data);
        sigma_2 = Subsequence::Concatenate(sigma_1, s.subseq_matrix[i1][i1+tam1-1], data);
        sigma_end = Subsequence::Concatenate(sigma_2, s.subseq_matrix[i2+tam2][n-1], data);

    } else {  // Nao adjacentes

        sigma_1 = Subsequence::Concatenate(s.subseq_matrix[0][i1-1], s.subseq_matrix[i2][i2+tam2-1], data);
        sigma_2 = Subsequence::Concatenate(sigma_1, s.subseq_matrix[i1+tam1][i2-1], data);
        sigma_3 = Subsequence::Concatenate(sigma_2, s.subseq_matrix[i1][i1+tam1-1], data);
        sigma_end = Subsequence::Concatenate(sigma_3, s.subseq_matrix[i2+tam2][n-1], data);

    }

    s.sequence.erase(s.sequence.begin() + i2, s.sequence.begin() + i2 + tam2);
    s.sequence.erase(s.sequence.begin() + i1, s.sequence.begin() + i1 + tam1);

    s.sequence.insert(s.sequence.begin() + i1, segmento2.begin(), segmento2.end());
    s.sequence.insert(s.sequence.begin() + i2 + tam2 - tam1, segmento1.begin(), segmento1.end());

    UpdateAllSubseq(&s, data);

    s.cost = sigma_end.C;

    return s;
}
#include "SolutionILS.h"
#include <random>

using namespace std;

Solucao Perturbacao(Solution s, Data& data) {
    
    int n = data.getDimension();

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> segmento(2, ceil(n / 10.0));

    int tam1 = segmento(rng);
    int tam2 = segmento(rng);

    uniform_int_distribution<int> indice1(1, n - tam1 - tam2 - 2);

    int i1 = indice1(rng);

    uniform_int_distribution<int> indice2(i1+1, n - tam2+1 - 2);

    int i2 = indice2(rng);

    vector<int> segmento1(s.sequence.begin() + i1, s.sequence.begin() + i1 + tam1);
    vector<int> segmento2(s.sequence.begin() + i2, s.sequence.begin() + i2 + tam2);

    int delta = 0;

    if ((i1+tam1) == (i2)) { // segmentos adjacentes

        delta = - data.getDistance(s.sequence[i1-1], s.sequence[i1])
                - data.getDistance(s.sequence[i1+tam1-1], s.sequence[i1+tam1])
                - data.getDistance(s.sequence[i2+tam2-1], s.sequence[i2+tam2])
                + data.getDistance(s.sequence[i1-1], s.sequence[i2])
                + data.getDistance(s.sequence[i1+tam1-1], s.sequence[i2+tam2])
                + data.getDistance(s.sequence[i2+tam2-1], s.sequence[i1]);

    } else { 

        delta = - data.getDistance(s.sequence[i1-1], s.sequence[i1])
                - data.getDistance(s.sequence[i1+tam1-1], s.sequence[i1+tam1])
                - data.getDistance(s.sequence[i2-1], s.sequence[i2]) 
                - data.getDistance(s.sequence[i2+tam2-1], s.sequence[i2+tam2])
                + data.getDistance(s.sequence[i1-1], s.sequence[i2])
                + data.getDistance(s.sequence[i2+tam2-1], s.sequence[i1+tam1])
                + data.getDistance(s.sequence[i2-1], s.sequence[i1])
                + data.getDistance(s.sequence[i1+tam1-1], s.sequence[i2+tam2]);

    }

    s.sequence.erase(s.sequence.begin() + i2, s.sequence.begin() + i2 + tam2);
    s.sequence.erase(s.sequence.begin() + i1, s.sequence.begin() + i1 + tam1);

    s.sequence.insert(s.sequence.begin() + i1, segmento2.begin(), segmento2.end());
    s.sequence.insert(s.sequence.begin() + i2 + tam2 - tam1, segmento1.begin(), segmento1.end());

    s.cost += delta;

    return s;

}
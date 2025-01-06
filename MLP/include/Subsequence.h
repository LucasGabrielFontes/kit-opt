#ifndef SUBSEQUENCE_H
#define SUBSEQUENCE_H

#include <vector>
#include "../include/Data.h"

using namespace std;

class Solution;

struct Subsequence {

    double T, C;
    int W;
    int first, last; // Primeiro e ultimo nos da subsequencia

    inline static Subsequence Concatenate(Subsequence &sigma_1, Subsequence &sigma_2, Data &data) {
        Subsequence sigma;
        double temp = data.getDistance(sigma_1.last, sigma_2.first);
        sigma.W = sigma_1.W + sigma_2.W;
        sigma.T = sigma_1.T + temp + sigma_2.T;
        sigma.C = sigma_1.C + sigma_2.W*(sigma_1.T+temp) + sigma_2.C;
        sigma.first = sigma_1.first;
        sigma.last = sigma_2.last;

        return sigma;
    }
};

void UpdateAllSubseq(Solution *s, vector<vector<Subsequence>>& subseq_matrix, Data& data);

#endif
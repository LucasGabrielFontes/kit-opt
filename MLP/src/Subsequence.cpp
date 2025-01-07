// n: numerodenosdainstancia
// s: solucaocorrente
// subseq_matrix = vector<vector<Subsequence>>(n,vector<Subsequence>(n));

#include "../include/SolutionILS.h"
#include "../include/Subsequence.h"
#include "../include/Data.h"
#include <vector>

using namespace std;

void UpdateAllSubseq(Solution *s, const Data& data) {

    int n = s->subseq_matrix.size();

    // subsequencias de um unico no
    for(int i = 0; i < n; i++) {
        s->subseq_matrix[i][i].W = (i > 0);
        s->subseq_matrix[i][i].C = 0;
        s->subseq_matrix[i][i].T = 0;
        s->subseq_matrix[i][i].first = s->sequence[i];
        s->subseq_matrix[i][i].last = s->sequence[i];
    }

    for(int i = 0; i < n; i++)
        for(int j = i+1; j < n; j++)
            s->subseq_matrix[i][j] = Subsequence::Concatenate(s->subseq_matrix[i][j-1], s->subseq_matrix[j][j], data);
    
    // subsequencias invertidas (necessarias para o 2-opt)
    for(int i = n-1; i >= 0; i--)
        for(int j = i-1; j >= 0; j--)
            s->subseq_matrix[i][j] = Subsequence::Concatenate(s->subseq_matrix[i][j+1], s->subseq_matrix[j][j], data);
}
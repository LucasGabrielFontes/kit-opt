#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include "../include/SolutionILS.h"

bool bestImprovementSwap(Solution& s, Data& data);
bool bestImprovement2Opt(Solution& s, Data& data);
bool bestImprovementOrOpt(Solution& s, const int size, Data& data);
void BuscaLocal(Solution& s, Data& data);

#endif
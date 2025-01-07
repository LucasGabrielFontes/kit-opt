#ifndef BUSCA_LOCAL_H
#define BUSCA_LOCAL_H

#include "../include/SolutionILS.h"

bool bestImprovementSwap(Solution& s, const Data& data);
bool bestImprovement2Opt(Solution& s, const Data& data);
bool bestImprovementOrOpt(Solution& s, const int size, const Data& data);
void BuscaLocal(Solution& s, const Data& data);

#endif
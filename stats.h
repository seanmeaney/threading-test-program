#ifndef STATS_H
#define STATS_H

#include "defs.h"

void initStats(StatsType *[NUM_SCENARIOS]);
void updateStats(RunSpecsType *);
void cleanupStats(StatsType *[NUM_SCENARIOS]);
void printStats(StatsType *[NUM_SCENARIOS], int);

#endif /* STATS_H */

#ifndef THREAD_STUFF_H
#define THREAD_STUFF_H

#include "defs.h"

void initFightThreads(FightSpecsType *, FightSpecsType *);
void initScenarioThreads(RunSpecsType *[NUM_SCENARIOS]);
void *scenarioProc(void *);
void singleFight(FighterType *, FighterType *);
void *fightProc(void *);

#endif /* THREAD_STUFF_H */

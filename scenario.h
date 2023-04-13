#ifndef SCENARIO_H
#define SCENARIO_H

void initFightSpec(DequeType *, sem_t *, DirectionType, FighterType *, FightSpecsType **);
void initRunSpec(DequeType *, FighterType *, FighterType *, StatsType *, RunSpecsType **);
void initRunSpecs(RunSpecsType *[NUM_SCENARIOS], StatsType *[NUM_SCENARIOS]);
void cleanupRuns(RunSpecsType *[NUM_SCENARIOS]);
void executeScenarios(StatsType *[NUM_SCENARIOS]);

#endif /* SCENARIO_H */

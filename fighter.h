#ifndef FIGHTER_H
#define FIGHTER_H

#include "defs.h"

void initFighter(int, int, int, FighterType **);
void initHeros(FighterType *[NUM_SCENARIOS], FighterType *[NUM_SCENARIOS]);
void initCrew(DequeType *);

#endif /* FIGHTER_H */

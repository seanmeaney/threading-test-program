#ifndef DEFS_H
#define DEFS_H

#include <math.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUM_RUNS 100
#define NUM_PIRATES 10
#define NUM_SCENARIOS 3

#define TORT_STRENGTH 5
#define TORT_ARMOUR 8
#define HARE_STRENGTH 8
#define HARE_ARMOUR 5
#define HERO_HEALTH 20
#define PIRATE_HEALTH 10
#define SWORD_STRENGTH 2

#define MAX_STR 64

typedef enum { SUCCESS,
               FAILURE,
               PART_SUCCESS,
               RES_UNKNOWN } ResultType;
typedef enum { FRONT,
               BACK } DirectionType;

typedef struct {  // Stats for one scenario, accumulated over all runs
    int numSuccess;
    int numPartSuccess;
    int numFailure;
} StatsType;

typedef struct {  // One fighter:  Tortoise, Hare, or Pirate
    int strength;
    int armour;
    int health;
} FighterType;

typedef struct Node {
    FighterType *data;
    struct Node *next;
} NodeType;

typedef struct {  // Stores the fighting pirates for one scenario
    NodeType *head;
    NodeType *tail;
} DequeType;

typedef struct {  // Specs for one scenario of one run
    DequeType *pirates;
    FighterType *tort;
    FighterType *hare;
    StatsType *stats;
} RunSpecsType;

typedef struct {  // Specs for one fight of one scenario of one run
    FighterType *hero;
    DequeType *pirates;
    DirectionType dir;
    sem_t *dqMutex;
} FightSpecsType;

void initDeque(DequeType **);
void addToDeque(DequeType *, FighterType *);
FighterType *popFront(DequeType *);
FighterType *popBack(DequeType *);
int hasNext(DequeType *);
void deepCopy(DequeType *, DequeType *);
void cleanupDeque(DequeType *);

void initFighter(int, int, int, FighterType **);
void initHeros(FighterType *[NUM_SCENARIOS], FighterType *[NUM_SCENARIOS]);
void initCrew(DequeType *);

void initFightSpec(DequeType *, sem_t *, DirectionType, FighterType *, FightSpecsType **);
void initRunSpec(DequeType *, FighterType *, FighterType *, StatsType *, RunSpecsType **);
void initRunSpecs(RunSpecsType *[NUM_SCENARIOS], StatsType *[NUM_SCENARIOS]);
void cleanupRuns(RunSpecsType *[NUM_SCENARIOS]);
void executeScenarios(StatsType *[NUM_SCENARIOS]);

void initFightThreads(FightSpecsType *, FightSpecsType *);
void initScenarioThreads(RunSpecsType *[NUM_SCENARIOS]);
void *scenarioProc(void *);
void singleFight(FighterType *, FighterType *);
void *fightProc(void *);

void initStats(StatsType *[NUM_SCENARIOS]);
void updateStats(RunSpecsType *);
void cleanupStats(StatsType *[NUM_SCENARIOS]);
void printStats(StatsType *[NUM_SCENARIOS], int);

int parseArgs(char *[]);
int randm(int);  // Pseudo-random number generator function

#endif

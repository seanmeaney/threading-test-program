#include "defs.h"

/**
 * @brief initialize FightSpec, allocates memory, assigns data
 * 
 * @param d in: deque of pirates
 * @param mutex in: shared mutex for threads
 * @param dir in: direction to process deque from
 * @param hero in: hero to fight against pirates
 * @param f in-out: unitialized FightSpecsType
 */
void initFightSpec(DequeType *d, sem_t *mutex, DirectionType dir, FighterType *hero, FightSpecsType **f) {
    *f = malloc(sizeof(FightSpecsType));
    (*f)->dir = dir;
    (*f)->dqMutex = mutex;
    (*f)->pirates = d;
    (*f)->hero = hero;
}

/**
 * @brief initialize RunSpec, allocates memory, assigns data
 * 
 * @param d in: deque of pirates
 * @param t in: tortoise
 * @param h in: hare
 * @param s in: scenario stats
 * @param r in-out: unitialized RunSpecsType
 */
void initRunSpec(DequeType *d, FighterType *t, FighterType *h, StatsType *s, RunSpecsType **r) {
    *r = malloc(sizeof(RunSpecsType));
    (*r)->pirates = d;
    (*r)->tort = t;
    (*r)->hare = h;
    (*r)->stats = s;
}

/**
 * @brief initializes array of RunSpecs, initializes pirates, deepCopy's deques, initializes torts/hares
 * 
 * @param r in-out: pointer array of RunSpecs
 * @param s in: pointer array of scenario statistics
 */
void initRunSpecs(RunSpecsType *r[NUM_SCENARIOS], StatsType *s[NUM_SCENARIOS]) {
    DequeType *d[NUM_SCENARIOS];
    FighterType *t[NUM_SCENARIOS], *h[NUM_SCENARIOS];

    initHeros(t, h);
    for (int i = 0; i < NUM_SCENARIOS; i++) {
        initDeque(&d[i]);
        if (i == 0) {  //to satisfy 3.3.1
            initCrew(d[0]);
        } else {
            deepCopy(d[0], d[i]);
        }
        initRunSpec(d[i], t[i], h[i], s[i], &r[i]);
    }
}

/**
 * @brief Free all dynamically allocated memory for run
 * 
 * @param r in: RunSpecsType array containing deques, torts, hares
 */
void cleanupRuns(RunSpecsType *r[NUM_SCENARIOS]) {
    for (int i = 0; i < NUM_SCENARIOS; i++) {
        cleanupDeque(r[i]->pirates);
        free(r[i]->hare);
        free(r[i]->tort);
        free(r[i]);
    }
}

/**
 * @brief executes all scenarios and updates stats
 * 
 * @param s in-out: statistics pointer array for each scenario
 */
void executeScenarios(StatsType *s[NUM_SCENARIOS]) {
    RunSpecsType *r[NUM_SCENARIOS];
    initRunSpecs(r, s);
    initScenarioThreads(r);
    cleanupRuns(r);
}
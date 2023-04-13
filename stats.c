#include "defs.h"

/**
 * @brief initializes NUM_SCENARIOS of Stats types by allocating memory and setting counters to 0
 * 
 * @param s in-out: array of unitiliazed StatsType pointers
 */
void initStats(StatsType *s[NUM_SCENARIOS]) {
    for (int i = 0; i < NUM_SCENARIOS; i++) {
        s[i] = malloc(sizeof(StatsType));
        s[i]->numFailure = 0;
        s[i]->numPartSuccess = 0;
        s[i]->numSuccess = 0;
    }
}

/**
 * @brief computes scenario outcome and updates a scenarios stats
 * 
 * @param r in: RunSpecsType contating stats and run data
 */
void updateStats(RunSpecsType *r) {
    if (hasNext(r->pirates) == 1) {
        r->stats->numFailure++;
    } else if (r->tort->health > 0 && r->hare->health > 0) {
        r->stats->numSuccess++;
    } else {
        r->stats->numPartSuccess++;
    }
}

/**
 * @brief deallocates dynamically allocated StatsType memory
 * 
 * @param s in: array of StatsType pointers
 */
void cleanupStats(StatsType *s[NUM_SCENARIOS]) {
    for (int i = 0; i < NUM_SCENARIOS; i++) {
        free(s[i]);
    }
}

/**
 * @brief prints formatted statistics data, seperated by scenario
 * 
 * @param s     array of StatsType
 * @param numRuns number of rums executed
 */
void printStats(StatsType *s[NUM_SCENARIOS], int numRuns) {
    printf("%s", "+-------------------------------------------------------------+\n");
    printf("| Hero with sword |  %% success  |   %% partial   |  %% failure  |  \n");
    printf("+-------------------------------------------------------------+\n");
    printf("|   Tortoise\t  |\t%02d\t|     %02d\t|\t%02d    |\n", (s[0]->numSuccess) * 100 / numRuns, (s[0]->numPartSuccess) * 100 / numRuns, (s[0]->numFailure) * 100 / numRuns);
    printf("+-------------------------------------------------------------+\n");
    printf("|   Hare\t  |\t%02d\t|     %02d\t|\t%02d    |\n", (s[1]->numSuccess) * 100 / numRuns, (s[1]->numPartSuccess) * 100 / numRuns, (s[1]->numFailure) * 100 / numRuns);
    printf("+-------------------------------------------------------------+\n");
    for (int i = 2; i < NUM_SCENARIOS; i++) {  //to satisfy 3.3.1
        printf("|   None\t  |\t%02d\t|     %02d\t|\t%02d    |\n", (s[i]->numSuccess) * 100 / numRuns, (s[i]->numPartSuccess) * 100 / numRuns, (s[i]->numFailure) * 100 / numRuns);
        printf("+-------------------------------------------------------------+\n");
    }
    printf("\nTotal runs: %d\n", numRuns);
}
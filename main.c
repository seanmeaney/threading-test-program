#include "defs.h"

int main(int argc, char *argv[]) {
    StatsType *s[NUM_SCENARIOS];
    int runNumber = (argc > 1) ? parseArgs(argv) : NUM_RUNS;

    srand((unsigned)time(NULL));
    initStats(s);

    for (int i = 0; i < runNumber; i++) {
        executeScenarios(s);
    }
    printStats(s, runNumber);
    cleanupStats(s);
    return 0;
}

/**
 * @brief parses a integer from arguemnts and checks if value is above 0
 * 
 * @param argv in: argument string
 * @return int 
 */
int parseArgs(char *argv[]) {
    int runNumber;
    sscanf(argv[1], "%d", &runNumber);
    if (runNumber <= 0) {
        printf("Invalid run number passed, using default %d\n", NUM_RUNS);
        runNumber = NUM_RUNS;
    }
    return runNumber;
}

/*
  Function:  randm
  Purpose:   returns a pseudo randomly generated number, 
             in the range 0 to (max - 1), inclusively
       in:   upper end of the range of the generated number
   return:   randomly generated integer in the range [0, max-1) 
*/
int randm(int max) {
    double r = ((double)rand() / ((double)(RAND_MAX) + (double)(1)));

    return (int)(r * max);
}

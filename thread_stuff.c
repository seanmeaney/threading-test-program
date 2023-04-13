#include <pthread.h>
#include <semaphore.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "defs.h"
#include "thread_stuff.h"
#include "deque.h"
#include "stats.h"
#include "scenario.h"

/**
 * @brief spawn threads to process deque in both directions, pass fightProc function and FightSpecsType 
 * 
 * @param f1 in-out: FightSpecsType for first thread containg deque, mutex, direction and hero 
 * @param f2 in-out: FightSpecsType for second thread containg deque, mutex, direction and hero 
 */
void initFightThreads(FightSpecsType *f1, FightSpecsType *f2) {
    pthread_t t1, t2;
    pthread_create(&t1, NULL, fightProc, f1);
    pthread_create(&t2, NULL, fightProc, f2);
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
}
/**
 * @brief spawn NUM_SCENARIOS threads to process each scenario, pass scenarioProc and RunSpecsType to each
 * 
 * @param r in-out: array of pointers to RunSpecsTypes to pass to each thread
 */
void initScenarioThreads(RunSpecsType *r[NUM_SCENARIOS]) {
    pthread_t t[NUM_SCENARIOS];
    for (int i = 0; i < NUM_SCENARIOS; i++) {
        pthread_create(&t[i], NULL, scenarioProc, r[i]);
        pthread_join(t[i], NULL);
    }
}

/**
 * @brief scenario start functiopn, spawns fight threads, simulates battle, updates stats and does garbage collection
 * 
 * @param arg in-out RunSpecsType pointer containing all data needed for thread execiution
 * @return void* 
 */
void *scenarioProc(void *arg) {
    RunSpecsType *r = (RunSpecsType *)arg;
    FightSpecsType *f1, *f2;

    sem_t mutex;
    if (sem_init(&mutex, 0, 1) < 0) {
        printf("semaphore initialization error\n");
        exit(1);
    }

    initFightSpec(r->pirates, &mutex, FRONT, r->tort, &f1);
    initFightSpec(r->pirates, &mutex, BACK, r->hare, &f2);
    initFightThreads(f1, f2);
    updateStats(r);
    free(f1);
    free(f2);
    return (0);
}

/**
 * @brief simulates a fight between the hero and a pirate
 * 
 * @param hero in-out: hero FighterType
 * @param pirate in-out: pirate FighterType
 */
void singleFight(FighterType *hero, FighterType *pirate) {
    int tempDamage;
    while (hero->health > 0 && pirate->health > 0) {
        tempDamage = hero->strength - pirate->armour;
        pirate->health -= (tempDamage < 0) ? 0 : tempDamage;
        if (pirate->health > 0) {  //allow pirate to hit back
            tempDamage = (pirate->strength + randm(pirate->strength - 1)) - hero->armour;
            hero->health -= (tempDamage < 0) ? 0 : tempDamage;
            if (hero->health < 0) {  //break upon next entry
                hero->health = 0;
            }
        } else {  //break upon next entry
            pirate->health = 0;
            hero->health += 3;
            if (hero->health > 20) {
                hero->health = 20;
            }
        }
    }
    free(pirate);
}

/**
 * @brief fight start function, simulates battle and does garbage collection for removed pirates
 * 
 * @param arg in-out: RunSpecsType pointer containing all data needed for thread execiution
 * @return void* 
 */
void *fightProc(void *arg) {
    FightSpecsType *f = (FightSpecsType *)arg;
    FighterType *pirate;

    int tempTemst = 1;

    while (hasNext(f->pirates) && f->hero->health > 0) {
        tempTemst++;
        if (sem_wait(f->dqMutex) < 0) {
            printf("semaphore wait error\n");
            exit(1);
        }
        
        if (hasNext(f->pirates)) {
            pirate = (f->dir == FRONT) ? popFront(f->pirates) : popBack(f->pirates);
            singleFight(f->hero, pirate);
        }

        if (sem_post(f->dqMutex) < 0) {
            printf("semaphore post error\n");
            exit(1);
        }
        usleep(1000);
    }
    return (0);
}
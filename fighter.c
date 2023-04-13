#include <stdlib.h>

#include "defs.h"
#include "scenario.h"
#include "deque.h"
/**
 * @brief initialize Fighter, allocates memory, assigns data
 * 
 * @param strength  in: strength for new fighter
 * @param armour    in: armour for new fighter
 * @param health    in: health for new fighter
 * @param f in-out: unitialized Fighter
 */
void initFighter(int strength, int armour, int health, FighterType **f) {
    *f = malloc(sizeof(FighterType));
    (*f)->strength = strength;
    (*f)->armour = armour;
    (*f)->health = health;
}

/**
 * @brief Initializes array of NUM_SCENARIOS tortoises and hares, any additional torts hares above default (3) are created with base stats
 * 
 * @param torts in-out: array of NUM_SCENARIOS tortoise pointers
 * @param hares in-out: array of NUM_SCENARIOS hare pointers
 */
void initHeros(FighterType *torts[NUM_SCENARIOS], FighterType *hares[NUM_SCENARIOS]) {
    initFighter(TORT_STRENGTH + SWORD_STRENGTH, TORT_ARMOUR, 20, &torts[0]);
    initFighter(HARE_STRENGTH, HARE_ARMOUR, 20, &hares[0]);
    initFighter(TORT_STRENGTH, TORT_ARMOUR, 20, &torts[1]);
    initFighter(HARE_STRENGTH + SWORD_STRENGTH, HARE_ARMOUR, 20, &hares[1]);

    for (int i = 2; i < NUM_SCENARIOS; i++) {  //to satisfy 3.3.1
        initFighter(TORT_STRENGTH, TORT_ARMOUR, 20, &torts[i]);
        initFighter(HARE_STRENGTH, HARE_ARMOUR, 20, &hares[i]);
    }
}

/**
 * @brief Initializes NUM_PIRATES pirates to populate deque
 * 
 * @param d in-out: empty fighter deque
 */
void initCrew(DequeType *d) {
    FighterType *f;
    for (int i = 0; i < NUM_PIRATES; i++) {
        initFighter(randm(5) + 5, randm(4) + 1, 10, &f);
        addToDeque(d, f);
    }
}
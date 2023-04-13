#ifndef DEQUE_H
#define DEQUE_H

void initDeque(DequeType **);
void addToDeque(DequeType *, FighterType *);
FighterType *popFront(DequeType *);
FighterType *popBack(DequeType *);
int hasNext(DequeType *);
void deepCopy(DequeType *, DequeType *);
void cleanupDeque(DequeType *);

#endif /* DEQUE_H */

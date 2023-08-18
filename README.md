Multithreaded test program that simulates multiple fight sceneraios between heros and pirates with 100 runs per scenario.

Includes a custom deque implementation using relevant concurrency mechanisms to allow for double ended operation.

A tortoise and hare pop enemies from front and back of the deque and a fight is simulated between the two (see defs for relevant fight attributes).

Results of the fights are recorded and averages are presented after run (full success achieved when both heros survive fight, partial success if one hero dies and failure if both heros die).

Build and execution instructions:
Simply make and ./piratewars

# Langtons-Ant

A C++ implementation of Langton's Ant using the SFML graphics library.

Langton's Ant is a cellular automaton in which an ant moves through an orthogonal grid.  
The grid consists of cells which are either alive or dead.

On a **living** tile, the ant turns 90 degrees to the right, turns the tile off and moves forward.
On a **dead** tile the ant turns 90 degrees to the left, turns the tile on and moves forward.

After about 11000 iterations, a single ant will fall into a pattern, creating a "highway" in one direction.

Enjoy!

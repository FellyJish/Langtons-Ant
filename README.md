# Langtons-Ant

Langton's Ant is a cellular automaton in which an ant moves through a grid, 
turning tiles on and off based on a set of rules.

On a living tile the ant turns 90 degrees to the right, turns the tile off and moves forward.
On a dead tile the ant turns 90 degrees to the left, turns the tile on and moves forward.

As I'd recently made Conway's Game of Life, I decided to modify the grid code for Langton's Ant.
I've now added in a variable amount of ants, and screen wrapping!

TODO: Proper input validation
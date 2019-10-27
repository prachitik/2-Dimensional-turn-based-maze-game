#ifndef PATH_H_INCLUDED
#define PATH_H_INCLUDED

#define V 8

#include <limits.h>
#include <iostream>
class Path{
public:
int dijkstra(int[V][V], int);
int minDistance(int[], bool[]);
void printSolution(int[], int);
};
#endif // PATH_H_INCLUDED

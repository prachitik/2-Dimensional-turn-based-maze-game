#ifndef BFS_H
#define BFS_H

#include <bits/stdc++.h>

using namespace std;


class bfs
{
public:
void add_edge(vector<int>[], int, int);

bool BFS(vector<int>[], int, int , int v, int[], int[]);

int printShortestDistance(vector<int>[], int s,  int dest, int v);

};
#endif

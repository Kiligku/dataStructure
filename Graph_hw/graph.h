#pragma once
#include <vector>
#include <queue>
#include <iostream>
#define MAX_DIS 100000
using namespace std;
class Graph
{
private:
    vector<int> visited;
    void BFS(int x);
    void DFS(int y);
    void floyd(vector<int> &ecc);
public:
    int nodeNum;
    int edgeNum;
    vector<string> vertex;
    vector<vector<int>> matrix;
    Graph(int nNum, int eNum);
    int firstNeighbour(int x);
    int nextNeighbour(int x, int y);
    int isConnected();
    void nodeDegree(vector<int> &ode_degree);
    double clusteringCoefficient();
    int dijkstra(int start, int end, vector<int> &path);
    int Diameter();
    int Radius();
    void printPath(vector<int> diameter_path);
};
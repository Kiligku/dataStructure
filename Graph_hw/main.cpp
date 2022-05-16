#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
using namespace std;

void printGraph(Graph g)
{
    for (auto i = g.matrix.begin(); i != g.matrix.end(); i++)
    {
        for (auto j = i->begin(); j != i->end(); j++)
        {
            cout << *j << " ";
        }
        cout << endl;
    }
}
void printAllNeighbours(Graph g, int nodeNum)
{
    for (int x = 0; x < nodeNum; x++)
    {
        cout << "node" << x << ":" << endl;
        for (int w = g.firstNeighbour(x); w != -1; w = g.nextNeighbour(x, w))
        {
            cout << "w=" << w << endl;
        }
    }
}
int main()
{
    int nodeNum;
    int edgeNum;
    int ca = 1;
    ifstream fin;
    fin.open("stu.in", ios::in);
    if (!fin.is_open())
    {
        cerr << "failed to open file!";
    }
    char line[1024] = {0};
    while (fin >> nodeNum >> edgeNum)
    {
        cout << "case" << ca++ << ":" << endl;
        fin.get(); // 读取换行符
        Graph g(nodeNum, edgeNum);
        int start_idx, end_idx, weight;
        for (int i = 0; i < edgeNum; i++)
        {
            fin.getline(line, sizeof(line));
            // cout << "line " << i + 1 << ":" << line << endl;
            stringstream word(line);
            word >> start_idx >> end_idx >> weight;
            g.matrix[start_idx][end_idx] = weight;
            g.matrix[end_idx][start_idx] = weight;
        }

        // task1:
        int isConnected = g.isConnected();
        cout << "connected: " << isConnected << endl;

        // task2:
        vector<int> degree;
        g.nodeDegree(degree);
        cout << "degree distribution" << endl;
        for (int i = 0; i < nodeNum; i++)
        {
            cout << "node" << g.vertex[i] << ":" << degree[i] << ",";
        }
        cout << endl;

        // task3:
        double c = g.clusteringCoefficient();
        cout << "clustering coefficient:" << c << endl;
        // task4:
        if(g.isConnected())
        {
            vector<int> short_path;
            int dis = g.dijkstra(1, 3, short_path);
            cout << "the shortest path between 1 and 3:" << dis << endl;
            g.printPath(short_path);

            int d = g.Diameter();
            cout << "diameter:" << d << endl;
            int r = g.Radius();
            cout << "radius:" << r << endl;
        }

        cout << endl
             << endl;
    }
    return 0;
}
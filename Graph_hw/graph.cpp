#include "graph.h"

/**
 * 创建一个节点数为n的图
 * @param nNum 节点个数
 * @param eNum 边数
 */
Graph::Graph(int nNum, int eNum)
{
    this->nodeNum = nNum;
    this->edgeNum = eNum;
    for (int i = 0; i < nNum; i++)
    {
        vector<int> r(nNum);
        this->matrix.push_back(r);
        this->vertex.push_back(to_string(i));
        this->visited.push_back(0);
    }
    for (int i = 0; i < nNum; i++)
    {
        for (int j = 0; j < nNum; j++)
        {
            if (i != j)
                this->matrix[i][j] = MAX_DIS;
        }
    }
}

/**
 * @brief 寻找顶点的第一个邻接点
 * @param x 顶点编号
 * @return 返回图中顶点x的第一个邻接点，有则返回顶点号，否则返回-1
 */
int Graph::firstNeighbour(int x)
{
    int idx = -1;
    for (int i = 0; i < this->nodeNum; i++)
    {
        if (this->matrix[x][i] < MAX_DIS && i != x)
            return i;
    }
    return -1;
}

/**
 * @brief 寻找顶点x除y外第一个邻接点并返回该邻接点的编号，找不到则返回-1
 *
 * @param x
 * @param y
 * @return int
 */
int Graph::nextNeighbour(int x, int y)
{
    int idx = -1;
    for (int i = 0; i < this->nodeNum; i++)
    {
        if (this->matrix[x][i] < MAX_DIS && i != x && i > y)
            return i;
    }
    return -1;
}

/**
 * @brief 图的广度优先遍历
 *
 * @param x 开始遍历的顶点
 */

void Graph::BFS(int x)
{
    queue<int> nodeQueue;
    nodeQueue.push(x);
    // cout << "visit node " << this->vertex[x] << endl;
    this->visited[x] = 1;
    while (!nodeQueue.empty())
    {
        x = nodeQueue.front();
        nodeQueue.pop();
        for (int w = firstNeighbour(x); w != -1; w = nextNeighbour(x, w))
        {
            if (!visited[w])
            {
                nodeQueue.push(w);
                // cout << "visit node " << this->vertex[w] << endl;
                this->visited[w] = 1;
            }
        }
    }
}

/**
 * @brief 图的广度优先遍历
 *
 * @param x 开始遍历的顶点
 */
void Graph::DFS(int x)
{
    // cout << "visit node " << this->vertex[x] << endl;
    visited[x] = 1;
    for (int w = firstNeighbour(x); w != -1; w = nextNeighbour(x, w))
    {
        if (!visited[w])
        {
            DFS(w);
        }
    }
}

/**
 * 判断图是否连通
 * @return 连通返回1，否则返回0
 */
int Graph::isConnected()
{
    vector<int> t(this->nodeNum);
    this->visited = t;
    // cout << t.size() << endl;
    DFS(0);
    for (int i = 0; i < nodeNum; i++)
    {
        if (visited[i] == 0)
            return 0;
    }
    return 1;
}

/**
 * 计算每个点的度
 * @param node_degree 将每个点的度写到这个数组中
 */
void Graph::nodeDegree(vector<int> &node_degree)
{
    for (int i = 0; i < this->nodeNum; i++)
    {
        int nodeDegree = 0;
        for (int j = 0; j < this->nodeNum; j++)
        {
            if (this->matrix[i][j] < MAX_DIS && j != i)
                nodeDegree++;
        }
        node_degree.push_back(nodeDegree);
    }
}

/**
 * 计算图的聚类系数
 * @return 返回聚类系数
 */
double Graph::clusteringCoefficient()
{
    double cc = 0;
    vector<int> neighbour;
    for (int i = 0; i < this->nodeNum; i++)
    {
        for (int w = firstNeighbour(i); w != -1; w = nextNeighbour(i, w))
        {
            neighbour.push_back(w);
        }
        int n = neighbour.size(); // 邻接点的总数
        if (n <= 1)               // 如果结点只有一个邻接点或更少，该点的聚类系数为0
        {
            neighbour.clear();
            continue;
        }
        int eNum = 0; // 邻接点之间的边数
        for (int j = 0; j < n; j++)
        {
            for (int k = j; k < n; k++)
            {
                int weight = this->matrix[neighbour[j]][neighbour[k]];
                if (weight > 0 && weight < MAX_DIS)
                    eNum++;
            }
        }
        cc += 2 * (double)eNum / (n * (n - 1));
        neighbour.clear();
    }
    return cc / this->nodeNum;
}

int Diameter();
int Radius();
int dijkstra(int start, int end, int *path);
void printPath(int d, int *diameter_path);
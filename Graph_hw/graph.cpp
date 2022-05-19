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
 * @brief 图的深度优先遍历
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

/**
 * 使用dijkstra算法计算单源最短路径
 * @param start 起点
 * @param end 终点
 * @param path 从start到end的路径, [start,...,end]
 * @return 路径长度
 */
int Graph::dijkstra(int start, int end, vector<int> &path)
{
    // 初始化
    vector<int> final(this->nodeNum, 0);
    vector<int> dist(this->nodeNum, MAX_DIS);
    vector<int> _path(this->nodeNum, -1);
    final[start] = 1;
    dist[start] = 0;
    _path[start] = start;
    for (int w = firstNeighbour(start); w != -1; w = nextNeighbour(start, w))
    {
        dist[w] = this->matrix[start][w];
        _path[w] = start;
    }
    // 遍历操作
    int cnt = 0;
    while (cnt < this->nodeNum - 1)
    {
        int node = -1;
        int minDist = MAX_DIS;
        for (int i = 0; i < this->nodeNum; i++)
        {
            if (!final[i] && dist[i] < minDist)
            {
                minDist = dist[i];
                node = i; // 选出dist最小且没有确定最佳路径的顶点
            }
        }
        final[node] = 1;
        for (int i = 0; i < this->nodeNum; i++)
        {
            if (!final[i] && this->matrix[node][i] < MAX_DIS) // 遍历没有确定最短路径的邻居
            {
                if (dist[i] > (dist[node] + this->matrix[i][node]))
                {
                    dist[i] = this->matrix[i][node] + dist[node]; // 更新最短距离
                    _path[i] = node;
                }
            }
        }
        cnt++;
    }
    int pathNode = end;
    while (pathNode != start)
    {

        path.insert(path.begin(), pathNode);
        pathNode = _path[pathNode];
    }
    path.insert(path.begin(), start);
    return dist[end];
}

/**
 * @brief 用floyd算法求每对顶点之间的最短距离
 *
 * @param ecc 存储每个顶点eccentricity的数组
 */
void Graph::floyd(vector<int> &ecc)
{
    vector<vector<int>> dis;
    for (int i = 0; i < this->nodeNum; i++)
    {
        vector<int> t;
        // 初始化距离数组
        for (int j = 0; j < this->nodeNum; j++)
        {
            t.push_back(matrix[i][j]);
        }
        dis.push_back(t);
    }
    for (int k = 0; k < this->nodeNum; k++) // 考虑以顶点k为中转
    {
        for (int i = 0; i < this->nodeNum; i++)
        {
            for (int j = 0; j < this->nodeNum; j++)
            {
                if (dis[i][j] > dis[i][k] + dis[k][j])
                {
                    dis[i][j] = dis[i][k] + dis[k][j];
                }
            }
        }
    }
    // 计算eccentricity
    for (int i = 0; i < this->nodeNum; i++)
    {
        int curEcc = 0;
        for (int j = 0; j < this->nodeNum; j++)
        {
            if (dis[i][j] > curEcc)
                curEcc = dis[i][j];
        }
        ecc.push_back(curEcc);
    }
}

/**
 * 计算图的直径。提示：Floyd算法
 * @return 直径的长度
 */
int Graph::Diameter()
{
    vector<int> ecc;
    floyd(ecc);
    int d = 0;
    for (int i = 0; i < this->nodeNum; i++)
    {
        if (ecc[i] > d)
            d = ecc[i];
    }
    return d;
}

/**
 * 计算图的半径
 * @return 半径长度
 */
int Graph::Radius()
{
    vector<int> ecc;
    floyd(ecc);
    int r = MAX_DIS;
    for (int i = 0; i < this->nodeNum; i++)
    {
        if (ecc[i] < r)
            r = ecc[i];
    }
    return r;
}

/**
 * 根据和路径数组path输出路径
 * @param diameter_path 储存路径的数组
 */
void Graph::printPath(vector<int> diameter_path)
{
    int k = 0;
    int path_length = 0;
    cout << "Path: ";
    for (auto it = diameter_path.begin(); it != diameter_path.end(); it++)
    {
        if (it + 1 == diameter_path.end())
        {
            cout << this->vertex[*it] << endl;
        }
        else
        {
            cout << this->vertex[*it] << "->";
        }
    }
}
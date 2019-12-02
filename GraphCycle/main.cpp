//
//  main.cpp
//  GraphCycle
//
//  Created by ShevaKuilin on 2019/11/20.
//  Copyright © 2019 ShevaKuilin. All rights reserved.
//

#include <iostream>
#include <stdlib.h>

using namespace std;
#define maxNum 100      // 定义邻接矩阵的最大顶点数
int visited[maxNum];    // [无向图记录]标记这个顶点是否被访问过，0表示未被访问，1表示被访问
int DFS_Count;          // 连通部件个数，用于测试无向图是否连通，DFS_Count=1 表示只有一个连通部件，所以整个无向图是连通的
bool existed = false;   // 是否存在环
int color[maxNum];      // [有向图记录]顶点颜色表

// 图的邻接矩阵表示结构
typedef struct {
    int m[maxNum][maxNum];  // 图的顶点信息
    int N;                  // 顶点个数
    int M;                  // 边的个数
    int I;                  // 0为有向图，1位无向图
}graph;

// 从顶点i开始深度优先遍历与其相邻的点
void dfs(graph *g, int i) {
    if (g->I == 0) {
        color[i] = -1;
        for(int j = 1; j <= g->N; j++) {
            if(g->m[i][j] != 0) {
                // 检测到回路，存在环
                if(color[j] == -1) {
                    existed = true;
                } else if(color[j] == 0) {
                    dfs(g, j);
                }
            }
        }
        // 表示i的后续节点都被访问过
        color[i] = 1;
    } else {
        visited[i] = 1;// 标记顶点i被访问
        for(int j = 1; j <= g->N; j++) {
            if(g->m[i][j] != 0 && visited[j] == 0) {
                dfs(g, j);
            }
        }
    }
}

// 深度优先搜索
void DFS(graph *g) {
    int i;
    if (g->I == 0) {
        //初始化color数组，表示一开始所有顶点都未被访问过
        for(i = 1; i <= g->N; i++) {
            color[i] = 0;
        }
        // 深度优先搜索
        for(i = 1; i <= g->N; i++) {
            // 如果这个顶点未被访问过，则从i顶点出发进行深度优先遍历
            if(color[i] == 0) {
                dfs(g, i);
            }
        }
    } else {
        // 初始化visited数组，表示一开始所有顶点都未被访问过
        for(i = 1; i <= g->N; i++) {
            visited[i]=0;
        }
        //初始化连通部件数为0
        DFS_Count = 0;
        //深度优先搜索
        for(i = 1; i <= g->N; i++) {
            //如果这个顶点为被访问过，则从i顶点出发进行深度优先遍历
            if(visited[i] == 0) {
                DFS_Count++;// 记录dfs_d(graph *g,int i)函数执行次数
                dfs(g, i);
            }
        }
    }
}

// 创建无向图
void createUndirectedGraph(graph *g) {
    int i, j;
    // 绘图
    for(i = 1; i <= g->N; i++) {
        for(j = 1; j <= g->N; j++) {
            g->m[i][j] = 0;
        }
    }
    // 输入 A 和 B
    for(int k = 0; k < g->M; k++) {
        cin >> i >> j;
        g->m[i][j] = 1;
        g->m[j][i] = 1;//无向图对称
    }
}

// 创建有向图
void createDirectedGraph(graph *g) {
    int i, j;
    // 绘图
    for(i = 1; i <= g->N; i++) {
        for(j = 1; j <= g->N; j++) {
            g->m[i][j] = 0;
        }
    }
    // 输入 A 和 B
    for(int k = 1; k <= g->M; k++) {
        cin >> i >> j;
        g->m[i][j] = 1;
    }
}

// 创建图
void createGraph(graph *g) {
    // 输入顶点个数 N
    cin >> g->N;
    // 输入边数 M
    cin >> g->M;
    // 输入图类别 I
    cin >> g->I;
    if (g->I == 0) {
        // 有向图
        createDirectedGraph(g);
    } else {
        // 无向图
        createUndirectedGraph(g);
    }
}

// 聚合输出结果
void printfResult(graph *g) {
    if (g-> I == 0) {
        // 判断邮箱图中是否有环
        if(existed) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    } else {
        // 判断无向图中是否有环
        if(g->M + DFS_Count > g->N) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}

int main() {
    graph *g;
    g = (graph *)malloc(sizeof(graph));
    // 创建图
    createGraph(g);
    // 深度优先遍历
    DFS(g);
    //判断图中是否有环
    printfResult(g);
    
    return 0;
}


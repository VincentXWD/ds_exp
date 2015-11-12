#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cstring>
#include <climits>
#include <complex>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <bitset>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <ctime>
#include <set>
#include <map>
#include <cmath>

using namespace std;

typedef struct Edge {
    int v;   //到达点
    int w;   //边权值
    int next;//当前起点的下一条边的起始edge的序号
    Edge() { next = -1; }
    Edge(int vv, int ww) : v(vv), w(ww) { next = -1; }
}Edge;

const int maxn = 1111111;

int n, m;  //n个点标号为1-n，有m条边
int vis[maxn];  //用于标记某边是否被遍历到，用于解决环的问题

int cnt;   //边的数量
int dig[maxn];//有一种特殊情况：某点的入度为0，这样利用边与出度点的关系是便利不到的，因此我们特殊考虑。统计点的入度
int head[maxn]; //每个顶点的边集数组的第一个存储位置
Edge edge[maxn];//链式前向星（静态邻接表）存储边集

void init() { //每次添加边的时候，head存储的都是起点添加的最后一条边
    memset(vis, 0, sizeof(vis));
    memset(edge, 0, sizeof(edge));
    memset(dig, 0, sizeof(dig));
    memset(head, -1, sizeof(head)); //因edge从0计数，用于区分
    cnt = 0;
}

void adde(int uu, int vv, int ww) { //添加边
    dig[vv]++;  //边指向点入度加一
    edge[cnt].v = vv;
    edge[cnt].w = ww;
    edge[cnt].next = head[uu];  //使要添加的边的指向下一条边的变量存下当前head中对应点的数
    head[uu] = cnt++;   //记下当前边在edge数组的位置，并且作为头传递给head数组
}

//根据链式前向星（静态邻接表）的特性，每个边存的是同一个起点出发的下一条边，
//只需要遍历每一个点再从每一个点开始的头边向后扫描即可按照bfs的顺序遍历所有的边
void bfs_edge() {
    int s = 1;
    queue<int> q;
    while(!q.empty()) q.pop();
    for(int i = 1; i <= n; i++) {
        if(head[i] != -1) {
            s = i;
            break;
        }
    }
    q.push(s);  //找到第一个出度不为0的点后，作为起点并入栈。
    memset(vis, 0, sizeof(vis));//初始化vis数组
    while(!q.empty()) {
        int u = q.front(); q.pop();
        for(int i = head[u]; ~i; i=edge[i].next) {  //遍历每一条以u为起点的边
            if(!vis[i]) {   //如果当前边未遍历到
                vis[i] = 1; //设置为已遍历过
                printf("from %d to %d w %d\n", u, edge[i].v, edge[i].w);//输出遍历结果
                q.push(edge[i].v);//将此边的目标点放入队列
            }
        }
    }
    for(int i = 1; i <= n; i++) {   //特判入度为0的点，也遍历到。
        if(!dig[i] && i != s) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

//与bfs_edge同理，不过遍历到每一个边的时候，用vis数组对遍历到的边节点
//所指向的下一个点进行标记就可以对点进行bfs了
void bfs_vertex() {
    printf("BFS the vertex:\n");
    int s = 1;
    queue<int> q;
    while(!q.empty()) q.pop();
    for(int i = 1; i <= n; i++) {
        if(head[i] != -1) {
            s = i;
            break;
        }
    }
    q.push(s);  //找到第一个出度不为0的点后，作为起点并入栈。
    memset(vis, 0, sizeof(vis));//初始化vis数组
    printf("%d ", s);
    while(!q.empty()) {
        int u = q.front(); q.pop(); //取头队列头部的点，进行遍历
        vis[u] = 1; //记下当前点为遍历到
        for(int i = head[u]; ~i; i=edge[i].next) { //遍历此点的出边
            if(!vis[edge[i].v]) {   //如果出边目标点未被遍历到
                vis[edge[i].v] = 1; //设置为已遍历 并输出遍历结果
                printf("%d ", edge[i].v);
                q.push(edge[i].v);  //将此点放入队中
            }
        }
    }
    for(int i = 1; i <= n; i++) {   //特判入度为0的点，也遍历到。
        if(!dig[i] && i != s) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

void _dfs(int u) {//dfs的辅助函数，用于递归遍历最深处的点
    vis[u] = 1;  //此点为遍历到，设置为已遍历
    for(int i = head[u]; ~i; i=edge[i].next) {//遍历所有此点的出边
        if(!vis[edge[i].v]) {   //如果下一个点未被遍历到
            vis[edge[i].v] = 1; //设置为已遍历
            _dfs(edge[i].v);    //递归地调用，以此点为起点向下寻找未被遍历到的点
        }
    }
    printf("%d ", u);   //此处输出，因为dfs是先输出最深处的点
}

void dfs_vertex() {
    printf("DFS the vertex:\n");
    int s = 1;
    for(int i = 1; i <= n; i++) {
        if(head[i] != -1) {
            s = i;
            break;
        }
    }   //查找第一个出度非零的点并执行dfs的辅助函数
    memset(vis, 0, sizeof(vis));
    _dfs(s);
    for(int i = 1; i <= n; i++) {   //特判入度为0的点，也遍历到。
        if(!dig[i] && i != s) {
            printf("%d ", i);
        }
    }
    printf("\n");
}

//回溯算法的辅助数组，用于统计是否出现过已经走过的顶点
int but[2048];
//flag判断是否已经有可走的简单路径
int flag = 0;
void solve(int cur, int x, int y, int k, int* step, int s) {
//回溯求简单路径
    if(cur == k && x == y) {  //已经走过限定的步数并且符合条件：走到了目标点
        for(int i = 0; i < cur; i++) {
            if(but[i] > 1) return ;//判断是否有重点
        }
        flag = 1;   //如果前面的要求全部达到，那么这个路径是符合条件的
        //输出路径
        printf("YES, From %d ", s);
        for(int i = 0; i < cur; i++) {
           if(i < cur) printf("to ");
            printf("%d ", step[i]);
        }
        printf("\n");
        return ;
    }
    for(int i = head[x]; ~i; i=edge[i].next) {  //遍历当前节点所有相邻的边，获取可达目标点
        if(!vis[edge[i].v]) {   //没被遍历到
            vis[edge[i].v] = 1; //标记为达到
            step[cur] = edge[i].v;//记下当前的路径
            but[edge[i].v]++; //扔到桶里，记下已经走到
            solve(cur+1, edge[i].v, y, k, step, s);//以目前到达的入点为出点，执行回溯
            but[edge[i].v]--;
            vis[edge[i].v] = 0; //回溯部分
        }
    }
}

//寻找从x到y，长度为k的简单路径
//如果有则输出所有的简单路径
void simple_path(int x, int y, int k) {
    int step[2048]; //记录路径
    flag = 0;
    for(int i = head[x]; ~i; i=edge[i].next) {
        //初始化所有的相关变量
        memset(step, 0, sizeof(step));
        memset(vis, 0, sizeof(vis));
        memset(but, 0, sizeof(but));
        step[0] = edge[i].v;
        but[edge[i].v]++;//将起点扔到桶里，防止出现重复遍历
        vis[x] = 1; //标记为已通过
        solve(1, edge[i].v, y, k, step, x); //调用回溯函数
    }
    if(!flag) { //如果没有被遍历到符合条件的情况，输出no
        printf("NO\n");
    }
}

int main() {
    freopen("in", "r", stdin);
    int uu, vv, ww;
    while(~scanf("%d %d", &n, &m)) {
        init();
        for(int i = 0; i < m; i++) { 
            scanf("%d %d %d", &uu, &vv, &ww);
            adde(uu, vv, ww);
            adde(vv, uu, ww);   //无向图，边的两头都可达
        }
        // for(int i = 1; i <= n; i++) {
        //     for(int j = head[i]; ~j; j=edge[j].next) {
        //         printf("%d %d %d\n", i, edge[j].v, edge[j].w);
        //     }
        // }
        // bfs_edge();
        bfs_vertex();
        dfs_vertex();

        //测试样例
        simple_path(3, 4, 4);
        int v1, v2, k;
        printf("Please input v1, v2 and k\n");
        scanf("%d %d %d", &v1, &v2, &k);
        printf("From v1:%d to v2:%d. lenth k:%d\n", v1, v2, k);
        // simple_path(3, 4, 3);
        simple_path(v1, v2, k);
    }
}

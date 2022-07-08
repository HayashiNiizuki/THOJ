#include <cstdio>
#define MAXSIZE 1000000
#define GetMax(a, b) a > b ? a : b
//注意全局变量数组的元素都会自动初始化为0
struct ENode {
    int vsub;
    ENode *succ;
};
struct VNode {
    int in, len; //相对于邻接表结构，额外添加了属性len以计算到每个顶点的最大路径
    ENode *fstEdge;
};
VNode adjList[MAXSIZE];
ENode *t;
int visited[MAXSIZE], stack[MAXSIZE], top = 0, maxlen = 0, n, e, i, j;
void TSort() {
    for (int k = 0; k < n; k++)
        if (!adjList[k].in)
            stack[++top] = k;
    while (top) {
        int v = stack[top--];
        for (ENode *p = adjList[v].fstEdge; p; p = p->succ) {
            //策略：动态规划-不断的更新到每个入度为0的顶点的邻居的最大路径长度
            //相对于拓扑排序，额外添加了下述2句以更新到每个邻居的最大路径长度和记录图的最大路径长度
            adjList[p->vsub].len =
                GetMax(adjList[v].len + 1, adjList[p->vsub].len);
            maxlen = GetMax(adjList[p->vsub].len, maxlen);
            if (!(--adjList[p->vsub].in))
                stack[++top] = p->vsub;
        }
    }
}
int main() {
    scanf("%d%d", &n, &e);
    for (int k = 0; k < e; k++) {
        scanf("%d%d", &i, &j);
        i--;
        j--;
        t = new ENode;
        t->vsub = j;
        adjList[j].in++;
        t->succ = adjList[i].fstEdge;
        adjList[i].fstEdge = t;
    }
    TSort();
    printf("%d\n", maxlen + 1); //最后求的是最大路径包含的顶点数，故需要+1
    return 0;
}
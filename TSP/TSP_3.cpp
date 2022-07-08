#include <cstdio>

#define max(a, b) a < b ? b : a;

struct edgeNode {
    int toNode;
    edgeNode *nextEdge = nullptr;
};

struct vertexNode {
    int inDegree = 0;
    int depth = 0;
    edgeNode *firstEdge = nullptr;
};

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    vertexNode *graphInt = new vertexNode[n];
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        graphInt[y].inDegree++;
        edgeNode *p = new edgeNode;
        p->toNode = y;
        edgeNode *q = graphInt[x].firstEdge;
        p->nextEdge = q;
        graphInt[x].firstEdge = p;
    }
    int *stack = new int[n];
    int top = 0; // top = size
    for (int i = 0; i < n; i++) {
        if (!graphInt[i].inDegree)
            stack[top++] = i;
    }
    int longest = 0;
    while (top) {
        int vertexNum = stack[--top];
        for (edgeNode *edge = graphInt[vertexNum].firstEdge; edge;
             edge = edge->nextEdge) {
            if (!(--graphInt[edge->toNode].inDegree))
                stack[top++] = edge->toNode;
            graphInt[edge->toNode].depth = max(graphInt[edge->toNode].depth,
                                               graphInt[vertexNum].depth + 1);
            longest = max(graphInt[edge->toNode].depth, longest);
        }
    }
    printf("%d\n", longest + 1);
    return 0;
}
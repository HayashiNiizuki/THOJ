#include <cstdio>

#define max(a, b) a < b ? b : a;

typedef enum { UNCOLORED, RED, BLACK } nodeColor;
typedef enum { UNDISCOVERED, DISCOVERED, VISITED } nodeStatus;

struct edgeNode {
    int friNode;
    edgeNode *nextEdge = nullptr;
};

struct vertexNode {
    nodeStatus status = UNDISCOVERED;
    nodeColor color = UNCOLORED;
    edgeNode *firstEdge = nullptr;
};

struct graph {
    // elem
    int size;
    vertexNode *_vertex;
    // functions
    graph(int);
    void insertEdge(int nodeA, int nodeB);
    void deleteEdge(int nodeA, int nodeB);
};

graph::graph(int n) {
    size = n;
    _vertex = new vertexNode[n];
}

void graph::insertEdge(int nodeA, int nodeB) {
    edgeNode *a = new edgeNode;
    edgeNode *b = new edgeNode;
    b->friNode = nodeA;
    a->friNode = nodeB;
    edgeNode *p = _vertex[nodeA].firstEdge;
    a->nextEdge = p;
    _vertex[nodeA].firstEdge = a;
    p = _vertex[nodeB].firstEdge;
    b->nextEdge = p;
    _vertex[nodeB].firstEdge = b;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    graph graphBC(n);
    // test
    // for (int i = 0; i < n; i++) {
    //     printf("%d\n",graphBC._vertex[i].status);
    // }
    // test
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        graphBC.insertEdge(x, y);
    }
    int *queue = new int[n];
    int in(0), out(0);
    // bfs
    {
        queue[in++] = 0;
        graphBC._vertex[0].status = DISCOVERED;
        graphBC._vertex[0].color = RED;
        while (in > out) {
            int nowV = queue[out++];
            for (edgeNode *p = graphBC._vertex[nowV].firstEdge; p;
                 p = p->nextEdge) {
                if (graphBC._vertex[p->friNode].status == UNDISCOVERED) {
                    graphBC._vertex[p->friNode].status = DISCOVERED;
                    queue[in++] = p->friNode;
                    if (graphBC._vertex[nowV].color == RED)
                        graphBC._vertex[p->friNode].color = BLACK;
                    else
                        graphBC._vertex[p->friNode].color = RED;
                } else if (graphBC._vertex[nowV].color ==
                           graphBC._vertex[p->friNode].color) {
                    printf("-1\n");
                    return 0;
                }
            }
            graphBC._vertex[nowV].status = VISITED;
        }
    }
    printf("1\n");
    return 0;
}
#include <cstdio>

#define Max(a, b) a > b ? a : b

struct DAG_int {
  public:
    //
    int size;
    int *vertex;
    bool *edge;
    int *depth;
    //
    DAG_int(int);
    ~DAG_int();
    void del(int);
};

DAG_int::DAG_int(int n) : size(n) {
    vertex = new int[n]{};
    depth = new int[n]{};
    edge = new bool[n * n]{};
}

DAG_int::~DAG_int() {
    delete vertex;
    delete depth;
    delete edge;
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    DAG_int dag(n);
    int u, v;
    int scale = m;
    while (scale--) {
        scanf("%d %d", &u, &v);
        dag.edge[(u - 1) * n + v - 1] = true;
        dag.vertex[v - 1]++;
    }
    scale = n;
    int *queue = new int[n]{};
    int top = 0;
    while (scale--) {
        if (!dag.vertex[scale])
            queue[top++] = scale;
    }
    int bottom = 0;
    int maxlen = 0;
    while (top - bottom + 1) {
        int j = queue[bottom++];
        for (int k = j * n; k < (j + 1) * n; k++) {
            if (dag.edge[k]) {
                dag.edge[k] = false;
                if (dag.vertex[k - (j * n - 1)] == 1)
                    queue[top++] = k - (j * n - 1);
                dag.vertex[k - (j * n - 1)]--;
                dag.depth[k - (j * n - 1)] = dag.depth[j] + 1;
                if (dag.depth[j] + 1 > maxlen)
                    maxlen = dag.depth[j] + 1;
            }
        }
    }
    printf("%d\n", maxlen + 1);
    return 0;
}
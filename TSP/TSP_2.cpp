#include <cstdio>
#define max(a, b) a < b ? b : a;
#define min(a, b) a > b ? b : a;

struct DAG_int {
  public:
    //
    int _size;
    bool **_edge;
    int *_vertex;
    //
    DAG_int(int);
    ~DAG_int();
    void del(int);
};

DAG_int::DAG_int(int size) : _size(size) {
    _vertex = new int[size];
    _edge = new bool *[size];
    for (int i = 0; i < size; i++) {
        _edge[i] = new bool[size];
    }
    for (int i = 0; i < size; i++)
        _vertex[i] = 0;
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            _edge[i][j] = 0;
}

DAG_int::~DAG_int() {
    delete _vertex;
    for (int i = 0; i < _size; i++) {
        delete[] _edge[i];
    }
    delete[] _edge;
}

void DAG_int::del(int y) {
    for (int i = 0; i < _size; i++)
        if (_edge[y][i]) {
            _edge[y][i] = false;
            _vertex[i]--;
        }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    DAG_int dag(n);
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        dag._edge[x - 1][y - 1] = true;
        dag._vertex[y - 1]++;
    }
    int *stack = new int[n + 1];
    stack[0] = 0;
    int *depth = new int[n];
    int longest = 0;
    for (int i = 0; i < n; i++) {
        if (!dag._vertex[i]) {
            stack[++stack[0]] = i;
            depth[i] = 0;
        }
    }
    while (stack[0]) {
        int v = stack[stack[0]--];
        for (int i = 0; i < n; i++) {
            if (dag._edge[v][i]) {
                if (dag._vertex[i] == 1)
                    stack[++stack[0]] = i;
                depth[i] = max(depth[i], depth[v] + 1);
                longest = max(depth[i], longest);
                dag.del(v);
            }
        }
    }
    printf("%d\n", longest + 1);
    return 0;
}
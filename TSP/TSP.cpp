#include <cstdio>

struct DAG_int {
  public:
    //
    int _size;
    bool *_edge;
    int *_vertex;
    //
    DAG_int(int);
    ~DAG_int();
    void del(int);
};

DAG_int::DAG_int(int size) : _size(size) {
    _edge = new bool[size * size];
    _vertex = new int[size];
}

DAG_int::~DAG_int() {
    delete _edge;
    delete _vertex;
}

void DAG_int::del(int x) {
    _vertex[x] = -1;
    for (int i = 0; i < _size; i++)
        if (_edge[(x - 1) * _size + i - 1] == true) {
            _edge[(x - 1) * _size + i - 1] = false;
            _vertex[i]--;
        }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    DAG_int dag(n);
    int x, y;
    int scale = m;
    while (scale--) {
        scanf("%d %d", &x, &y);
        dag._edge[y * dag._size + x - 1] = true;
        dag._vertex[y]++;
    }
    scale = 0;
    for (int i = 0; i < dag._size; i++) {
        if (dag._vertex[i])
            scale++;
    }
    int re = 0;
    while (true) {
        scale = 1;
        for (int i = 0; i < dag._size; i++) {
            if (!dag._vertex[i]) {
                dag.del(i);
                scale = 0;
            }
        }
        re++;
        if (scale)
            break;
    }
    printf("%d\n", re);
    return 0;
}
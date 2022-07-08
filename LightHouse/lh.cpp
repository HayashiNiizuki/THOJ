#include <cstdio>

struct node {
    int _x;
    int _y;
    node *pred;
    node *succ;
    node(int x = 0, int y = 0, node *p = nullptr, node *s = nullptr)
        : _x(x), _y(y), pred(p), succ(s) {}
};

class list {
  private:
    int _size;
    node *header;
    node *trailer;

  public:
    list();
    void insert(const int &x, const int &y);
    void print();
    void give(int *S);
};

list::list() {
    header = new node(0, 0);
    trailer = new node(0, 0, header);
    header->succ = trailer;
    _size = 0;
}

void list::insert(const int &x, const int &y) {
    int i = _size;
    node *p = trailer;
    do {
        p = p->pred;
        if (p->_x <= x)
            break;
    } while (i--);
    node *ad = new node(x, y, p, p->succ);
    p->succ->pred = ad;
    p->succ = ad;
    _size++;
}

void list::print() {
    printf("</test>\n");
    int n = _size;
    node *p = trailer;
    while (n--) {
        p = p->pred;
        printf("%d %d\n", p->_x, p->_y);
    }
    printf("</test>\n");
}

void list::give(int *S) {
    node *p = header;
    for (int i = 0; i < _size; i++) {
        p = p->succ;
        S[i] = p->_y;
    }
}

long invBetween(int S[], int lo, int mi, int hi) {
    long num = 0;
    int j = 0;
    int lb = mi - lo;
    int k = 0;
    int lc = hi - mi;
    int *A = S + lo;
    int B[lb];
    int i = 0;
    for (; i < lb; i++)
        B[i] = A[i];
    int *C = S + mi;
    i = 0;
    while (j < lb && k < lc) { /*A[i++] = B[j] < C[k] ? B[j++] : C[k++];*/
        if (B[j] < C[k]) {
            A[i++] = B[j++];
        } else {
            A[i++] = C[k++];
            num += (lb - j);
        }
    }
    while (j < lb)
        A[i++] = B[j++];
    return num;
}

long invInside(int S[], int lo, int hi) {
    if (hi - lo < 2)
        return 0;
    int mi = (lo + hi) >> 1;
    long num = invInside(S, lo, mi);
    num += invInside(S, mi, hi);
    num += invBetween(S, lo, mi, hi);
    return num;
}

int main() {
    list light;
    int n;
    scanf("%d", &n);
    int x, y;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        light.insert(x, y);
    }
    // light.print();
    int house[n];
    light.give(house);
    printf("%ld\n", invInside(house, 0, n));
    return 0;
}
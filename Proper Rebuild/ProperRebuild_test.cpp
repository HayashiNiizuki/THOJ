#include <cstdlib>
#include "cstdio"

using namespace std;
const int maxn = 4e6 + 100;
const int SZ = 1 << 20;  //快速io
struct fastio {
    char inbuf[SZ];
    char outbuf[SZ];

    fastio() {
        setvbuf(stdin, inbuf, _IOFBF, SZ);
        setvbuf(stdout, outbuf, _IOFBF, SZ);
    }
} io;

typedef struct node {
    int val;
    node *l, *r;
} *tree;
tree root = NULL;

int mlr[maxn], lrm[maxn];
int n;

void build(tree &t, int s1, int e1, int s2, int e2) {

    t = (tree) malloc(sizeof(node));
    t->val = mlr[s1];
    if (s1 == e1) return;
    int now;
    for (int i = s2; i <= e2; i++) {
        if (mlr[s1 + 1] == lrm[i]) {
            now = i;
            break;
        }
    }
    build(t->l, s1 + 1, now - s2 + 1 + s1, s2, now);
    build(t->r, now - s2 + 2 + s1, e1, now + 1, e2 - 1);
}

void dfs(tree now) {
    if (now == NULL) return;
    dfs(now->l);
    printf("%d ", now->val);
    dfs(now->r);
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &mlr[i]);
    }
    for (int i = 1; i <= n; i++) {
        scanf("%d", &lrm[i]);
    }
    build(root, 1, n, 1, n);
    dfs(root);
    return 0;
}
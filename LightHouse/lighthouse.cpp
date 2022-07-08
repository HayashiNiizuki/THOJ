#include <cstdio>

struct node {
    /* data */
    int _x;
    int _y;
    bool operator<(const node l) const { return _x > l._x; };
};

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
            num += (long)(lb - j);
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

template <typename T> void merge(T S[], int lo, int mi, int hi) {
    int j = 0;
    int lb = mi - lo;
    int k = 0;
    int lc = hi - mi;
    T *A = S + lo;
    T B[lb];
    int i = 0;
    for (; i < lb; i++)
        B[i] = A[i];
    T *C = S + mi;
    i = 0;
    while (j < lb && k < lc)
        A[i++] = B[j] < C[k] ? B[j++] : C[k++];
    while (j < lb)
        A[i++] = B[j++];
}

template <typename T> void mergeSort(T S[], int lo, int hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    mergeSort(S, lo, mi);
    mergeSort(S, mi, hi);
    merge(S, lo, mi, hi);
}

void print(node *S, int n) {
    printf("</test>\n");
    while (n--)
        printf("%d %d\n", S[n]._x, S[n]._y);
    printf("</test>\n");
}

int main() {
    int n;
    scanf("%d", &n);
    node light[n];
    int x, y;
    for (int i = 0; i < n; i++) {
        scanf("%d %d", &x, &y);
        light[i]._x = x;
        light[i]._y = y;
    }
    mergeSort<node>(light, 0, n);
    // print(light, n);
    int house[n];
    for (int h = 0; h < n; h++)
        house[h] = light[h]._y;
    printf("%ld\n", invInside(house, 0, n));
    return 0;
}
#include <cstdio>

void swap(int &a, int &b) {
    int c = a;
    a = b;
    b = c;
}

void merge(int S[], int lo, int mi, int hi) {
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
    while (j < lb && k < lc)
        A[i++] = B[j] < C[k] ? B[j++] : C[k++];
    while (j < lb)
        A[i++] = B[j++];
}

void mergeSort(int S[], int lo, int hi) {
    if (hi - lo < 2)
        return;
    int mi = (lo + hi) >> 1;
    mergeSort(S, lo, mi);
    mergeSort(S, mi, hi);
    merge(S, lo, mi, hi);
}

template <typename T> T min(const T &a, const T &b) { return (a < b) ? a : b; }

int search(int S[], int x, int lo, int hi) {
    while (lo < hi) {
        int mi = (lo + hi) >> 1;
        if (S[mi] < x)
            lo = mi + 1;
        else if (S[mi] > x)
            hi = mi;
        else
            return mi;
    }
    return hi;
}

int main() {
    int n, m;
    // input n,m
    scanf("%d %d", &n, &m);
    if (n == 0)
        return 0;
    // input vector
    int S[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &S[i]);
    }
    // sort
    mergeSort(S, 0, n);
    /*
    for (int i = 0; i < n; i++)
        printf("%d ", S[i]);
    printf("\n");
    */
    int a, b, lo, hi;
    // search
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &a, &b);
        lo = search(S, a, 0, n);
        hi = search(S, b + 1, lo, n);
        printf("%d\n", hi - lo);
    }
    return 0;
}

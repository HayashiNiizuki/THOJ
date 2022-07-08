#include <cstdio>

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
    int *C = A + mi;
    i = 0;
    while (j < lb && k < lc)
        A[i++] = B[j] < C[k] ? B[j++] : C[k++];
    while (j < lb)
        A[i++] = B[j++];
    for (int h = 0; h < 6; h++)
        printf("%d ", S[h]);
    printf("\n");
}

int main() {
    int S[] = {1, 3, 5, 2, 4, 6};
    merge(S, 0, 3, 6);
    return 0;
}
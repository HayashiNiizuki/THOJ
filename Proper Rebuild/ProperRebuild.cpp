#include <cstdio>

int search(const int *array, int elem) {
    int i = 0;
    while (array[i] != elem)
        i++;
    return i;
}

void rebulid(const int *pre, const int *post, int n) {
    if (n == 1) {
        printf("%d ", pre[0]);
        return;
    }
    int parent = pre[0];
    int leftChild = pre[1];
    int rightChlid = post[1];
    int leftLength = search(pre + 1, post[1]);
    int rightLength = n - leftLength - 1;
    rebulid(pre + 1, post + rightLength + 1, leftLength);
    printf("%d ", parent);
    rebulid(pre + 1 + leftLength, post + 1, rightLength);
    return;
}

int main(int argc, char *argv[]) {
    // input
    int n;
    scanf("%d", &n);
    int pre[n];
    int post[n];
    for (int i = 0; i < n; i++)
        scanf("%d", &pre[i]);
    for (int i = n - 1; i > -1; i--)
        scanf("%d", &post[i]);
    // output
    rebulid(pre, post, n);
    return 0;
}
#include <cstdio>

typedef enum { UNCOLORED, RED, BLACK } nodeColor;

nodeColor world[10000];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);
    int x, y;
    for (int i = 0; i < m; i++) {
        scanf("%d %d", &x, &y);
        x--;
        y--;
        switch (world[x] * world[y]) {
        case 0:
            if (world[x])
                world[y] = world[x] < 2 ? BLACK : RED;
            else if (world[y])
                world[x] = world[y] < 2 ? BLACK : RED;
            else {
                world[x] = RED;
                world[y] = BLACK;
            }
            break;
        case 1:
            printf("-1\n");
            return 0;
        case 4:
            printf("-1\n");
            return 0;
        case 2:
            break;
        }
    }
    printf("1\n");
    return 0;
}
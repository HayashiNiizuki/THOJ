#include <cstdio>

// a simple implementation
class intStack {
  private:
    int _size = 0;
    int *_elem;

  public:
    intStack(int n) : _size(0) { _elem = new int[n]; };
    int size() { return _size; }
    void push(int const &e) { _elem[_size++] = e; }
    int pop() { return _elem[--_size]; }
    int top() {
        if (_size == 0)
            return -1;
        return _elem[_size - 1];
    }
};

int main() {
    int m, n;
    scanf("%d %d", &n, &m);
    intStack A(n), B(n), S(m);
    int a;
    scanf("%d", &a);
    B.push(a);
    // input include space
    for (int i = 1; i < n; i++) {
        scanf(" %d", &a);
        B.push(a);
    }
    int order = n;
    intStack Order(2 * n); // a stack for output
    while (order) {
        if (S.top() == order) {
            A.push(S.pop());
            Order.push(0);
            order--;
        } else if (S.size() == m) {
            break;
        } else if (B.size() == 0) {
            break;
        } else {
            S.push(B.pop());
            Order.push(1);
        }
    }
    if (order > 0)
        printf("No\n");
    else {
        for (int i = 0; i < 2 * n; i++) {
            if (Order.pop())
                printf("pop\n");
            else
                printf("push\n");
        }
    }
    return 0;
}
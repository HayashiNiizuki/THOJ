#include <cstdio>
#include <cstring>

template <typename T> void swap(T &a, T &b) {
    T c = b;
    b = a;
    a = c;
    return;
}

#define parent(i) ((i - 1) >> 1)
#define lChild(i) ((i << 1) + 1)
#define rChild(i) ((i + 1) << 1)

struct task {
    long long int prior;
    char name[9];
    bool operator<(const task &) const;
    bool operator>(const task &) const;
};

bool task::operator<(const task &right) const {
    if (this->prior < right.prior)
        return true;
    else if (this->prior == right.prior && (strcmp(this->name, right.name) < 0))
        return true;
    else
        return false;
}

bool task::operator>(const task &right) const { return right < *this; }

class priorQu {
  protected:
    int size;
    task *root;
    int priorChild(int);

  public:
    priorQu(int);
    void insert(task);
    task pop();
    task top();
    bool isEmpty();
};

priorQu::priorQu(int maxSize) : size(0) { root = new task[maxSize]; }

task priorQu::top() { return root[0]; }

int priorQu::priorChild(int parent) {
    int lChild = lChild(parent);
    int rChild = lChild + 1;
    if (lChild < size && rChild < size)
        return root[lChild].prior < root[rChild].prior ? lChild : rChild;
    else if (lChild < size)
        return lChild;
    else
        return size;
}

void priorQu::insert(task newTask) {
    root[size++] = newTask;
    int i = size - 1;
    int parent = parent(i);
    while (parent > -1) {
        if (root[i] < root[parent]) {
            swap(root[i], root[parent(i)]);
        }
        i = parent;
        parent = parent(i);
    }
}

task priorQu::pop() {
    task backup = root[0];
    root[0] = root[--size];
    int i = 0;
    int child = priorChild(i);
    while (child < size) {
        if (root[i] > root[child])
            swap(root[i], root[child]);
        i = child;
        child = priorChild(i);
    }
    return backup;
}

bool priorQu::isEmpty() { return size <= 0; }

int main(int argc, char const *argv[]) {
    long long int maxI = 2147483648;
    int n, m;
    // input n and m
    scanf("%d %d", &n, &m);
    // input priority and task name
    task temp;
    priorQu qu(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld %s", &temp.prior, temp.name);
        qu.insert(temp);
    }
    for (int i = 0; i < m; i++) {
        if (!qu.isEmpty()) {
            task out = qu.pop();
            printf("%s\n", out.name);
            if (out.prior < maxI) {
                out.prior *= 2;
                qu.insert(out);
            }
        } else
            break;
    }
    return 0;
}

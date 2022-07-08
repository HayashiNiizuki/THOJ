#include <cstdio>
#include <cstring>
#include <cstdlib>

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
    unsigned int prior;
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
    unsigned int priorChild(unsigned int);

  public:
    priorQu(int);
    void insert(task);
    task pop();
    task top();
    bool isEmpty();
};

priorQu::priorQu(int maxSize) : size(0) { root = new task[maxSize]; }

task priorQu::top() { return root[0]; }

unsigned int priorQu::priorChild(unsigned int parent) {
    long lChild = lChild(parent);
    long rChild = lChild + 1;
    if (lChild < size && rChild < size)
        return root[lChild].prior < root[rChild].prior ? lChild : rChild;
    else if (lChild < size)
        return lChild;
    else if (rChild < size)
        return rChild;
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
    priorQu qu(100);
    task temp;
    strcpy(temp.name, "test");
    for (int i = 0; i < 100; i++) {
        temp.prior = rand();
        qu.insert(temp);
    }
    for (int i = 0; i < 100; i++) {
        temp = qu.pop();
        printf("%lld\t", temp.prior);
        if (i % 10 == 9)
            printf("\n");
    }
}

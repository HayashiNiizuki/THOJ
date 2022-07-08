#include <cstdio>

struct node {
    node *pred;
    node *succ;
    char elem;
    node(char e, node *p = nullptr, node *s = nullptr)
        : pred(p), succ(s), elem(e) {}
};

class list {
  private:
    int _size;
    node *header;
    node *trailer;

  public:
    list();
    node *insert(char const &in, int place);
    void insertAsLast(char const &e);
    bool remove(node *const, int lo);
    void print();
};

list::list() {
    header = new node(0);
    trailer = new node(0, header);
    header->succ = trailer;
    _size = 0;
}

node *list::insert(char const &in, int place) {
    node *po = header;
    while (place--)
        po = po->succ;
    node *ins = new node(in, po, po->succ);
    po->succ->pred = ins;
    po->succ = ins;
    _size++;
    return ins;
}

void list::insertAsLast(char const &e) {
    node *a = new node(e, trailer->pred, trailer);
    trailer->pred->succ = a;
    trailer->pred = a;
    _size++;
};

bool list::remove(node *const low, int place) {
    node *lo = low;
    node *hi = low->succ;
    int left = place - 1;
    int right = place + 1;
    char eleme = lo->elem;
    lo = lo->pred;
    while (left >= 0 && lo->elem == eleme) {
        left--;
        lo = lo->pred;
    }
    while (right < _size && hi->elem == eleme) {
        right++;
        hi = hi->succ;
    }
    int num = right - left - 1;
    if (num > 2) {
        lo->succ = hi;
        hi->pred = lo;
        _size -= num;
        remove(lo, left);
        return true;
    }
    return false;
}

void list::print() {
    if (_size < 1) {
        printf("-\n");
        return;
    }
    node *p = header->succ;
    for (int i = 0; i < _size; i++, p = p->succ)
        printf("%c", p->elem);
    printf("\n");
}

int main() {
    list zuma;
    char in = 0;
    scanf("%c", &in);
    while ('@' < in) {
        zuma.insertAsLast(in);
        scanf("%c", &in);
    }
    int n = 0;
    scanf("%d", &n);
    int place;
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &place, &in);
        zuma.remove(zuma.insert(in, place), place);
        zuma.print();
    }
    return 0;
}
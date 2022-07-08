#include <stdio.h>

class zuma {
  public:
    int size = 0;
    char _zuma[20000];
    zuma();
    int insert(char in, int place);
    bool remove(int pl);
    void print();
};

zuma::zuma() {
    size = 0;
    do {
        scanf("%c", &_zuma[size]);
    } while ('@' < _zuma[size++]);
    size--;
}

int zuma::insert(char in, int place) {
    for (int i = size; i > place; i--)
        _zuma[i] = _zuma[i - 1];
    _zuma[place] = in;
    size++;
    return size;
}

void zuma::print() {
    if (size < 1) {
        printf("-\n");
        return;
    }
    for (int i = 0; i < size; i++)
        printf("%c", _zuma[i]);
    printf("\n");
}

bool zuma::remove(int p) {
    char elem = _zuma[p];
    int lo = p - 1, hi = p;
    while (_zuma[lo] == elem && lo >= 0)
        lo--;
    while (_zuma[hi] == elem && hi < size)
        hi++;
    int num = hi - lo - 1;
    if (num > 2) {
        for (int i = hi; i < size; i++)
            _zuma[i - num] = _zuma[i];
        size -= num;
        remove(lo);
        return true;
    }
    return false;
}

int main() {
    zuma zu;
    int n = 0;
    scanf("%d", &n);
    char in;
    int place;
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &place, &in);
        zu.insert(in, place);
        zu.remove(place);
        zu.print();
    }
    return 0;
}

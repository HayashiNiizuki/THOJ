#include <stdio.h>

struct pair {
    int lo;
    int hi;
};

class zuma {
  public:
    int size = 0;
    char _zuma[20000];
    zuma();
    int insert(char in, int place);
    pair touch(pair pa);
    void print();
    void del(pair pa);
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

void zuma::del(pair pa) {
    int num = pa.hi - pa.lo - 1;
    if (num > 2) {
        for (int i = pa.hi; i < size; i++) {
            _zuma[i - num] = _zuma[i];
        }
        size -= num;
    }
}

pair zuma::touch(pair pa) {
    pair pa1 = pa;
    char elem = _zuma[pa1.lo];
    pa1.lo--;
    while (_zuma[pa1.lo] == elem && pa1.lo >= 0)
        pa1.lo--;
    while (_zuma[pa1.hi] == elem && pa1.hi < size)
        pa1.hi++;
    int num = (pa1.hi - pa.hi) + (pa.lo - pa1.lo);
    if (num > 2)
        return touch(pa1);
    else
        return pa;
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
        pair pa = {place, place + 1};
        pa = zu.touch(pa);
        zu.del(pa);
        zu.print();
    }
    return 0;
}

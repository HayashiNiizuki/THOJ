#include <stdio.h>

class zuma {
  public:
    int size = 0;
    char _zuma[20000];
    zuma();
    int insert(char in, int place);
    bool remove(int &lo, int &hi);
    void remove(int &lo, int &hi, bool ju);
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
    for (int i = size; i > place - 1; i--)
        _zuma[i] = _zuma[i - 1];
    _zuma[place - 1] = in;
    int lo = place - 1;
    int hi = place;
    int ju = remove(lo, hi);
    if (ju == 1) {
        int rm = hi - lo - 1;
        for (int i = lo + 1; i < size - rm; i++)
            _zuma[i] = _zuma[i + rm];
        size -= rm - 1;
    } else
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

bool zuma::remove(int &lo, int &hi) {
    int ju = 0;
    if (lo < 0 || hi > size)
        return 0;
    if (_zuma[lo] == _zuma[hi]) {
        if (_zuma[lo - 1] == _zuma[hi] && 0 < lo) {
            lo--;
            while (_zuma[lo - 1] == _zuma[lo] && 0 < --lo)
                lo--;
            while (_zuma[hi + 1] == _zuma[hi] && hi < size)
                hi++;
            lo--;
            hi++;
            ju = 1;
            remove(lo, hi);
        } else if (_zuma[lo] == _zuma[hi + 1] && hi < size) {
            hi++;
            while (_zuma[lo - 1] == _zuma[lo] && 0 < lo)
                lo--;
            while (_zuma[hi + 1] == _zuma[hi] && hi < size)
                hi++;
            lo--;
            hi++;
            ju = 1;
            remove(lo, hi);
        }
    }
    return ju;
}

void zuma::remove(int &lo, int &hi, bool ju) {}

int main() {
    zuma zu;
    int n = 0;
    scanf("%d", &n);
    char in;
    int place;
    for (int i = 0; i < n; i++) {
        scanf("%d %c", &place, &in);
        zu.insert(in, place + 1);
        zu.print();
    }
    return 0;
}

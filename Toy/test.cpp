#include <iostream>

class MyCircularDeque {
  private:
    int maxCapa;
    int size;
    unsigned short *elem;
    int head = 0;
    int tail = 0;

  public:
    MyCircularDeque(int k);
    bool insertFront(int value);
    bool insertLast(int value);
    bool deleteFront();
    bool deleteLast();
    int getFront();
    int getRear();
    bool isEmpty();
    bool isFull();
};

MyCircularDeque::MyCircularDeque(int k)
    : maxCapa(k), size(0), head(0), tail(0) {
    elem = new unsigned short[k];
}

bool MyCircularDeque::insertFront(int value) {
    if (isFull())
        return false;
    else {
        if (head == 0)
            elem[head = (maxCapa - 1)] = value;
        else
            elem[--head] = value;
        size++;
        return true;
    }
}

bool MyCircularDeque::insertLast(int value) {
    if (isFull())
        return false;
    else {
        if (tail == (maxCapa - 1)) {
            elem[maxCapa - 1] = value;
            tail = 0;
        } else
            elem[tail++] = value;
        size++;
        return true;
    }
}

bool MyCircularDeque::deleteFront() {
    if (!size)
        return false;
    else {
        if (head == (maxCapa - 1))
            head = 0;
        else
            head++;
        size--;
        return true;
    }
}

bool MyCircularDeque::deleteLast() {
    if (!size)
        return false;
    else {
        if (tail == 0)
            tail = maxCapa - 1;
        else
            tail--;
        size--;
        return true;
    }
}

int MyCircularDeque::getFront() { return !size ? -1 : elem[head]; }

int MyCircularDeque::getRear() {
    if (!size)
        return -1;
    else {
        if (!tail)
            return elem[maxCapa - 1];
        else
            return elem[tail - 1];
    }
}

bool MyCircularDeque::isEmpty() { return !size; }

bool MyCircularDeque::isFull() { return (head == tail) && size; }

enum target { EXCHANGE, LOOP, ROTATE };
static const short factorial[8] = {1, 1, 2, 6, 24, 120, 720, 5040};

unsigned char oct(unsigned int num, int index) {
    return ((num >> ((8 - index) * 3)) & 0x7) + 48;
}

unsigned short cantor(unsigned int in) {
    unsigned short out = 0;
    for (int i = 0; i < 8; i++) {
        int smaller = 0;
        for (int j = i + 1; j < 8; j++) {
            if (oct(in, j + 1) < oct(in, i + 1))
                smaller++;
        }
        out += smaller * factorial[8 - i - 1];
    }
    return out;
}

unsigned int reCantor(unsigned short in) {
    unsigned int out(0);
    unsigned int A[8];
    bool *take = new bool[8];
    for (int i = 0; i < 8; i++) {
        A[i] = in / factorial[7 - i];
        in %= factorial[7 - i];
    }
    for (int i = 0; i < 8; i++) {
        out <<= 3;
        unsigned int j = 0;
        for (; j < A[i] + 1; j++) {
            if (take[j])
                A[i]++;
        }
        take[--j] = true;
        out |= j;
    }
    return out;
}

unsigned int exc(unsigned int in) {
    unsigned int out = in & 0x7;
    for (int i = 0; i < 7; i++) {
        in >>= 3;
        out <<= 3;
        out |= in & 0x7;
    }
    return out;
}

unsigned int loo(unsigned int in) {
    unsigned int right = (in >> 3) & 0x1FF;
    right |= ((in & 0x7) << 9);
    unsigned int out = (in << 3) & 0xFF8000;
    out |= ((in >> 21) << 12);
    out |= right;
    return out;
}

unsigned int rot(unsigned int in) {
    unsigned int out = in & 0xE07E07;
    out |= ((in & 0x1C0000) >> 15);
    out |= ((in & 0x038000) << 3);
    out |= ((in & 0x0001C0) << 9);
    out |= ((in & 0x000038) << 3);
    return out;
}

void printToy(unsigned int in) {
    unsigned int mask = 0xE00000;
    for (int i = 0; i < 8; i++) {
        std::cout << (((in & mask) >> ((7 - i) * 3)) + 1);
        mask = mask >> 3;
    }
    // std::cout << std::endl;
    return;
}

class Toy {
  private:
    unsigned int status = 0;
    short leastTrans = -1;

  public:
    Toy();

    //
    unsigned int getStatus() const;
    short getTrans() const;
    void setTr(short);
    void setSt(unsigned int);
};

Toy::Toy() : status(0), leastTrans(-1) {}

unsigned int Toy::getStatus() const { return status; }

short Toy::getTrans() const { return leastTrans; }

void Toy::setTr(short depth) { leastTrans = depth; }

void Toy::setSt(unsigned int in) { status = in; }

Toy *stGa = new Toy[40320];

void checkQu(MyCircularDeque &Qu, unsigned short i, unsigned short be) {
    if (stGa[i].getTrans() == -1) {
        stGa[i].setTr(stGa[be].getTrans() + 1);
        Qu.insertLast(i);
    }
}

void BFS() {
    MyCircularDeque deq(40320);
    deq.insertLast(0);
    unsigned short noIn;
    stGa[0].setTr(0);
    stGa[0].setSt(reCantor(0));
    while (!deq.isEmpty()) {
        noIn = deq.getFront();
        deq.deleteFront();
        unsigned int Exc = exc(stGa[noIn].getStatus());
        unsigned int Loo = loo(stGa[noIn].getStatus());
        unsigned int Rot = rot(stGa[noIn].getStatus());
        unsigned short wExc = cantor(Exc);
        unsigned short wLoo = cantor(Loo);
        unsigned short wRot = cantor(Rot);
        stGa[wExc].setSt(Exc);
        stGa[wLoo].setSt(Loo);
        stGa[wRot].setSt(Rot);
        checkQu(deq, wExc, noIn);
        checkQu(deq, wLoo, noIn);
        checkQu(deq, wRot, noIn);
    }
}

int main(int argc, char *argv[]) {
    BFS();
    for (int i = 0; i < 40320; i++) {
        std::cout << stGa[i].getTrans() << ',';
    }
}
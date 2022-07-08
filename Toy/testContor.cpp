#include <iomanip>
#include <iostream>
#include <string>

enum target { EXCHANGE, LOOP, ROTATE };
static const short factorial[8] = {1, 1, 2, 6, 24, 120, 720, 5040};
static const short prime[8] = {2, 3, 5, 7, 11, 13, 17, 19};

unsigned char oct(unsigned int num, int index) {
    return ((num >> ((8 - index) * 3)) & 0x7) + 48;
}

unsigned short contor(unsigned int in) {
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
    unsigned int out = in << 3;
    out |= (in >> 21);
    out &= 0xFFFFFF;
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
    Toy *exchange, *loop, *rotate;
    // Toy *unexchange, *unloop, *unrotate;
    short leastTrans;

  public:
    Toy();
    Toy(unsigned int);
    Toy(const Toy &, target);
    Toy(std::string);

    //
    unsigned int getStatus() const;
    short getTrans() const;
};

Toy::Toy()
    : status(0), exchange(nullptr), loop(nullptr), rotate(nullptr),
      leastTrans(-1) {}

Toy::Toy(unsigned int s)
    : status(s), exchange(nullptr), loop(nullptr), rotate(nullptr),
      leastTrans(-1) {}

Toy::Toy(const Toy &sour, target t)
    : exchange(nullptr), loop(nullptr), rotate(nullptr) {
    switch (t) {
    case EXCHANGE:
        status = exc(sour.getStatus());
        break;
    case LOOP:
        status = loo(sour.getStatus());
        break;
    case ROTATE:
        status = rot(sour.getStatus());
        break;
    }
    if (sour.getTrans())
        leastTrans = sour.getTrans() + 1;
    else
        leastTrans = -1;
}

Toy::Toy(std::string input) {}

unsigned int Toy::getStatus() const { return status; }

short Toy::getTrans() const { return leastTrans; }

int main(int argc, char *argv[]) {
    bool correct = true;
    // max: 0xFAC689
    // as screen: 0x55000
    for (unsigned int i = 0; i < 0xFAC689; i++) {
        int a = 1;
        unsigned int ii = i;
        for (int j = 0; j < 8; j++) {
            a *= prime[ii & 0x7];
            ii >>= 3;
        }
        if (a == 9699690 && (i != (reCantor(contor(i))))) {
            correct = false;
            printToy(i);
            std::cout << "\t" << contor(i) << "\t";
            printToy(reCantor(contor(i)));
            std::cout << std::endl;
        }
    }
    if (correct)
        std::cout << "contor is correct!\n";
    return 0;
}
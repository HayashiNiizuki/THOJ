#include <cstdlib>
#include <ctime>
#include <iostream>
// class 2dTree
// #include "include/kdTree.h"
#include "include/priorQu.h"
#include "printPQ.hpp"


int main(int argc, char const *argv[]) {
    std::cout << "exe start.\n";
    hys::priorQu<int> qu;
    srand((unsigned)time(NULL));
    for (int i = 0; i < 10; i++) {
        qu.insert(rand() % 1000);
        printPQ(qu);
    }
    for (int i = 0; i < 10; i++) {
        // std::cout << qu.pop() << " ";
        // if (i % 10 == 9)
        //     std::cout << std::endl;
        qu.pop();
        printPQ(qu);
    }
    return 0;
}

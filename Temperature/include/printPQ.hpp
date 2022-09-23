#include <iostream>
#include "priorQu.h"

void printPQ(const hys::priorQu<int> &pq) {
    std::cout << "\n" << "Size: " << pq.size() << "\n\n";
    int line = 0;
    for (int i = 0; i < pq.size(); i++) {
        std::cout << pq[i] << ' ';
        if (i == line) {
            std::cout << std::endl;
            line = (line + 2)  * 2 - 2;
        }
    }
    std::cout << std::endl;
}

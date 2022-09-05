#pragma once

#include <vector>

namespace hys {
// priority queue
template <typename T> class priorQu {
  private:
    std::vector<T> __data__;

  public:
    priorQu();
    priorQu(const std::vector<T> &);
    int size() const;
    static int parent(int);
    static int lChild(int);
    static int rChild(int);
    T root() const;
    T pop();
    void insert(T);
    // NOTE: for test
//   private:
    T take(int) const;
};

template <typename T> priorQu<T>::priorQu() { __data__ = *(new std::vector<T>); }

template <typename T> priorQu<T>::priorQu(const std::vector<T> &elems) {
    __data__ = *(new std::vector<T>);
    for (int i = 0; i < elems.size(); i++)
        this->insert(elems[i]);
}

template <typename T> int priorQu<T>::parent(int i) { return (i - 1) >> 1; }
template <typename T> int priorQu<T>::lChild(int i) { return (i << 1) + 1; }
template <typename T> int priorQu<T>::rChild(int i) { return (i + 1) << 1; }

template <typename T> T priorQu<T>::root() const { return __data__[0]; }

template <typename T> T priorQu<T>::pop() {
    T backup = __data__[0];
    __data__[0] = __data__.back();
    __data__.pop_back();
    if (__data__.empty())
        return backup;
    int i = 0;
    while (rChild(i) < __data__.size()) {
        int child = __data__[lChild(i)] < __data__[rChild(i)] ? lChild(i) : rChild(i);
        if (__data__[i] > __data__[child]) {
            std::swap(__data__[i], __data__[child]);
            i = child;
        } else
            break;
    }
    return backup;
}

template <typename T> void priorQu<T>::insert(T t) {
    int i = __data__.size();
    __data__.push_back(t);
    while (true) {
        if (i && __data__[parent(i)] > __data__[i]) {
            std::swap(__data__[i], __data__[parent(i)]);
            i = parent(i);
        } else
            break;
    }
    return;
}

template <typename T> int priorQu<T>::size() const { return __data__.size(); }

template <typename T> T priorQu<T>::take(int i) const { return __data__.at(i); }

} // namespace hys

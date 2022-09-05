#pragma once

#include <vector>

namespace hys {
// priority queue
template <typename T> class priorQu {
  private:
    std::vector<T> data_;

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

template <typename T> priorQu<T>::priorQu() { data_ = *(new std::vector<T>); }

template <typename T> priorQu<T>::priorQu(const std::vector<T> &elems) {
    data_ = *(new std::vector<T>);
    for (int i = 0; i < elems.size(); i++)
        this->insert(elems[i]);
}

template <typename T> int priorQu<T>::parent(int i) { return (i - 1) >> 1; }
template <typename T> int priorQu<T>::lChild(int i) { return (i << 1) + 1; }
template <typename T> int priorQu<T>::rChild(int i) { return (i + 1) << 1; }

template <typename T> T priorQu<T>::root() const { return data_[0]; }

template <typename T> T priorQu<T>::pop() {
    T backup = data_[0];
    data_[0] = data_.back();
    data_.pop_back();
    if (data_.empty())
        return backup;
    int i = 0;
    while (rChild(i) < data_.size()) {
        int child = data_[lChild(i)] < data_[rChild(i)] ? lChild(i) : rChild(i);
        if (data_[i] > data_[child]) {
            std::swap(data_[i], data_[child]);
            i = child;
        } else
            break;
    }
    return backup;
}

template <typename T> void priorQu<T>::insert(T t) {
    int i = data_.size();
    data_.push_back(t);
    while (true) {
        if (i && data_[parent(i)] > data_[i]) {
            std::swap(data_[i], data_[parent(i)]);
            i = parent(i);
        } else
            break;
    }
    return;
}

template <typename T> int priorQu<T>::size() const { return data_.size(); }

template <typename T> T priorQu<T>::take(int i) const { return data_.at(i); }

} // namespace hys

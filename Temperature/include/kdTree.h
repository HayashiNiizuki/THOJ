#pragma once

// This is header file of k-dimension tree

#include "point2d.h"
#include <vector>

namespace hys {
template <typename X, typename Y> struct kdTreeNode2 {
    point2d<X, Y> data;
    kdTreeNode2<X, Y> *lChild = nullptr;
    kdTreeNode2<X, Y> *rChild = nullptr;
};

template <typename X, typename Y> class kdTree2 {
  private:
    point2d<X, Y> *root;

  public:
    // constructor
    kdTree2();
    kdTree2(const std::vector<point2d<X, Y>> &);
    // member functions
    point2d<X, Y> search(point2d<X, Y>) const;
    bool insert(point2d<X, Y>);
    bool remove(point2d<X, Y>);
};

template <typename X, typename Y> kdTree2<X, Y>::kdTree2() {
    root = new kdTreeNode2<X, Y>;
}

template <typename X, typename Y>
kdTree2<X, Y>::kdTree2(const std::vector<point2d<X, Y>> &nodes) {
    ;
}

} // namespace hys
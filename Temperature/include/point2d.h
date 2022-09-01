#pragma once

// This is header file of a simple 2d point template

namespace hys {
template <typename X, typename Y> struct point2d {
    X x;
    Y y;
    static enum { XO, YO } dimen = XO;
    point2d();
    point2d(X, Y);
    bool operator>(const point2d &);
    bool operator<(const point2d &);
};

template <typename X, typename Y>
point2d<X, Y>::point2d() { // default constructor
    x = new X;
    y = new Y;
}

template <typename X, typename Y>
point2d<X, Y>::point2d(X varx, Y vary) : x(varx), y(vary) {}

template <typename X, typename Y>
bool point2d<X, Y>::operator>(const point2d &rPoint) {
    return dimen == XO ? this->x > rPoint.x : this->y > rPoint.y;
}

template <typename X, typename Y>
bool point2d<X, Y>::operator<(const point2d &rPoint) {
    return rPoint > *this;
}
} // namespace hys
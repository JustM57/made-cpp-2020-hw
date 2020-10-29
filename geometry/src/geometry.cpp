#include "geometry.h"

using namespace geometry;

Point::Point() : x(0), y(0) {};

Point::Point(double x, double y) : x(x), y(y) {};

bool Point::operator==(const Point& other) const{
    return ((std::abs(this->x - other.x) < EPS) && (std::abs(this->y - other.y) < EPS));
};

bool Point::operator!=(const Point& other) const{
    return ((std::abs(this->x - other.x) >= EPS) || (std::abs(this->y - other.y) >= EPS));
};

Line::Line(double k, double b) : a(-1), b(k), c(b) {};

Line::Line(const Point &p, double k) {
    // y = kx + b => b = y - kx
    this->a = -1;
    this->b = k;
    this->c = p.y - k * p.x;
};

Line::Line(const Point &p1, const Point &p2) {
    this->a = p1.y - p2.y;
    this->b = p1.x - p2.x;
    this->c = p1.x * p2.y - p1.y * p2.x;
};

bool Line::operator==(const Line &other) const {
    double k1, k2, k3;
    if (std::abs(other.a - 0) >= EPS) {
        k1 = this->a / other.a;
    } else k1 = this->b / other.b;
    if (std::abs(other.b - 0) >= EPS) {
        k2 = this->b / other.b;
    } else k2 = k1;
    if (std::abs(other.c - 0) >= EPS) {
        k3 = this->c / other.c;
    } else k3 = k1;
    return ((std::abs(k1 / k2 - 1) < EPS) && (std::abs(k1 / k3 - 1) < EPS));
};

bool Line::operator!=(const Line &other) const {
    double k1, k2, k3;
    if (std::abs(other.a - 0) >= EPS) {
        k1 = this->a / other.a;
    } else k1 = this->b / other.b;
    if (std::abs(other.b - 0) >= EPS) {
        k2 = this->b / other.b;
    } else k2 = k1;
    if (std::abs(other.c - 0) >= EPS) {
        k3 = this->c / other.c;
    } else k3 = k1;
    return ((std::abs(k1 / k2 - 1) >= EPS) || (std::abs(k1 / k3 - 1) >= EPS));
};


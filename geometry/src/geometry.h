#pragma once
#include <cmath>

namespace geometry {
    const double EPS = 1e-6;

    struct Point {
        double x, y;
        Point();
        Point(double x, double y);
        bool operator==(const Point& other) const;
        bool operator!=(const Point& other) const;
    };


};

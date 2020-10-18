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

    class Line {
    private:
        // a x + b y + c = 0
        double a, b, c;
    public:
        Line(const Point& p1, const Point& p2);
        Line(double k, double b);
        Line(const Point& p, double k);
        bool operator==(const Line& other) const;
        bool operator!=(const Line& other) const;
    };


};

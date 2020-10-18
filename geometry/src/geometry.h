#pragma once
#define _USE_MATH_DEFINES
#include <cmath>
#include <vector>
#include <iostream>
#include <tuple>


const double EPS = 1e-6;


struct Point {
    double x;
    double y;

    Point() : x(0), y(0) {};

    Point(double x, double y) : x(x), y(y) {};

    bool operator==(const Point& other) const {
        return ((std::abs(this->x - other.x) < EPS) && (std::abs(this->y - other.y) < EPS));
    };

    bool operator!=(const Point& other) const {
        return ((std::abs(this->x - other.x) >= EPS) || (std::abs(this->y - other.y) >= EPS));
    };
};


class Line {
private:
    // a x + b y + c = 0
    double a, b, c;
public:
    Line(const Point &p1, const Point &p2) {
        this->a = p1.y - p2.y;
        this->b = p1.x - p2.x;
        this->c = p1.x * p2.y - p1.y * p2.x;
    };

    Line(double k, double b) : a(-1), b(k), c(b) {};

    Line(const Point &p, double k) {
        // y = kx + b => b = y - kx
        this->a = -1;
        this->b = k;
        this->c = p.y - k * p.x;
    };

    std::tuple<double, double, double> getCoefficients() const {
        return std::make_tuple(this->a, this->b, this->c);
    }

    bool operator==(const Line &other) const {
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

    bool operator!=(const Line &other) const {
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
};


double pointDistance(const Point& p1, const Point& p2){
    return std::sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}


class Shape {
public:
    virtual double perimeter() const {};
    virtual double area() const {};
    virtual bool operator ==(const Shape& another) {};
    virtual bool operator !=(const Shape& another) {};
    virtual void rotate(Point center, double angle) {};
    virtual void reflex(Point center) {};
    virtual void reflex(Line axis) {};
    virtual void scale(Point center, double coefficient) {};
};


class Ellipse: public Shape {
private:
    Point f1, f2;
    double a;

public:
    Ellipse(Point f1, Point f2, double a) : f1(f1), f2(f2), a(a) {};

    std::pair<Point, Point> focuses() const {
        return std::make_pair(f1, f2);
    };

    double eccentricity() const {
        double f_dist = pointDistance(this->f1, this->f2);
        double b_sqr = a *  a - f_dist * f_dist;
        double e = std::sqrt(1 - b_sqr / (a * a));
        return e;
    };

    double radius() const {
        return this->a / 2;
    }

    Point center() const {
        Point res((this->f1.x + this->f2.x) / 2, (this->f1.y + this->f2.y) / 2);
        return res;
    };

    double perimeter() const override {
        return 2 * a * std::comp_ellint_2(this->eccentricity());
    };

    double area() const override {
        double f_dist = pointDistance(this->f1, this->f2);
        double b = std::sqrt(a *  a - f_dist * f_dist);
        return M_PI * a * b / 4;
    };

    bool operator==(const Ellipse& another) {
        if (((this->f1 == another.f1) && (this->f2 == another.f2)) && (this->a == another.a))
            return true;
        if (((this->f1 == another.f2) && (this->f2 == another.f1)) && (this->a == another.a))
            return true;
        return false;
    };

    bool operator!=(const Ellipse& another) {
        if (((this->f1 == another.f1) && (this->f2 == another.f2)) && (this->a == another.a))
            return false;
        if (((this->f1 == another.f2) && (this->f2 == another.f1)) && (this->a == another.a))
            return false;
        return true;
    };

    void rotate(Point center, double angle) override {
        double x1, y1;
        f1.x -= center.x;
        f1.y -= center.y;
        x1 = f1.x * std::cos(angle) - f1.y * std::sin(angle);
        y1 = f1.x * std::sin(angle) + f1.y * std::cos(angle);
        f1.x = x1;
        f1.y = y1;
        f1.x += center.x;
        f1.x += center.y;

        f2.x -= center.x;
        f2.y -= center.y;
        x1 = f2.x * std::cos(angle) - f2.y * std::sin(angle);
        y1 = f2.x * std::sin(angle) + f2.y * std::cos(angle);
        f2.x = x1;
        f2.y = y1;
        f2.x += center.x;
        f2.x += center.y;
    };

    void reflex(Point center) override {
        this->scale(center, 1.);
    };

    void reflex(Line axis) override {
        std::tuple<double, double, double> coefs = axis.getCoefficients();
        double a = std::get<0>(coefs);
        double b = std::get<1>(coefs);
        double c = std::get<2>(coefs);
        double d;
        double x1, y1;
        d = a * this->f1.y - b * this->f1.x;
        y1 = (b * c - a * d) / (a * a + b * b);
        x1 = (a * y1 - d) / b;
        this->f1.x = 2 * x1 - this->f1.x;
        this->f1.y = 2 * y1 - this->f1.y;

        d = a * this->f2.y - b * this->f2.x;
        y1 = (b * c - a * d) / (a * a + b * b);
        x1 = (a * y1 - d) / b;
        this->f2.x = 2 * x1 - this->f2.x;
        this->f2.y = 2 * y1 - this->f2.y;
    };

    void scale(Point center, double coefficient) override {
        this->f1.x = (this->f1.x - center.x) * coefficient + center.x;
        this->f1.y = (this->f1.y - center.y) * coefficient + center.y;
        this->f2.x = (this->f2.x - center.x) * coefficient + center.x;
        this->f2.y = (this->f2.y - center.y) * coefficient + center.y;
        this->a *= coefficient;
    };
};


class Circle: public Ellipse {
public:
    Circle(Point center, double radius) : Ellipse(center, center, 2 * radius) {};
};


class Polygon: public Shape {
    std::vector<Point> vertices;
public:
    Polygon(std::vector<Point> points) {
        this->vertices = points;
    };

    unsigned verticesCount() const {
        return this->vertices.size();
    };

    std::vector<Point> getVertices() const {
        const std::vector<Point> res(this->vertices);
        return res;
    }

    double perimeter() const override {
        double perim = 0;
        for (unsigned i = 0; i < this->vertices.size(); ++i) {
            perim += pointDistance(this->vertices[i], this->vertices[(i + 1) % this->vertices.size()]);
        }
        return perim;
    }

    double area() const override {
        double a = 0;
        for (int i = 1; i < this->verticesCount() - 1; ++i) {
            a += (1. / 2) * std::abs((this->vertices[i].x - this->vertices[0].x) *
                    (this->vertices[i + 1].y - this->vertices[0].y) -
                    (this->vertices[i + 1].x - this->vertices[0].x) *
                    (this->vertices[i].y - this->vertices[0].y));
        }
        return a;
    }

    bool operator==(const Polygon& another) {
        if (this->vertices.size() != another.vertices.size()) return false;
        unsigned size = another.vertices.size();
        unsigned i = 0;
        while ((i < size) && (this->vertices[0] != another.vertices[i])) {
            ++i;
        }
        for (unsigned j = 0; j < size; ++j) {
            if ((this->vertices[j] != another.vertices[(i + j) % size]) &&
                (this->vertices[j] != another.vertices[(i - j + size) % size])) return false;
        }
        return true;
    };

    bool operator!=(const Polygon& another) {
        if (this->vertices.size() != another.vertices.size()) return true;
        unsigned size = another.vertices.size();
        unsigned i = 0;
        while ((i < size) && (this->vertices[0] != another.vertices[i])) {
            ++i;
        }
        for (unsigned j = 0; j < size; ++j) {
            if ((this->vertices[j] != another.vertices[(i + j) % size]) &&
                (this->vertices[j] != another.vertices[(i - j + size) % size])) return true;
        }
        return false;
    };

    void rotate(Point center, double angle) override {
        double x1, y1;
        for (int i = 0; i < this->verticesCount(); ++i) {
            //coordinate to 0
            vertices[i].x -= center.x;
            vertices[i].y -= center.y;
        }
        for (int i = 0; i < this->verticesCount(); ++i) {
            //rotate
            x1 = vertices[i].x * std::cos(angle) - vertices[i].y * std::sin(angle);
            y1 = vertices[i].x * std::sin(angle) + vertices[i].y * std::cos(angle);
            vertices[i].x = x1;
            vertices[i].y = y1;
        }
        for (int i = 0; i < this->verticesCount(); ++i) {
            //coordinate to previous
            vertices[i].x += center.x;
            vertices[i].x += center.y;
        }
    };

    void scale(Point center, double coefficient) override {
        for (int i = 0; i < this->verticesCount(); ++i) {
            //coordinate to 0
            vertices[i].x -= center.x;
            vertices[i].x -= center.y;
        }
        for (int i = 0; i < this->verticesCount(); ++i) {
            //scale
            vertices[i].x *= coefficient;
            vertices[i].y *= coefficient;
        }
        for (int i = 0; i < this->verticesCount(); ++i) {
            //coordinate to previous
            vertices[i].x += center.x;
            vertices[i].x += center.y;
        }
    };

    void reflex(Point center) override {
        this->scale(center, 1.);
    };

    void reflex(Line axis) override {
        std::tuple<double, double, double> coefs = axis.getCoefficients();
        double a = std::get<0>(coefs);
        double b = std::get<1>(coefs);
        double c = std::get<2>(coefs);
        double d;
        double x1, y1;
        for (unsigned i = 0; i < this->verticesCount(); ++i) {
            d = a * this->vertices[i].y - b * this->vertices[i].x;
            y1 = (b * c - a * d) / (a * a + b * b);
            x1 = (a * y1 - d) / b;
            this->vertices[i].x = 2 * x1 - this->vertices[i].x;
            this->vertices[i].y = 2 * y1 - this->vertices[i].y;
        }
    };
};

class Triangle: public Polygon {
public:
    Triangle(Point& p1, Point& p2, Point& p3) : Polygon({p1, p2, p3}) {};

    Circle circumscribedCircle() {
        auto v = this->getVertices();
        Point a = v[0];
        Point b = v[1];
        Point c = v[2];
        b.x -= a.x;
        b.y -= a.y;
        c.x -= a.x;
        c.y -= a.y;
        double d = 2 * (b.x * c.y - b.y * c.x);
        double ux = (c.y * (b.x * b.x + b.y * b.y) -
                b.y * (c.x * c.x + c.y * c.y)) / d;
        double uy = (b.x * (c.x * c.x + c.y * c.y) -
                    c.x * (b.x * b.x + b.y * b.y)) / d;
        double x = ux + a.x;
        double y = uy + a.y;
        Point center(x, y);
        double r = std::sqrt(ux * ux + uy * uy);
        Circle res(center, r);
        return res;
    };

    Circle inscribedCircle() {
        auto v = this->getVertices();
        double a = pointDistance(v[1], v[2]);
        double b = pointDistance(v[0], v[2]);
        double c = pointDistance(v[0], v[1]);
        double x = (a * v[0].x + b * v[1].x + c * v[2].x) / (a + b + c);
        double y = (a * v[0].y + b * v[1].y + c * v[2].y) / (a + b + c);
        Point center(x, y);
        double s = (a + b + c) / 2;
        double r = std::sqrt((s - a) * (s - b) * (s - c) / s);
        Circle res(center, r);
        return res;
    };

    Point centroid() {
        auto v = this->getVertices();
        Point a = v[0];
        Point b = v[1];
        Point c = v[2];
        double x = (a.x + b.x + c.x) / 3;
        double y = (a.y + b.y + c.y) / 3;
        Point center(x, y);
        return center;
    };

    Point orthocenter() {
        Point o = this->circumscribedCircle().center();
        Point h = o;
        auto v = this->getVertices();
        for (unsigned i = 0; i < 3; ++i) {
            h.x += (v[i].x - o.x);
            h.y += (v[i].y - o.y);
        }
        return h;
    };

    Line EulerLine() {
        Line l(this->orthocenter(), this->centroid());
        return l;
    };

    Circle ninePointsCircle() {
        Point h = this->orthocenter();
        Point o = this->circumscribedCircle().center();
        Point center;
        center.x = (h.x + o.x) / 2;
        center.y = (h.y + o.y) / 2;
        double r = this->circumscribedCircle().radius() / 2;
        Circle res(center, r);
        return res;
    };
};


class Rectangle: public Polygon {
    std::vector<Point> calcPoints(Point p1, Point p3, double k) {
        k = std::max(k, 1 / k);
        double x3 = p3.x - p1.x;
        double y3 = p3.y - p1.y;
        //rotate
        double angle = std::atan(k);
        double x2 = x3 * std::cos(angle) - y3 * std::sin(angle);
        double y2 = x3 * std::sin(angle) + y3 * std::cos(angle);
        x2 /= k * k + 1;
        y2 /= k * k + 1;
        x2 += p1.x;
        y2 += p1.y;
        Point p2(x2, y2);
        Point p4(p3.x + p1.x - x2, p3.y + p1.y - y2);
        std::vector<Point> res = {p1, p2, p3, p4};
        return res;
    };

public:
    Rectangle(Point p1, Point p3, double k) : Polygon(calcPoints(p1, p3, k)) {};

    Point center() {
        auto vertices = this->getVertices();
        Point res((vertices[0].x + vertices[2].x) / 2,
                  (vertices[0].y + vertices[2].y) / 2);
        return res;
    }

    std::pair<Line, Line> diagonals() {
        auto vertices = this->getVertices();
        Line d1 = Line(vertices[0], vertices[2]);
        Line d2 = Line(vertices[1], vertices[3]);
        return std::make_pair(d1, d2);
    }
};


class Square: public Rectangle {
public:
    Square(Point p1, Point p3) : Rectangle(p1, p3, 1) {};

    Circle circumscribedCircle() {
        double r = std::sqrt(2) * this->perimeter() / 4;
        Circle res(this->center(), r);
        return res;
    };

    Circle inscribedCircle() {
        Circle res(this->center(), this->perimeter() / 4);
        return res;
    };
};
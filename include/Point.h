#ifndef POINT_H
#define POINT_H

struct Point {
    double x, y;
    double v, a;
    constexpr Point();
    constexpr Point(double, double, double, double);
};

constexpr Point::Point() : x(0), y(0), v(0), a(0) {}

constexpr Point::Point(const double _x, const double _y, const double _v, const double _a):
    x(_x), y(_y), v(_v), a(_a) {}

inline std::ostream& operator<<(std::ostream &os, const Point &p) {
    os << p.x << "," << p.y << "," << p.v << "," << p.a;
    return os;
}

#endif //POINT_H

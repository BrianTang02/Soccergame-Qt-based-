#ifndef POINT_H
#define POINT_H

struct Point {
    double x, y;
    Point operator+(const Point& t);
    Point operator-(const Point& t);
    Point& operator+=(const Point& t);
    Point& operator-=(const Point& t);
};

#endif // POINT_H

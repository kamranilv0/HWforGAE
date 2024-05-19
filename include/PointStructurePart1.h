#include <iostream>
#include <cmath>
#include <bitset>

enum quadrants{
    FIRST=1,
    SECOND=2,
    THIRD=3,
    FOURTH=4,
    FIFTH=5,
    SIXTH=6,
    SEVENTH=7,
    EIGHTH=8,
    ONLINE=9
};



struct Point {
    private:
        float x;
        float y;
        float z;

    public:
        Point(float x, float y, float z) : x(x), y(y), z(z) {}
        Point() : x(0), y(0), z(0) {}
        void print();
        float zero_distance();
        float distance(Point p1, Point p2);
        float distance(Point p);
        int region();
        bool is_in_same_region(Point p1, Point p2);
        bool is_in_same_region(Point p);

};
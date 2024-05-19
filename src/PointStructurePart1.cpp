#include "PointStructurePart1.h"


void Point::print() {
    std::cout << "Point: (" << x << ", " << y << ", " << z << ")" << std::endl;
}

float Point::zero_distance() {
    return distance(Point(0, 0, 0));
}

float Point::distance(Point p1, Point p2) {
    return (float)sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2) + pow(p1.z - p2.z, 2));
}

float Point::distance(Point p) {
    return distance(*this, p);
}

int Point::region() {
    int f=0;
    f += (z>0) ;
    f += (y>0) << 1;
    f += (x>0) << 2;

    if (x*y*z==0)
    return ONLINE;

    switch (f) {
        case 0:
            return SEVENTH;
        case 1:
            return THIRD;
        case 2:
            return SIXTH;
        case 3:
            return SECOND;
        case 4:
            return EIGHTH;
        case 5:
            return FOURTH;
        case 6:
            return FIFTH;
        case 7:
            return FIRST;
        default:
            return ONLINE;
    }
}

bool Point::is_in_same_region(Point p1, Point p2) {
    return (p1.region()==p2.region());
}
bool Point::is_in_same_region(Point p){
    return is_in_same_region( *this , p);
}
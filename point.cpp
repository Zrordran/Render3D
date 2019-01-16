
#include "tgaimage.h"
#include "point.h"


Point::Point(int tx, int ty, int tz){
    x = tx;
    y = ty;
    z = tz;
}

Point::~Point() {
}

int Point::getX(){
    return x;
}

int Point::getY(){
    return y;
}

int Point::getZ(){
    return z;
}
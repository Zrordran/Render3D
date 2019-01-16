
#include "tgaimage.h"
#include "point.h"


Point::Point(int tx, int ty){
    x = tx;
    y = ty;
}

Point::~Point() {
}

int Point::getX(){
    return x;
}

int Point::getY(){
    return y;
}
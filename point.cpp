
#include "tgaimage.h"
#include "point.h"


Point::Point(float tx, float ty, float tz){
    x = tx;
    y = ty;
    z = tz;
}

Point::~Point() {
}

Point* Point::toRatio(int w, int h) {
	Point* p = new Point((int)(x*w / 2 + w / 2), (int)(y*h / 2 + h / 2), z);
	return p;
}

float Point::getX(){
    return x;
}

float Point::getY(){
    return y;
}

float Point::getZ(){
    return z;
}

point::point()
{
}


point::~point()
{
}

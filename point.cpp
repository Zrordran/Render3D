
#include "tgaimage.h"
#include "point.h"


Point::Point(double tx, double ty, double tz){
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

double Point::getX(){
    return x;
}

double Point::getY(){
    return y;
}

double Point::getZ(){
    return z;
}

point::point()
{
}


point::~point()
{
}

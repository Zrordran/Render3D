/* 
 * File:   Point.h
 * Author: marbach5u
 *
 * Created on 16 janvier 2019, 08:19
 */

#ifndef POINT_H
#define	POINT_H

class Point {
private:
	double x;
	double y;
	double z;
public:
	Point(double tx, double ty, double tz);
	~Point();
	double getX();
	double getY();
	double getZ();
	Point* toRatio(int w, int h);
};

#endif	/* POINT_H */

 class point
 {
 public:
	 point();
	 ~point();
 };


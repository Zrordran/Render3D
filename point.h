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
	float x;
	float y;
	float z;
public:
	Point(float tx, float ty, float tz);
	~Point();
	float getX();
	float getY();
	float getZ();
	Point* toRatio(int w, int h);
};

#endif	/* POINT_H */

 class point
 {
 public:
	 point();
	 ~point();
 };


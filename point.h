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
        int x;
	int y;
public:
	Point(int tx, int ty);
	~Point();
	int getX();
	int getY();
};

#endif	/* POINT_H */


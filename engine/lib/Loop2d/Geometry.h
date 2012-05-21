#ifndef __GEOMETRY_H__
#define __GEOMETRY_H__

#include "CCGeometry.h"


class Point : public cocos2d::CCPoint
{
public:
	
	Point();
	Point(float x, float y);
	
public:
	static bool PointEqualToPoint(const Point& point1, const Point& point2);
};




class Rect : public cocos2d::CCRect
{
public:
	
	Rect();
	Rect(float x, float y, float width, float height);
};

#endif // __GEOMETRY_H__

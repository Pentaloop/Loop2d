/*
 *  Geometry.cpp
 *  test
 *
 *  Created by Haseeb Yousaf on 1/8/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Geometry.h"

Point::Point(void)
{
	x = 0;
	y = 0;
}

Point::Point(float x, float y)
{
	this->x = x;
	this->y = y;
}

bool Point::PointEqualToPoint(const Point& point1, const Point& point2)
{
	return ((point1.x == point2.x) && (point1.y == point2.y));
}

// implementation of CCRect

Rect::Rect(void)
{
	origin.x = 0;
	origin.y = 0;
	
	size.width = 0;
	size.height = 0;
}

Rect::Rect(float x, float y, float width, float height)
{
	// Only support that, the width and height > 0
	CC_ASSERT(width >= 0 && height >= 0);
	
	origin.x = x;
	origin.y = y;
	
	size.width = width;
	size.height = height;
}

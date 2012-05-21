/*
 *  Util.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 2/29/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include <sstream>
using namespace std; 

#ifndef __UTIL_H__
#define __UTIL_H__

using namespace cocos2d;

typedef enum
{
	CCScaleFitFull,
	CCScaleFitAspectFit,
	CCScaleFitAspectFill,
} CCScaleFit;

class Util 
{
public:
	static void spriteScaleToSize(CCSprite* sprite, CCSize size, CCScaleFit fitType);
	
	template <class T>
	static string toString( T argument)
	{
		/**************************************/
		/* This template shows the power of   */
		/* C++ templates. This function will  */
		/* convert anything to a string!      */
		/* Precondition:                      */
		/* operator<< is defined for type T    */
		/**************************************/
		string r;
		stringstream s;
		s << argument;
		r = s.str();
		return r;
	}
};





#endif
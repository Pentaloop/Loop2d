/*
 *  Screen.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 1/26/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "scene.h"

#ifndef __SCREEN_H__
#define __SCREEN_H__

using namespace cocos2d;

class Screen {
public:
	static CCPoint getCenterPoint();
	static CCSize getSize();
	/*
	CCPoint getTopLeft();
	CCPoint getTopRight();
	CCPoint getMiddleLeft();
	CCPoint getMiddleRight();
	CCPoint get();
	CCPoint getMiddleRight();
	 */
};

#endif
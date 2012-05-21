/*
 *  Screen.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 1/26/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Screen.h"

CCPoint Screen::getCenterPoint() 
{
	CCLog("test");
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	return CCPoint(screenSize.width / 2.0f, screenSize.height / 2.0f);
}


CCSize Screen::getSize() 
{
	CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
	return screenSize;
}
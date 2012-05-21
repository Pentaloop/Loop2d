/*
 *  Action.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 1/27/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "scene.h"

#ifndef __ACTION_H__
#define __ACTION_H__

using namespace cocos2d;

class Action {
public:
	static cocos2d::CCFadeTo* fadeTo(float duration, float opacity);
	static cocos2d::CCFadeIn* fadeIn(float duration);
	static cocos2d::CCFadeOut* fadeOut(float duration);
	
	static cocos2d::CCScaleTo* scaleTo(float duration, float scale);
	
	
	static cocos2d::CCAnimate* frameAnimation(float delay, int frameCount, string frames[]);
	
	static cocos2d::CCActionInterval* repeatAction(CCActionInterval* action, int repeatCount);
	
	
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
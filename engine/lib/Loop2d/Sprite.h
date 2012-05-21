/*
 *  sprite.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/3/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#import "Geometry.h"

#ifndef __SPRITE_H__
#define __SPRITE_H__

using namespace cocos2d;

class Sprite : public CCSprite {
public:
	static Sprite* spriteWithFile(const char *pszFileName);
	static Sprite* spriteWithFrame(const char *frameName);
	
	float getX();
	void setX(float newVal);
	float getY();
	void setY(float newVal);

	float getWidth();
	void setWidth(float newVal);
	float getHeight();
	void setHeight(float newVal);

	// Sprite Sheet
	static void loadSheet(string plistFilename);
	static void loadSheet(string plistFilename, string imageFilename);
};

#endif
/*
 *  Transition.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/9/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */


#include "cocos2d.h"
#import "Geometry.h"
#import "Sprite.h"

#ifndef __SPRITE_H__
#define __SPRITE_H__

using namespace cocos2d;

class Transition : public CCSprite {
public:
	static Sprite* spriteWithFile(const char *pszFileName);
};

#endif
/*
 *  Label.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/2/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "Sprite.h"

#ifndef __LABEL_H__
#define __LABEL_H__

using namespace cocos2d;

class Label : public Sprite {
private:
	bool isBitmapFontLabel;
public:
	static Label* newLabel(string text, float x, float y, string fontName = "");	
};

#endif
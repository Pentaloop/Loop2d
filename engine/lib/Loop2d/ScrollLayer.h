/*
 *  ScrollLayer.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/1/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */


#include "cocos2d.h"
#include "CCScrollLayer.h"
#include "Layer.h"

using namespace cocos2d;

#ifndef __SCROLL_LAYER_H__
#define __SCROLL_LAYER_H__

using namespace cocos2d;

class ScrollLayer : public CCScrollLayer {
public:
	static ScrollLayer* newLayer();
	void addPage(Layer* layer);
};

#endif
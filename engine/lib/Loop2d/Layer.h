/*
 *  Layer.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/1/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"

using namespace cocos2d;

#ifndef __LAYER_H__
#define __LAYER_H__

using namespace cocos2d;

class Layer : protected CCLayer {
public:
	static Layer* newLayer();
};

#endif
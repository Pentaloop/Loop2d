/*
 *  Layer.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/1/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Layer.h"

Layer* Layer::newLayer()
{
	Layer *layer = new Layer();
	layer->autorelease();
	return layer;
}
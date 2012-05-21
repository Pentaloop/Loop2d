/*
 *  ScrollLayer.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/1/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "ScrollLayer.h"

ScrollLayer* ScrollLayer::newLayer()
{
	ScrollLayer *layer = new ScrollLayer();
	layer->autorelease();
	layer->initWithLayers(CCArray::arrayWithCapacity(1), 0);
	return layer;
}


void ScrollLayer::addPage(Layer* layer)
{
	CCScrollLayer::addPage(layer);
}
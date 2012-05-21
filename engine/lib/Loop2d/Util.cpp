/*
 *  Util.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 2/29/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Util.h"

void Util::spriteScaleToSize(CCSprite* sprite, CCSize size, CCScaleFit fitType)
{
	CCSize targetSize = size;
	CCSize mySize = sprite->getContentSize();
	
	float targetAspect = targetSize.width/targetSize.height;
	float myAspect = mySize.width/mySize.height;
	
	float xScale = sprite->getScaleX();
	float yScale = sprite->getScaleY();
	
	switch (fitType)
	{
		case CCScaleFitFull:
			xScale = targetSize.width/mySize.width;
			yScale = targetSize.height/mySize.height;
			break;
			
		case CCScaleFitAspectFit:
			if(targetAspect > myAspect)
			{
				xScale = yScale = targetSize.height/mySize.height;
			}
			else
			{
				yScale = xScale = targetSize.width/mySize.width;
			}
			break;
			
		case CCScaleFitAspectFill:
			
			if(targetAspect > myAspect)
			{
				xScale = yScale = targetSize.width/mySize.width;
			}
			else
			{
				yScale = xScale = targetSize.height/mySize.height;
			}
			break;
			
		default:
			break;
	}
	
	sprite->setScaleX(xScale);
	sprite->setScaleX(yScale);
}
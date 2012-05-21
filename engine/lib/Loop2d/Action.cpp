/*
 *  Action.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 1/27/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Action.h"


CCFadeTo* Action::fadeTo(float duration, float opacity) 
{
	CCLog("Action::fadeTo: duriation:%f opacity:%f", duration, opacity);
	return CCFadeTo::actionWithDuration(duration, opacity * 100);
}

CCFadeIn* Action::fadeIn(float duration) 
{
	return CCFadeIn::actionWithDuration(duration);
}

CCFadeOut* Action::fadeOut(float duration)
{
	return CCFadeOut::actionWithDuration(duration);
}

CCScaleTo* Action::scaleTo(float duration, float scale) 
{
	CCLog("Action::scaleTo: duriation:%f scale:%f", duration, scale);
	return CCScaleTo::actionWithDuration(duration,scale);
}


cocos2d::CCAnimate* Action::frameAnimation(float delay, int frameCount, string frames[])
{
	CCAnimation* animation = CCAnimation::animation();
	for (int x = 0; x < frameCount; x++) 
	{
		CCSpriteFrame* frame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(frames[x].c_str());
		if (frame == NULL) 
		{
			CCLog("Could not add frame %s", frames[x].c_str());
			return NULL;
		}
		animation->addFrame(frame);
	}
	animation->setDelay(delay);
	CCAnimate* action = CCAnimate::actionWithAnimation(animation, false);
	return action;
}


cocos2d::CCActionInterval* Action::repeatAction(CCActionInterval* repeatAction, int repeatCount)
{
	if (repeatCount < 0) {
		return CCRepeatForever::actionWithAction(repeatAction);
	} else {
		return CCRepeat::actionWithAction(repeatAction, repeatCount);
	}
}

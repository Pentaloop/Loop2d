/*
 *  director.cpp
 *  test
 *
 *  Created by Haseeb Yousaf on 1/4/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Director.h"
#include "CCStdC.h"
#include <cctype>

using namespace std;

void Director::showScene(Scene* aScene, std::string transition, float duration) {
	//CCLog("Director::showScene: START");
	CCScene* transitionType = NULL; 
	if (!transition.empty()) {
		string lowerCaseTrans(transition);
		std::transform(lowerCaseTrans.begin(), lowerCaseTrans.end(), lowerCaseTrans.begin(), std::tolower);
		if (lowerCaseTrans.compare("fadein") == 0) {
			transitionType = CCTransitionFade::transitionWithDuration(duration, aScene, ccBLACK);
		}
	} else {
		transitionType = aScene;
	}

	
	if (CCDirector::sharedDirector()->getRunningScene()) {
		CCDirector::sharedDirector()->replaceScene(transitionType);
	} else {
		CCDirector::sharedDirector()->runWithScene(transitionType);
	}
	//CCLog("Director::showScene: END");
}

void Director::clearMemoryCache() 
{	
	CCDirector::sharedDirector()->purgeCachedData();
	CCSpriteFrameCache::sharedSpriteFrameCache()->removeUnusedSpriteFrames();
}
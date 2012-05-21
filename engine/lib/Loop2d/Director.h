/*
 *  director.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/4/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "scene.h"

#ifndef __DIRECTOR_H__
#define __DIRECTOR_H__

using namespace cocos2d;

class Scene;

class Director {
public:
	static void showScene(Scene* aScene, string transition="", float duration=0);
	
	static void clearMemoryCache();
};

#endif
/*
 *  Log.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/4/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "scene.h"

#ifndef __LOG_H__
#define __LOG_H__

using namespace cocos2d;


class Log {
public:
	static void write(const char * pszFormat, ...);
};

#endif
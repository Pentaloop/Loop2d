/*
 *  LPScheduler.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/19/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#ifndef __LP_SCHEDULAR_H__
#define __LP_SCHEDULAR_H__


#include "cocos2d.h"
#include "Callback1.h"

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "luajit.h"
#include "lauxlib.h"
#include "tolua++.h"
}

using namespace cocos2d;


// Hash Element used for "selectors with interval"
typedef struct _hashSelectorEntry
{
	ccArray          	        *timers;
	
	unsigned int				timerIndex;
	CCTimer						*currentTimer;
	bool						currentTimerSalvaged;
	bool						paused;
	UT_hash_handle				hh;
} tHashSelectorEntry;

// Hash Element used for "script functions with interval"
typedef struct _hashScriptFuncEntry
{
	CCTimer *timer;
	SelectorProtocol *target;
	bool paused;
	const char *funcName;
	UT_hash_handle hh;
} tHashScriptFuncEntry;


class LPScheduler {
private:
	
public:
	static LPScheduler* sharedScheduler(void);
	void scheduleSelector(LuaCall<int,int>* pfnCallback, SelectorProtocol *pTarget, float fInterval, bool bPaused);
	/*void scheduleScriptFunc(const char *pszFuncName, ccTime fInterval, bool bPaused)*/
};
#endif
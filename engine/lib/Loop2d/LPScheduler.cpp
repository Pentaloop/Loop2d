/*
 *  LPScheduler.cpp
 *  test
 *
 *  Created by Haseeb Yousaf on 1/19/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "LPScheduler.h"

static LPScheduler *pSharedScheduler;

LPScheduler* LPScheduler::sharedScheduler(void)
{
	if (! pSharedScheduler)
	{
		pSharedScheduler = new LPScheduler();
		//pSharedScheduler->init();
	}
	
	return pSharedScheduler;
}



void LPScheduler::scheduleSelector(LuaCall<int,int>* pfnCallback, SelectorProtocol *pTarget, float fInterval, bool bPaused)
{
			
}

/*
void CCScheduler::scheduleScriptFunc(const char *pszFuncName, ccTime fInterval, bool bPaused)
{
	//CCAssert(pfnSelector);
	CCAssert(pszFuncName, "");
	
	tHashScriptFuncEntry *pElement = NULL;
	HASH_FIND_INT(m_pHashForScriptFunctions, &pszFuncName, pElement);
	
	if (! pElement)
	{
		pElement = (tHashScriptFuncEntry *)calloc(sizeof(*pElement), 1);
		pElement->funcName = pszFuncName;
		pElement->timer = new CCTimer();
		pElement->timer->initWithScriptFuncName(pszFuncName, fInterval);
		pElement->paused = bPaused;
		
		HASH_ADD_INT(m_pHashForScriptFunctions, funcName, pElement);		
	}
	else
	{
		CCAssert(pElement->paused == bPaused, "");
	}	
}*/
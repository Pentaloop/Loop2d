/*
 *  Log.cpp
 *  test
 *
 *  Created by Haseeb Yousaf on 1/4/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Log.h"

void Log::write(const char * pszFormat, ...) {
	printf("Loop2d: ");
    char szBuf[kMaxLogLen];
    
    va_list ap;
    va_start(ap, pszFormat);
    vsprintf(szBuf, pszFormat, ap);
    va_end(ap);
    printf("%s", szBuf);
    printf("\n");
}
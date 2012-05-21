//
//  PLLua.h
//  Loop2d
//
//  Created by Pl-5 on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "cocos2d.h"

#ifndef Loop2d_PLLua_h
#define Loop2d_PLLua_h
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "luajit.h"
#include "lauxlib.h"
#include "tolua++.h"
}

#define PLFuncRef int


class PLLua {
public:
    static float getFloatForKey(lua_State* L, const char *key, float defaultValue);
    static void* getUserTypeForKey(lua_State* L, const char *type, const char *key);
    static int getFunctionForKey(lua_State* L, const char *key);
    static void stackDump(lua_State* l);
    
};


#endif

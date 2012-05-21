//
//  PLLua.cpp
//  Loop2d
//
//  Created by Pl-5 on 5/11/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#include "PLLua.h"

void PrintTable(lua_State *L, int tabCount = 0);

float PLLua::getFloatForKey(lua_State* L, const char *key, float defaultValue) {
    float result = defaultValue;
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    if (lua_isnumber(L, -1)) {
        result = (float)lua_tonumber(L, -1);
    } else {
        CCLOGERROR("Invalid type or not found");
    }
    lua_pop(L, 1);    
    return result;
}


void* PLLua::getUserTypeForKey(lua_State* L, const char *type, const char *key) {
    void* result = NULL;
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    tolua_Error tolua_err;
    if (tolua_isusertype(L,-1,type,0,&tolua_err)) {       
        result = (void*)tolua_tousertype(L, -1,0);
    } else {
        CCLOGERROR("Invalid type or not found");
    }        
    lua_pop(L, 1);    
    return result;
}


PLFuncRef PLLua::getFunctionForKey(lua_State* L, const char *key) {
    PLFuncRef result = NULL;
    printf("%s\n",key);
    lua_pushstring(L, key);
    lua_gettable(L, -2);
    if (!lua_isnil(L, -1) && lua_isfunction(L,-1)) {       
        result = luaL_ref(L ,LUA_REGISTRYINDEX);
    } else {
        CCLOGERROR("Invalid type or not found");
        lua_pop(L, 1);    
    } 
    return result;
}

void PLLua::stackDump(lua_State* l)
{
    PrintTable(l);
}


void PrintTable(lua_State *L, int tabCount)
{
    lua_pushnil(L);
    printf("{\n");
    while(lua_next(L, -2) != 0)
    {
        for (int c = 0; c < tabCount; c++) {
            printf("\t");
        }
        if(lua_isstring(L, -1))
            printf("\t%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_isnumber(L, -1))
            printf("\t%s = %d\n", lua_tostring(L, -2), lua_tonumber(L, -1));
        //else if(lua_isfunction(L, -1))
        //    printf("\t%s = %s\n", lua_tostring(L, -2), lua_tostring(L, -1));
        else if(lua_istable(L, -1)) {
            printf("\t%s = ", lua_tostring(L, -2));
            PrintTable(L,tabCount+1);
        }
        else {
            int t = lua_type(L, -1);
            //printf("\t%s = %s\n", lua_tostring(L, -2), lua_typename(L, t));
            char* type = (char*)tolua_typename(L, -1);
            lua_pop(L, 1);
            printf("\t%s = %s\n", lua_tostring(L, -2), type);
            
        }
        lua_pop(L, 1);
    }
    printf("}\n");
}

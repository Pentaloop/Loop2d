/*
 *  scene.h
 *  test
 *
 *  Created by Haseeb Yousaf on 1/4/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "Callback1.h"

#ifndef __SCENE_H__
#define __SCENE_H__

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "luajit.h"
#include "lauxlib.h"
#include "tolua++.h"
}

using namespace cocos2d;

class Scene : public CCScene {
private:
	LuaCall<int>* onEnterCallback;
	LuaCall<int>* onTransitionCompleteCallback;
	LuaCall<int>* onExitCallback;
public:
	
	
	static Scene* newScene();
	
	void schedule(lua_State* L, lua_Object obj);
	void schedule(lua_State* L, lua_Object obj, float delay);
	void schedule(LuaCall<int, int>* callback, ccTime interval);
	

	void onEnter();
	void onEnter(lua_State* L);
	
	void onExit();
	void onExit(lua_State* L);
	
	void onEnterTransitionDidFinish();
	void onEnterTransitionComplete(lua_State* L);
};
#endif
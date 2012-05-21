/*
 *  scene.cpp
 *  test
 *
 *  Created by Haseeb Yousaf on 1/4/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "luajit.h"
#include "lauxlib.h"
#include "tolua++.h"
}

#include "Scene.h"
#include "Callback1.h"
//#include "LPScheduler.h"

Scene* Scene::newScene() {
	Scene *scene = new Scene();
	scene->autorelease();
	scene->onEnterCallback = NULL;
	scene->onTransitionCompleteCallback = NULL;
	scene->onExitCallback = NULL;
	return scene;
}


void Scene::schedule(lua_State* L, lua_Object obj) {
	this->schedule(L, obj, 0.0f);
}


void Scene::schedule(lua_State* L, lua_Object obj, float delay) {
	if (L != NULL) {
		if (lua_isfunction(L, -1)) {
			LuaCall<int, int> callback = LuaCall<int, int>(L, "");
			this->schedule(&callback,0);
			
		} 		
	}	
}


void Scene::schedule(LuaCall<int, int>* callback, ccTime interval) {
	CCAssert( callback, "Argument must be non-nil");
	CCAssert( interval >=0, "Argument must be positive");
	
	//LPScheduler::sharedScheduler()->scheduleCallback(callback, this, interval, !m_bIsRunning);
}

// ===============================================================
#pragma mark Events
// ===============================================================
void Scene::onEnter() {
	CCScene::onEnter();
	if (onEnterCallback) {
		onEnterCallback->call();
	}
}


void Scene::onEnter(lua_State* func) 
{
	if (onEnterCallback) {
		delete onEnterCallback;
		onEnterCallback = NULL;
	}
	if (func) {
		onEnterCallback = new LuaCall<int>((lua_State*)func, "");
	}
}

void Scene::onExit() 
{
	CCScene::onExit();
	if (onEnterCallback) {
		onEnterCallback->call();
	}
}


void Scene::onExit(lua_State* func) 
{
	if (onExitCallback) {
		delete onExitCallback;
		onExitCallback = NULL;
	}
	if (func) {
		onExitCallback = new LuaCall<int>((lua_State*)func, "");
	}
}

void Scene::onEnterTransitionDidFinish() 
{
	CCScene::onEnterTransitionDidFinish();
	if (onTransitionCompleteCallback) {
		onTransitionCompleteCallback->call();
	}
}


void Scene::onEnterTransitionComplete(lua_State* func) 
{
	
	if (onTransitionCompleteCallback) {
		delete onTransitionCompleteCallback;
		onTransitionCompleteCallback = NULL;
	}
	if (func) {
		onTransitionCompleteCallback = new LuaCall<int>((lua_State*)func, "");
	}
}



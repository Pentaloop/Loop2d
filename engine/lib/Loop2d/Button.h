/*
 *  Button.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 2/29/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"
#include "Geometry.h"
#include "Callback1.h"
#include "Util.h"
#include "Sprite.h"
#include "Event.h"
#include "PLLua.h"

#ifndef __BUTTON_H__
#define __BUTTON_H__
extern "C"
{
#include "lua.h"
#include "lualib.h"
#include "luajit.h"
#include "lauxlib.h"
#include "tolua++.h"
}



using namespace cocos2d;

typedef enum _CCButtonEvent {
	CCButtonEventTouchDownInside,
	CCButtonEventTouchUpInside,
	CCButtonEventTouchesCanceled
} CCButtonEvent;

typedef enum _CCButtonState {
	CCButtonStateNormal,
	CCButtonStateHighlighted,
	CCButtonStateDisabled
} CCButtonState;


class Button : public Sprite, CCTouchDelegate {
private:
	LuaCall<int, Event*>* onPressCallback;
	LuaCall<int, Event*>* onReleaseCallback;
	LuaCall<int, Event*>* onCancelCallback;
	CCButtonState currentState;
	CCDictionary<std::string, CCObject*> *buttonSprites;
	
	void setButtonState(CCButtonState state);
	CCSprite* spriteForState(CCButtonState state);
	
	void loadDefaults(); 
	void updateGUI();
	void sizeToFit();
	
	bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchMoved(CCTouch* touch, CCEvent* event);
	void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
	void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
	
	bool enabled;
public:
    
    static Button* newButton(lua_State* L);
	static Button* buttonWithFrame(Rect frame);
	static Button* buttonWithFrame(float frame[4]);
	static Button* buttonAtPoint(Point point);
	static Button* buttonAtPoint(float point[2]);
	
	void onPress(lua_State* L);	
	void onRelease(lua_State* L);
	void onCancel(lua_State* L);
	
	bool getEnabled();
	void setEnabled(bool newValue);
	
	void setContentSize(CCSize newSize);
	
	void setImage(CCSprite* sprite, string state);
	
	~Button();
};

#endif
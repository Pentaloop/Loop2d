/*
 *  Button.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 2/29/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Button.h"

#define kCurrentSpriteTag 0x0101

bool Button::getEnabled()
{
	return enabled;
}


void Button::setEnabled(bool newValue) 
{
	if (newValue && newValue != enabled) 
	{
		CCTouchDispatcher::sharedDispatcher()->addTargetedDelegate(this, 1, true);
	}
	else
	{
		CCTouchDispatcher::sharedDispatcher()->removeDelegate(this);
	}
	enabled = newValue;
}

void Button::setContentSize(CCSize newSize) 
{
	CCSprite::setContentSize(newSize);
	this->updateGUI();
}


// ===============================================================
// Creation
// ===============================================================
Button* Button::buttonWithFrame(float frame[4])
{
	return buttonWithFrame(Rect(frame[0], frame[1], frame[2], frame[3]));
}


Button* Button::buttonWithFrame(Rect frame)
{
	Button *btn = new Button();
	if (btn->init())
	{
		btn->autorelease();
		btn->loadDefaults();
		btn->setContentSize(CCSize(frame.size.width, frame.size.height));
		btn->setPosition(CCPoint(frame.origin.x + frame.size.width / 2, frame.origin.y + frame.size.height / 2));
	} 
	else 
	{
        delete btn;
		btn = NULL;
	}			
	return btn;
}


Button* Button::buttonAtPoint(float point[2])
{
	return buttonAtPoint(Point(point[0], point[1]));
}


Button* Button::buttonAtPoint(Point point)
{
	Button *btn = new Button();
	if (btn->init())
	{
		btn->autorelease();
		btn->setContentSize(CCSize(0, 0));
		btn->setPosition(CCPoint(point.x, point.y));
		btn->loadDefaults();
	} 
	else 
	{
        delete btn;
		btn = NULL;
	}			
	return btn;
}


//**************************************************************
Button* Button::newButton(lua_State* L) {
    float x = 0.0f;
    float y = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
    CCSprite* normal = NULL;
    CCSprite* pressed = NULL;
    PLFuncRef onPress = NULL;
    PLFuncRef onRelease = NULL;
    PLFuncRef onCancel = NULL;
    
    // Get all the parameters
    if (L) {
        if (lua_istable(L, -1)) {
            printf("here\n");
            //int t = lua_gettop(L);
            PLLua::stackDump(L);
            x = PLLua::getFloatForKey(L,"x",0);
            y = PLLua::getFloatForKey(L,"y",0);
            width = PLLua::getFloatForKey(L,"width",-1);
            height = PLLua::getFloatForKey(L,"height",-1);
            normal = (Sprite*)PLLua::getUserTypeForKey(L, "Sprite", "normal");
            pressed = (Sprite*)PLLua::getUserTypeForKey(L, "Sprite", "pressed");
            onPress = PLLua::getFunctionForKey(L, "onPress");
            onRelease = PLLua::getFunctionForKey(L, "onRelease");
            onCancel = PLLua::getFunctionForKey(L, "onCancel");
             /*
            lua_pushnil(L);
            while (lua_next(L, t) != 0) {
                printf("%s - %s\n",
                       lua_typename(L, lua_type(L, -2)),
                       lua_typename(L, lua_type(L, -1)));
                lua_pop(L, 1);
            }
             */
            
        }
    } else {
        // No parameters provided
    }
    // Now create the button    
    Button* button = Button::buttonAtPoint(Point(x, y));
    if (width >= 0 && height >= 0) {
        button->setContentSize(CCSize(width, height));
    }
    if (normal) {
        button->setImage(normal, string("normal"));
    }
    if (pressed) {
        button->setImage(pressed, string("pressed"));
    }
    if (onPress) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, onPress);
        button->onPress(L);
    }
    if (onRelease) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, onRelease);
        button->onRelease(L);
    }
    if (onCancel) {
        lua_rawgeti(L, LUA_REGISTRYINDEX, onCancel);
        button->onCancel(L);
    }
    return button;
}



//**************************************************************
void Button::loadDefaults() 
{
	this->buttonSprites = NULL;
	this->onPressCallback = NULL;
	this->onReleaseCallback = NULL;
	this->onCancelCallback = NULL;
	//this->setColor(ccRED);
	this->setButtonState(CCButtonStateNormal);
	// Update gui
	this->updateGUI();
	this->setEnabled(true);
}

//=========================================================================
#pragma mark -
#pragma mark Button state management methods
//=========================================================================
//**************************************************************
void Button::updateGUI() {
	CCSize buttonFrame = this->getContentSize();
	CCPoint buttonCenter = CCPoint(buttonFrame.width / 2, buttonFrame.height / 2);
		
	//this->setTextureRect(CCRectMake(this->getPosition().x - buttonFrame.width / 2.0, this->getPosition().y - buttonFrame.height / 2.0, buttonFrame.width, buttonFrame.height));
	CCSprite* currentSprite = (CCSprite*)this->getChildByTag(kCurrentSpriteTag);
	if (currentSprite) {
		Util::spriteScaleToSize(currentSprite, buttonFrame, CCScaleFitAspectFill);
		currentSprite->setPosition(buttonCenter);
	}
}


//**************************************************************
void Button::setButtonState(CCButtonState state) 
{
	currentState = state;
	//Log(@"button state: %d tag:%d",state,self.tag);
	CCSprite* newSprite = NULL;
	switch (state) {
		case CCButtonStateNormal: {
			newSprite = this->spriteForState(CCButtonStateNormal);
		}
			break;
		case CCButtonStateHighlighted: {
			newSprite = this->spriteForState(CCButtonStateHighlighted);
			if (!newSprite) {
				newSprite = this->spriteForState(CCButtonStateNormal);
			}
		}
			break;
		case CCButtonStateDisabled: {
			newSprite = this->spriteForState(CCButtonStateDisabled);
			if (!newSprite) {
				newSprite = this->spriteForState(CCButtonStateNormal);
			}
		}
			break;
		default:
			break;
	}
	// Change the sprite
	CCSprite* currentSprite = (CCSprite*)this->getChildByTag(kCurrentSpriteTag);
	if(newSprite != currentSprite) {
		if (currentSprite) {
			this->removeChild(currentSprite, true);
		}
		if(newSprite) {
			this->addChild(newSprite, 0, kCurrentSpriteTag);
			CCPoint pos = CCPoint(this->getContentSize().width / 2, this->getContentSize().height / 2);
			//CCLog("%f %f",pos.x, pos.y);
			newSprite->setPosition(pos);
			this->sizeToFit();
		}	
	}
	// Update GUI
	this->updateGUI();
}


void Button::setImage(CCSprite* sprite, string state) 
{
	if(!buttonSprites) {
		buttonSprites = new CCDictionary<std::string, CCObject*>();
	}
	CCButtonState st = CCButtonStateNormal;
	if (state == "pressed") {
		st = CCButtonStateHighlighted;
	} else if (state == "disabled") {
		st = CCButtonStateDisabled;
	}

	if (sprite != NULL) {
		buttonSprites->setObject(sprite, Util::toString((int)st));
	}
	this->setButtonState(currentState);
}


CCSprite* Button::spriteForState(CCButtonState state)
{
	CCSprite* result = NULL;
	if(buttonSprites) {
		result = (CCSprite*)buttonSprites->objectForKey(Util::toString((int)state));
	}
	return result;
}


void Button::sizeToFit() 
{
	CCSprite* currentSprite = (CCSprite*)this->getChildByTag(kCurrentSpriteTag);
	if (currentSprite) {
		CCSize spriteSize = currentSprite->getContentSize();
		this->setContentSize(spriteSize);
		//Util::spriteScaleToSize(currentSprite, spriteSize, CCScaleFitAspectFill);
		//[currentSprite scaleToSize:buttonFrame fitType:CCScaleFitAspectFill];
	}
}


// ===============================================================
// Touches
// ===============================================================
//*************************************************************************
bool Button::ccTouchBegan(CCTouch *touch, CCEvent *pEvent)
{
	CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->locationInView(touch->view()));
	//Log(@"x:%f  y:%f tag:%d, position:%f %f",location.x,location.y,self.tag,self.position.x, self.position.y);
	//Do a fast rect check before doing a circle hit check:
	CCRect buttonFrame = this->boundingBox();
	CCPoint touchPoint = this->convertTouchToNodeSpace(touch);
	//CCLog("{%f %f %f %f} (%f %f) %d", buttonFrame.origin.x, buttonFrame.origin.y, buttonFrame.size.width, buttonFrame.size.height,touchPoint.x,touchPoint.y, this->getTag());
	//	CGPoint pt =  [self convertToWorldSpace:mk];
	//CGRect rect = CGRectMake(pt.x, pt.y, [currentSprite boundingBox].size.width, [currentSprite boundingBox].size.height);
	//DDLogVerbose(@"rect:%@ point:%@ tag:%d res:%d",[NSValue valueWithCGRect:buttonFrame],[NSValue valueWithCGPoint:location],self.tag,CGRectContainsPoint(buttonFrame, location));
	buttonFrame.origin.x =0;
	buttonFrame.origin.y =0;
	if(!CCRect::CCRectContainsPoint(buttonFrame, touchPoint)){
		return false;
	} else {
		// **** Button is touched ***
		// Change button state
		this->setButtonState(CCButtonStateHighlighted);
		// Call selector
		//DDLogVerbose(@"ButtonDown");
		if (onPressCallback) {
			Event* ent = new Event();
			ent->autorelease();
			ent->addObject("item", (void*)this, "Button");
			onPressCallback->call(ent);
		}
		return true;
	}	
	return false;
}


void Button::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	
	CCPoint location = CCDirector::sharedDirector()->convertToGL(touch->locationInView(touch->view()));
	//Log(@"x:%f  y:%f %d",location.x,location.y,CGRectContainsPoint(frame, location));
	//Do a fast rect check before doing a circle hit check:
	CCSprite* currentSprite = (CCSprite*)this->getChildByTag(kCurrentSpriteTag);
	if(currentSprite) {
		CCPoint mk = currentSprite->boundingBox().origin;
		CCPoint pt =  this->convertToWorldSpace(mk);
		CCRect rect = CCRect(pt.x, pt.y, currentSprite->boundingBox().size.width, currentSprite->boundingBox().size.height);
		if(!CCRect::CCRectContainsPoint(rect, location)){
			this->setButtonState(CCButtonStateHighlighted);
		} else {
			// **** Button is untouched ***
			// Change button state
			this->setButtonState(CCButtonStateNormal);
		}
	}	
}


void Button::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
	// **** Button is touched ***
	// Change button state
	this->setButtonState(CCButtonStateNormal);
	// Call selector
	//DDLogVerbose(@"ButtonUp");
	if (onReleaseCallback) {
		Event* ent = new Event();
		ent->autorelease();
		ent->addObject("item", (void*)this, "Button");
		onReleaseCallback->call(ent);
	}
}


void Button::ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent)
{
	this->setButtonState(CCButtonStateNormal);
	if (onCancelCallback) {
		Event* ent = new Event();
		ent->autorelease();
		ent->addObject("item", (void*)this, "Button");
		onCancelCallback->call(ent);
	}
}


// ===============================================================
// Events
// ===============================================================
void Button::onPress(lua_State* func) 
{
	if (onPressCallback) {
		delete onPressCallback;
		onPressCallback = NULL;
	}
	if (func) {
		onPressCallback = new LuaCall<int, Event*>((lua_State*)func, "");
	}
}

void Button::onRelease(lua_State* func) 
{
	if (onReleaseCallback) {
		delete onReleaseCallback;
		onReleaseCallback = NULL;
	}
	if (func) {
		onReleaseCallback = new LuaCall<int, Event*>((lua_State*)func, "");
	}
}


void Button::onCancel(lua_State* func) 
{
	
	if (onCancelCallback) {
		delete onCancelCallback;
		onCancelCallback = NULL;
	}
	if (func) {
		onCancelCallback = new LuaCall<int, Event*>((lua_State*)func, "");
	}
}

Button::~Button()
{
	this->setEnabled(false);
}

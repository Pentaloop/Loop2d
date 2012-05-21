/*
 *  Event.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/2/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Event.h"

void Event::addObject(string key, int object)
{
	_TypedObject* obj = new _TypedObject();
	obj->autorelease();
	obj->intValue = object;
	obj->valueType = ValueTypeInt;
	CCMutableDictionary<string, _TypedObject*>::setObject(obj, key);
}


void Event::addObject(string key, float object)
{
	_TypedObject* obj = new _TypedObject();
	obj->autorelease();
	obj->floatValue = object;
	obj->valueType = ValueTypeFloat;
	CCMutableDictionary<string, _TypedObject*>::setObject(obj, key);
}


void Event::addObject(string key, double object)
{
	_TypedObject* obj = new _TypedObject();
	obj->autorelease();
	obj->doubleValue = object;
	obj->valueType = ValueTypeDouble;
	CCMutableDictionary<string, _TypedObject*>::setObject(obj, key);
}

void Event::addObject(string key, string object)
{
	_TypedObject* obj = new _TypedObject();
	obj->autorelease();
	obj->strValue = object;
	obj->valueType = ValueTypeString;
	CCMutableDictionary<string, _TypedObject*>::setObject(obj, key);
}

void Event::addObject(string key, void* object, string type)
{
	_TypedObject* obj = new _TypedObject();
	obj->autorelease();
	obj->object = object;
	obj->type = type;
	obj->valueType = ValueTypeCustom;
	CCMutableDictionary<string, _TypedObject*>::setObject(obj, key);
}
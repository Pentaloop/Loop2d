/*
 *  Event.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/2/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */


#include "cocos2d.h"

#ifndef __EVENT_H__
#define __EVENT_H__

using namespace cocos2d;

typedef enum {
	ValueTypeCustom,
	ValueTypeInt,
	ValueTypeFloat,
	ValueTypeDouble,
	ValueTypeString,
} ValueType;


class _TypedObject:public CCObject
{
public:
	void* object;
	string type;
	int intValue;
	int floatValue;
	int doubleValue;
	string strValue;
	ValueType valueType;
};


class Event : public CCMutableDictionary<string, _TypedObject*>
{
public:
	void addObject(string key, int object);
	void addObject(string key, float object);
	void addObject(string key, double object);
	void addObject(string key, string object);
	void addObject(string key, void* object, string type);
};

#endif
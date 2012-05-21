/*
 *  Settings.h
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/6/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "cocos2d.h"

#ifndef __SETTINGS_H__
#define __SETTINGS_H__

using namespace cocos2d;

class Settings {
public:
	static void setValue(string aKey, string aValue);
	static void setValue(string aKey, int aValue);
	static void setValue(string aKey, float aValue);
	static void setValue(string aKey, double aValue);
	static void setValue(string aKey, bool aValue);
	
	static string getValue(string aKey);
	static int getValue(int aKey);
	static float getValue(float aKey);
	static double getValue(double aKey);
	static bool getValue(bool aKey);
	
};

#endif
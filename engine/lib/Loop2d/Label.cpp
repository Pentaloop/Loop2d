/*
 *  Label.cpp
 *  BubbleTrouble
 *
 *  Created by Haseeb Yousaf on 3/2/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Label.h"

Label* Label::newLabel(string text, float x, float y, string fontName)
{
	Label* lbl = new Label();
	if (lbl->init())
	{
		CCLog(text.c_str());
		lbl->autorelease();
		if (!fontName.empty()) {
			CCLabelBMFont* label = CCLabelBMFont::labelWithString(text.c_str(),fontName.c_str());
			lbl->addChild(label, 0);
			lbl->setPosition(CCPoint(x, y));
		}
	}
	return lbl;
}
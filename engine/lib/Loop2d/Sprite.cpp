/*
 *  sprite.cpp
 *  test
 *
 *  Created by Haseeb Yousaf on 1/3/12.
 *  Copyright 2012 Penta::Loop inc. All rights reserved.
 *
 */

#include "Sprite.h"

Sprite* Sprite::spriteWithFile(const char *pszFileName) {
	Sprite *sprite = new Sprite();
	if (sprite->initWithFile(pszFileName))
	{
		sprite->autorelease();
	} else {
        delete sprite;
		sprite = NULL;
	}			
	return sprite;
}


Sprite* Sprite::spriteWithFrame(const char *frameName) 
{
	Sprite *sprite = new Sprite();
	if (sprite->initWithSpriteFrameName(frameName))
	{
		sprite->autorelease();
	} else {
        delete sprite;
		sprite = NULL;
	}			
	return sprite;
}



float Sprite::getX() {
	return this->getPosition().x;
}

void Sprite::setX(float newVal) {
	this->setPosition(ccp(newVal, this->getPosition().y));
}

float Sprite::getY() {
	return this->getPosition().x;
}

void Sprite::setY(float newVal) {
	this->setPosition(ccp(this->getPosition().x, newVal));
}


float Sprite::getWidth() 
{
	return this->boundingBox().size.width;
}

void Sprite::setWidth(float newVal) 
{
	//return this->boundingBox().size.width;
}

float Sprite::getHeight()
{
	return this->boundingBox().size.height;
}


void Sprite::setHeight(float newVal)
{
	//return this->boundingBox().size.width;
}


void Sprite::loadSheet(string plistFilename)
{
	/*
	if (!plistFilename.empty()) {
		string path = plistFilename.substr(0, plistFilename.find_last_of(".") + 1);
		if(!path.empty()) {
			string fullpath = path.append(".png");
			Sprite::loadSheet(plistFilename)
		} else {
		}
	}
	 */
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename.c_str());
}


void Sprite::loadSheet(string plistFilename, string imageFilename)
{
	CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(plistFilename.c_str(), imageFilename.c_str());
}


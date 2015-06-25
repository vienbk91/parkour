/*
 * RunnerSprite.h
 *
 *  Created on: 2015/01/27
 *      Author: chu
 */

#ifndef RUNNERSPRITE_H_
#define RUNNERSPRITE_H_

#include "cocos2d.h"
#include "parkour\Global.h"

USING_NS_CC;


class RunnerSprite : public Sprite {
public:

	static RunnerSprite* create();

	virtual void onEnter();

	float getEyeX();


	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

};


#endif /* RUNNERSPRITE_H_ */

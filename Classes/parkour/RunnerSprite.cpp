/*
 * RunnerSprite.cpp
 *
 *  Created on: 2015/01/27
 *      Author: chu
 */

#include "RunnerSprite.h"


RunnerSprite* RunnerSprite::create() {
	auto runnerSprite = new RunnerSprite();

	runnerSprite->initWithFile("parkour_img/runner.png");
	runnerSprite->autorelease();

	return runnerSprite;
}

void RunnerSprite::onEnter() {

	Sprite::onEnter(); // super

	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("parkour_img/running.plist");

	Vector<SpriteFrame*> frames(8);
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "runner" << i << ".png";
		auto frame = cacher->getSpriteFrameByName(ss.str());
		frames.pushBack(frame);
	}

	auto anim = Animation::createWithSpriteFrames(frames, 0.1f);

	auto action = Animate::create(anim);
	auto anime = RepeatForever::create(action);
	this->runAction(anime);

	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(RunnerSprite::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(RunnerSprite::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(RunnerSprite::onTouchEnded, this);
	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
			this);

}

float RunnerSprite::getEyeX() {
    return this->getPositionX() - Global::g_runnerStartX;
}


bool RunnerSprite::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	if(getBoundingBox().containsPoint(touch->getLocation())){
	return true;
	} 

	return false;
}
void RunnerSprite::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {
	this->setPosition(touch->getLocation());
}

void RunnerSprite::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

}

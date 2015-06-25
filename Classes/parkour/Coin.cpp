/*
 * Coin.cpp
 *
 *  Created on: 2015/01/28
 *      Author: chu
 */

#include "parkour\Coin.h"
#include "parkour\Global.h"

USING_NS_CC;

Coin* Coin::create() {
	auto coin = new Coin();

	coin->initWithFile("parkour_img/coin0.png");
	coin->autorelease();

	return coin;

}




void Coin::onEnter() {
	Sprite::onEnter(); // super

	auto cacher = SpriteFrameCache::getInstance();
	cacher->addSpriteFramesWithFile("parkour_img/background.plist");

	Vector<SpriteFrame*> frames(8);
	for (int i = 0; i < 8; i++) {
		std::stringstream ss;
		ss << "coin" << i << ".png";
		auto frame = cacher->getSpriteFrameByName(ss.str());
		frames.pushBack(frame);
	}

	auto anim = Animation::createWithSpriteFrames(frames, 0.1f);

	auto action = Animate::create(anim);
	auto anime = RepeatForever::create(action);
	this->runAction(anime);
}


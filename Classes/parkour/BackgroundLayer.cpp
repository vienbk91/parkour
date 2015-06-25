/*
 * BachgroundLayer.cpp
 *
 *  Created on: 2015/01/19
 *      Author: chu
 */

#include "parkour\BackgroundLayer.h"

USING_NS_CC;

Scene* BackgroundLayer::createScene() {

	auto scene = Scene::create();
	auto layer = BackgroundLayer::create();

	scene->addChild(layer);

	return scene;
}

bool BackgroundLayer::init() {
	if (!Layer::init()) {
		return false;
	}

	/////////////////////////////////////////////////////////////////////////////
	//  load map sprite - test version
	/////////////////////////////////////////////////////////////////////////////

	 Sprite* background1 = Sprite::create("parkour_img/PlayBG.png");
	 background1->setAnchorPoint(Vec2::ZERO);
	 background1->setPosition(Vec2::ZERO);
	 addChild(background1);

	 Sprite* background2 = Sprite::create("parkour_img/PlayBG.png");
	 background2->setAnchorPoint(Vec2::ZERO);
	 background2->setPosition(background1->getContentSize().width , 0);
	 addChild(background2);

	return true;
}


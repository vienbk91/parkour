/*
 * WelcomeScene.cpp
 *
 *  Created on: 2015/03/30
 *      Author: chu
 */

#include "WelcomeScene.h"

USING_NS_CC;

Scene* WelcomeScene::createScene()
{
	auto scene = Scene::create();
	auto layer = WelcomeScene::create();

	scene->addChild(layer);

	return scene;
}

bool WelcomeScene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// Xac dinh kich thuoc cho man hinh
	auto visiableSize = Director::getInstance()->getVisibleSize();

	// Doc file plist
	SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui2/sprites.plist");

	// Xet thoi gian hien tai de thiet lap background
	time_t t = time(NULL);
	tm* lt = localtime(&t);
	int hour = lt->tm_hour;

	Sprite* welcomeBackground;

	if (hour >= 6 && hour <= 17)
	{
		log("Hello Evening");
		welcomeBackground = Sprite::createWithSpriteFrameName("slice40_40.png");
	}
	else
	{
		log("Hello Night");
		welcomeBackground = Sprite::createWithSpriteFrameName("slice42_42.png");
	}


	float scaleX = visiableSize.width / welcomeBackground->getContentSize().width;
	float scaleY = visiableSize.height / welcomeBackground->getContentSize().height;
	welcomeBackground->setScale(scaleX, scaleY);
	welcomeBackground->setPosition(visiableSize.width / 2, visiableSize.height / 2);
	this->addChild(welcomeBackground);

	// Title
	Sprite* title = Sprite::createWithSpriteFrameName("slice23_23.png");
	title->setPosition(Vec2(visiableSize.width / 2, visiableSize.height * 5 / 7));
	this->addChild(title);

	// Start Button
	Sprite *startButton = Sprite::createWithSpriteFrameName("slice34_34.png");
	Sprite *activeStartButton = Sprite::createWithSpriteFrameName("slice34_34.png");
	activeStartButton->setPositionY(5);
	auto menuItem = MenuItemSprite::create(startButton, activeStartButton, NULL, CC_CALLBACK_1(WelcomeScene::menuStartCallback, this));
	menuItem->setPosition(Point(visiableSize.width / 2, visiableSize.height * 2 / 5));

	auto menu = Menu::create(menuItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// Create a Bird and set position


	// Add land
	land1 = Sprite::createWithSpriteFrameName("slice03_03.png");
	float scaleXLand = float(visiableSize.width / land1->getContentSize().width);
	land1->setScaleX(scaleXLand);
	land1->setAnchorPoint(Vec2::ZERO);
	land1->setPosition(Vec2::ZERO);
	this->addChild(land1);

	land2 = Sprite::createWithSpriteFrameName("slice03_03.png");
	land2->setScaleX(scaleXLand);
	land2->setAnchorPoint(Vec2::ZERO);
	land2->setPosition(Vec2(land1->getContentSize().width * scaleXLand - 2.0f , 0.0f));
	this->addChild(land2);



	// Schedule update scroll land
	this->schedule(schedule_selector(WelcomeScene::scrollLandUpdate), 0.01f);


	return true;
}

void WelcomeScene::scrollLandUpdate(float dt)
{
	Size visiableSize = Director::getInstance()->getVisibleSize();
	float scaleXLand = visiableSize.width / land1->getContentSize().width;
	land1->setPositionX(land1->getPositionX() - 2.0f);
	land2->setPositionX(land1->getPositionX() - 2.0f + land1->getContentSize().width * scaleXLand);

	if (land2->getPositionX() == 0)
	{
		land1->setPositionX(0);
	}

}


void WelcomeScene::menuStartCallback(Ref* pSender)
{

}

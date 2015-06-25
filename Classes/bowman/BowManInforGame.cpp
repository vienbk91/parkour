/*
 * BowManInforGame.cpp
 *
 *  Created on: 2015/02/06
 *      Author: chu
 */


#include "BowManInforGame.h"

#define WINSIZE Director::getInstance()->getVisibleSize()

USING_NS_CC;



Scene* BowManInforGame::createScene()
{
	auto scene = Scene::create();
	auto layer = BowManInforGame::create();

	scene->addChild(layer);

	return scene;
}

bool BowManInforGame::init()
{
	if(!Layer::init())
	{
		return false;
	}

	/////////////////////////////////////////////////////////////////
	// BACKGROUNG INFO
	/////////////////////////////////////////////////////////////////

	Sprite* background = Sprite::create("img/background/bg_info.png");
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2(WINSIZE.width/2 , WINSIZE.height/2));
	this->addChild(background);


	/////////////////////////////////////////////////////////////////
	// DIALOG INFO
	/////////////////////////////////////////////////////////////////

	Sprite* infoDialog = Sprite::create("img/dialog/info_dialog.png");
	infoDialog->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	infoDialog->setPosition(Vec2(WINSIZE.width/2 , WINSIZE.height/2));
	this->addChild(infoDialog);

	

	/////////////////////////////////////////////////////////////////
	// BACK BUTTON
	/////////////////////////////////////////////////////////////////

	Sprite* backSprite1 = Sprite::create("img/button/back_btn.png");
	Sprite* backSprite2 = Sprite::create("img/button/back_btn1.png");

	MenuItemSprite* backBtn = MenuItemSprite::create(
		backSprite1,
		backSprite2,
		CC_CALLBACK_1(BowManInforGame::backCallback, this)
		);

	backBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	backBtn->setPosition(Vec2(
		10 + backBtn->getContentSize().width / 2,
		WINSIZE.height - 10 - backBtn->getContentSize().height / 2
		));

	Menu* menu = Menu::create(backBtn,NULL);

	this->addChild(menu);

	return true;
}


void BowManInforGame::backCallback(Ref* pSender)
{
	// Todo
	auto menuScene = BowManMenuScene::createScene();
	Director::getInstance()->replaceScene(menuScene);
}
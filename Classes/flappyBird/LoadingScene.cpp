/*
 * LoadingScene.cpp
 *
 *  Created on: 2015/03/29
 *      Author: Chu Quang Vien
 */
#include "LoadingScene.h"

USING_NS_CC;

Scene* LoadingScene::createScene()
{
	auto scene = Scene::create();
	auto layer = LoadingScene::create();

	scene->addChild(layer);

	return scene;
}

bool LoadingScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* loadBackground = Sprite::create("splash.png");
	float scaleX = visibleSize.width / loadBackground->getContentSize().width;
	float scaleY = visibleSize.height / loadBackground->getContentSize().height;
	loadBackground->setScale(scaleX, scaleY);
	loadBackground->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(loadBackground);

	auto moveSequence = Sequence::create(
		DelayTime::create(5.0f)
		, CallFuncN::create(CC_CALLBACK_1(LoadingScene::moveCallback, this))
		, NULL);
	loadBackground->runAction(moveSequence);


	return true;
}

void LoadingScene::moveCallback(Ref* pSender)
{
	auto welcomeScene = WelcomeScene::createScene();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f , welcomeScene));
}

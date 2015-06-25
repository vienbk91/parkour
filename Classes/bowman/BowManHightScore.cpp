#include "bowman\BowManHightScore.h"

USING_NS_CC;

Scene* BowManHightScore::createScene()
{
	auto scene = Scene::create();
	auto layer = BowManHightScore::create();

	scene->addChild(layer);

	return scene;
}

bool BowManHightScore::init()
{
	if(!Layer::init()){
		return false;
	}


	Size visibleSize = Director::getInstance()->getVisibleSize();

	Sprite* backSprite1 = Sprite::create("img/button/back_btn.png");
	Sprite* backSprite2 = Sprite::create("img/button/back_btn1.png");


	MenuItemSprite* backBtn = MenuItemSprite::create(
		backSprite1 , 
		backSprite2 ,
		CC_CALLBACK_1(BowManHightScore::backCallback , this)
		);

	backBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	backBtn->setPosition(Vec2(
		10 + backBtn->getContentSize().width/2 ,
		visibleSize.height - 10 - backBtn->getContentSize().height/2
		));

	Menu* menu = Menu::create(
		backBtn,
		NULL
		);

	this->addChild(menu);

	return true;
}

void BowManHightScore::backCallback(Ref* pSender)
{
	// Todo
	auto menuScene = BowManMenuScene::createScene();
	Director::getInstance()->replaceScene(menuScene);
}
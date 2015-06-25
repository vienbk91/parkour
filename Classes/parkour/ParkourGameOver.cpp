/*
 * ParkourGameOver.cpp
 *
 *  Created on: 2015/01/30
 *      Author: chu
 */

#include "ParkourGameOver.h"
#include "PlayScene.h"

#define WINSIZE Director::getInstance()->getVisibleSize()

USING_NS_CC;

ParkourGameOver* ParkourGameOver::create(const Color4B& color)
{
	ParkourGameOver *pRet = new ParkourGameOver();
    if(pRet && pRet->initWithColor(color))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool ParkourGameOver::initWithColor(const Color4B& color){


	if(!LayerColor::initWithColor(color)){
		return false;
	}

	cocos2d::log("Day la layer moi");

	createDebug();
	return true;

}

void ParkourGameOver::createDebug()
{
	/////////////////////////////////////////////////
	// DEBUG BUTTON
	/////////////////////////////////////////////////

	MenuItemImage* back = MenuItemImage::create("parkour_img/back_btn.png", "parkour_img/back_btn1.png", CC_CALLBACK_1(ParkourGameOver::rebootCallback, this));
	back->setPosition(Vec2(WINSIZE.width - 40, WINSIZE.height - 40));

	Menu* menu = Menu::create(back, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu);
}

void ParkourGameOver::rebootCallback(Ref *pSEnder){
	Director::getInstance()->replaceScene(ListViewGameScene::createScene());
}
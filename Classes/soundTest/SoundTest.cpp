#include "soundTest\SoundTest.h"

USING_NS_CC;

Scene* SoundTest::createScene()
{
	auto scene = Scene::create();
	auto layer = SoundTest::create();

	scene->addChild(layer);

	return scene;
}

bool SoundTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto closeItem = MenuItemImage::create(
		"CloseNormal.png",
		"CloseSelected.png",
		CC_CALLBACK_1(SoundTest::menuCloseCallback, this));

	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width / 2 - 20 ,
		origin.y + visibleSize.height - closeItem->getContentSize().height / 2 - 20));

	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	// Effect and music
	auto soundManager = CocosDenshion::SimpleAudioEngine::getInstance();

	soundManager->preloadEffect("soundTest/effect.wav");
	soundId = soundManager->playEffect("soundTest/effect.wav", true); // true la loop lien tuc
	

	soundManager->setEffectsVolume(0.5); // No chi co the dieu chinh tu 0->1 so voi am thanh duoc thiet lap cua may(chi co the lam nho hon)


	return true;
}

void SoundTest::menuCloseCallback(Ref* pSender)
{
	// Stop all effect
	auto soundManager = CocosDenshion::SimpleAudioEngine::getInstance();

	//soundManager->stopAllEffects();

	// Stop 1 effect
	//soundManager->stopEffect(soundId);

	// Pause effect
	// Neu effect dang chay thi no la true
	if (isEffectPlaying)
	{
		soundManager->pauseEffect(soundId); // Neu true thi pause lai
	}
	else
	{
		soundManager->resumeEffect(soundId);
	}

	isEffectPlaying = !isEffectPlaying;
	

}
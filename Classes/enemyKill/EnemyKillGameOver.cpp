/*
 * FirstGameOver.cpp
 *
 *  Created on: 2015/01/15
 *      Author: chu
 */

#include "enemyKill\EnemyKillGameOver.h"
#include "enemyKill\EnemyKillScene.h"


USING_NS_CC;

int EnemyKillGameOver::fScore;

Scene* EnemyKillGameOver::createScene(int score) {
	auto scene = Scene::create();

	if (score != 0) {
		cocos2d::log("Score over: %d", score);

		EnemyKillGameOver::fScore = score;
	}

	auto layer = EnemyKillGameOver::create();
	scene->addChild(layer);
	return scene;
}

bool EnemyKillGameOver::init() {
	if (!Layer::init()) {
		return false;
	}

	cocos2d::log("Chuyen den scene lose game");
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Tao ra layer chua thong bao ban thua
	auto youLoseLabel = LabelTTF::create("You Lose", "Arial", 50);
	youLoseLabel->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height / 2));
	this->addChild(youLoseLabel);

	// Tao ra layer chua thong bao ban thua
	std::stringstream text;
	text << fScore << std::endl;
	cocos2d::log("fuck %s", text.str().c_str());

	auto youScoreLabel = LabelTTF::create("", "Arial", 50);
	youScoreLabel->setString(text.str().c_str());
	youScoreLabel->setPosition(
			Vec2(visibleSize.width / 2 + 180, visibleSize.height / 2));
	this->addChild(youScoreLabel);

	auto backLabel = LabelTTF::create("Back", "Arial", 30);
	MenuItemLabel* backButton = MenuItemLabel::create(backLabel,
			CC_CALLBACK_1(EnemyKillGameOver::backCallBack , this));
	backButton->setPosition(
			Vec2(visibleSize.width / 2, visibleSize.height / 2 - 80));

	Menu* menuBack = Menu::create(backButton, NULL);
	menuBack->setPosition(Vec2::ZERO);
	this->addChild(menuBack);


	return true;

}

void EnemyKillGameOver::backCallBack(Ref* pRender) {

	cocos2d::log("Quay lai");
	Director::getInstance()->replaceScene(EnemyKillScene::createScene());
}

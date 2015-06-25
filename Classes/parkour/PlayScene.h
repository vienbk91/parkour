/*
* PlayScene.h
*
*  Created on: 2015/01/19
*      Author: chu
*/

#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_

#include "cocos2d.h"
#include "BackgroundLayer.h"
#include "Global.h"
#include "RunnerSprite.h"
#include "ParkourMenu.h"
#include "ParkourGameOver.h"
#include "ui\CocosGUI.h"

USING_NS_CC;
using namespace ui;


class PlayScene: public cocos2d::Layer {
public:
	

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void setWorld(PhysicsWorld *world);
	CREATE_FUNC(PlayScene);

	virtual void onEnter();

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchCanceled(cocos2d::Touch* touch, cocos2d::Event* event);

	int score;
	bool onStopFlag;

protected:

	RunnerSprite* runnerSprite;
	BackgroundLayer* backgroundLayer;
	Coin* coin;
	Rock* rock;
	Node* nodeLine;

	cocos2d::Label* labelScore;

	int mapIndex;

	void createBackground();
	void createGround();
	void createRunner();
	void createCoin();
	void createRock();
	void createStatus();
	void createDebug();

	void update(float dt);
	bool onContactBegin(PhysicsContact& contact);

	void removeCointCollision();
private:
	PhysicsWorld *myWorld;
	virtual void debugCallback(Ref *pSEnder, Widget::TouchEventType type);


};

#endif /* PLAYSCENE_H_ */

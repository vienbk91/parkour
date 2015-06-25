/*
 * Box2DTest.h
 *
 *  Created on: 2015/02/06
 *      Author: chu
 */

#ifndef BOX2DTEST_H_
#define BOX2DTEST_H_

#include "cocos2d.h"
#include "Box2D/Box2D.h"

USING_NS_CC;

class Box2DTest: public cocos2d::Layer {

public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(Box2DTest);

	b2World* world; // Dinh nghia world cua physics

	b2Body *ballBody ; // Body của bong
	b2BodyDef bodyDef; // Dinh nghia cai body o tren
	b2FixtureDef fixtureDef; // Dinh nghia 1 so thuoc tinh nhu ma sat,trong luong,...
	b2CircleShape bodyShape; // Hinh khoi cua body

	Sprite *ball; // Hinh qua bong
	float deltaTime; // Bien tinh thoi gian

	bool existBall;
	float ballX;
	float ballY;
	int dragOffsetStartX;
	int dragOffsetStartY;
	int dragOffsetEndX;
	int dragOffsetEndY;

	float powerMultiplier; // Luc
	Sprite *points[31];

	void defineBall(); // Tao qua bong theo Box2D

	void simulateTrajectory(b2Vec2 coord);
	
	bool onTouchBegan(cocos2d::Touch* touch , cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch , cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch , cocos2d::Event* event);

	void update(float dt);
	
	void addWall(float w , float h , float px , float py); // Tao 1 khung wall cho bong va cham
	
};

#endif /* BOX2DTEST_H_ */

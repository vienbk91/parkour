#ifndef BREAKOUTMAINSCENE_H_
#define BREAKOUTMAINSCENE_H_

#include "cocos2d.h"
#include "BreakoutGameOver.h"

USING_NS_CC;

class BreakoutMainScene : public cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(BreakoutMainScene);

	int score;
	bool checkLoseFlag;
	bool checkMissBall;

	Sprite* ball;
	Sprite* paddle;
	
	Sprite* screenBorder;
	std::vector<Sprite*> blocksArray;

	void createBound();
	void createBall();
	void createPaddle();
	void createBlock();

	bool onTouchBegan(cocos2d::Touch* touch , cocos2d::Event* event);
	void onTouchMoved(cocos2d::Touch* touch , cocos2d::Event* event);
	void onTouchEnded(cocos2d::Touch* touch , cocos2d::Event* event);
	void onTouchCancelled(cocos2d::Touch* touch , cocos2d::Event* event);

	bool onContactBegin(PhysicsContact &contact);

	void updateGame(float dt);

protected:
	enum Tag
	{
		T_ScreenBorder = 0 ,
		T_Ball = 1 ,
		T_Paddle = 2 ,
		T_Block = 3
	};

};

#endif BREAKOUTMAINSCENE_H_
/*
 * FirstGameScene.h
 *
 *  Created on: 2015/01/14
 *      Author: chu
 */

#ifndef FIRSTGAMESCENE_H_
#define FIRSTGAMESCENE_H_

#include "cocos2d.h"
#include "EnemyKillGameOver.h"
#include "uiTest\ListViewGameScene.h"

USING_NS_CC;

using namespace cocos2d;
using namespace std;


class EnemyKillScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(EnemyKillScene);


	void createBack();


    void addTarget();
    void logicGame(float dt);
    void spriteMoveFinished(cocos2d::Node* node);

    cocos2d::Sprite* player;


    int score;
    cocos2d::Label* labelScore;

    bool onTouchBegan(Touch* touch , Event* event);
    void onTouchMoved(Touch* touch , Event* event);
    void onTouchEnded(Touch* touch , Event* event);

    bool checkCollisionSprite(Sprite* sprite1 , Sprite* sprite2);
    bool onContactBegin(PhysicsContact& contact);

	void backCallback(Ref* pSender);

	
};



#endif /* FIRSTGAMESCENE_H_ */

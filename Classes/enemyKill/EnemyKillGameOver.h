/*
 * FirstGameOver.h
 *
 *  Created on: 2015/01/15
 *      Author: chu
 */

#ifndef FIRSTGAMEOVER_H_
#define FIRSTGAMEOVER_H_

#include "cocos2d.h"
#include "EnemyKillScene.h"

USING_NS_CC;

using namespace cocos2d;
using namespace std;


class EnemyKillGameOver : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene(int score);

	static int fScore;

    virtual bool init();

    CREATE_FUNC(EnemyKillGameOver);

	void backCallBack(Ref* pRender);
	void moveSceneCallBack(Ref* pRender);
};


#endif /* FIRSTGAMEOVER_H_ */

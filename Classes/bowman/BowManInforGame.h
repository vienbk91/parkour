/*
 * BowManInforGame.h
 *
 *  Created on: 2015/02/06
 *      Author: chu
 */

#ifndef BOWMANINFORGAME_H_
#define BOWMANINFORGAME_H_

#include "cocos2d.h"
#include "BowManMenuScene.h"


class BowManInforGame : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(BowManInforGame);

	void backCallback(Ref*);
};

#endif /* BOWMANINFORGAME_H_ */

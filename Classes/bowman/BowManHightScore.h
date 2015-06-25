#ifndef BOWMANHIGHTSCORE_H_
#define BOWMANHIGHTSCORE_H_

#include "cocos2d.h"
#include "BowManMenuScene.h"

class BowManHightScore : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(BowManHightScore);


	void backCallback(Ref* pSender);

};


#endif /* BOWMANHIGHTSCORE_H_ */

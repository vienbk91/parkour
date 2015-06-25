#ifndef _WELCOMESCENE_H_
#define _WELCOMESCENE_H_

#include "cocos2d.h"

USING_NS_CC;

class WelcomeScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	CREATE_FUNC(WelcomeScene);

	virtual bool init();


private:
	Sprite* land1;
	Sprite* land2;

	virtual void menuStartCallback(Ref* pSender);
	void scrollLandUpdate(float dt);


};

#endif // _WELCOMESCENE_H_

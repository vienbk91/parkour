#ifndef __BOWMANMAINSCENE__H__
#define __BOWMANMAINSCENE__H__

#include "cocos2d.h"
#include "bowman\BowManMenuScene.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;


class BowManMainScene : public Layer
{
public:
	static cocos2d::Scene* createScene();

	virtual bool init();

	CREATE_FUNC(BowManMainScene);

	void loadingCallBack(float dt);
};



#endif /* __BOWMANMAINSCENE__H__ */
#ifndef BOWMANSELECTMAP_H_
#define BOWMANSELECTMAP_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "bowman\BowManPlayGameScene.h"

USING_NS_CC;
using namespace ui;

class BowManSelectMap : public cocos2d::Layer

{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(BowManSelectMap);

	ui::ScrollView* scrollMenu;

	void map1Callback(Ref* pSender);
	void map2Callback(Ref* pSender);
	void map3Callback(Ref* pSender);
	void map4Callback(Ref* pSender);

	void update(float dt);

private:

};





#endif //BOWMANSELECTMAP_H_
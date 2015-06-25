#ifndef _SELECTMENUTEST_H_
#define _SELECTMENUTEST_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"

USING_NS_CC;

class SelectMenuTest : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SelectMenuTest);

private:
	int index;
	Sprite* button1;
	Sprite* button2;
	Sprite* button3;

	void update(float dt);
	void pageViewCallback(Ref* pSender, cocos2d::ui::PageViewEventType type);
protected:
};



#endif /* _SELECTMENUTEST_H_ */
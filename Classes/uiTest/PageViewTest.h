#ifndef _PAGEVIEWTEST_H_
#define _PAGEVIEWTEST_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"


USING_NS_CC;

class PageViewTest : public cocos2d::Layer
{
public:
	
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(PageViewTest);

	void pageViewCallback(Ref* pSender, cocos2d::ui::PageViewEventType type);

private:
};





#endif /* _PAGEVIEWTEST_H_ */
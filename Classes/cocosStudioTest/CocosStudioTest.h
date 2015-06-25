#ifndef _COCOSSTUDUOTEST_H_
#define _COCOSSTUDUOTEST_H_

#include "cocos2d.h"
#include "cocostudio\CocoStudio.h"
#include "extensions\cocos-ext.h"
#include "uiTest\ListViewGameScene.h"

USING_NS_CC;
using namespace cocostudio;


class CocosStudioTest : public Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(CocosStudioTest);
private:
	Armature* armature;
	virtual void rebootCallback(Ref *pSEnder);
};


#endif // _COCOSSTUDUOTEST_H_
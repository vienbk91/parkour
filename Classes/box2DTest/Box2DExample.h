#ifndef BOX2DEXAMPLE_H_
#define BOX2DEXAMPLE_H_

#include "cocos2d.h"
#include "Box2D\Box2D.h"

USING_NS_CC;


class Box2DExample : public cocos2d::Layer

{
public:
	Box2DExample();
	~Box2DExample();

	static cocos2d::Scene* createScene();
	virtual bool init();

	void initPhysics();

	CREATE_FUNC(Box2DExample);

private:

};

#endif BOX2DEXAMPLE_H_

#ifndef BOWMANPLAYGAMESCENE_H_
#define BOWMANPLAYGAMESCENE_H_

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "bowman\MyBodyParser.h"
#include "bowman\BowManLevelTwo.h"




USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class BowManPlayGameScene : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void setWorld(PhysicsWorld *world);
	CREATE_FUNC(BowManPlayGameScene);
	virtual void onEnterTransitionDidFinish();

	

private:
	PhysicsWorld *myWorld;
	PhysicsJointPin* jointLine;

	Vec2 touchBeginPosition;
	Vec2 touchEndMovePosition;
	Vec2 touchEndPosition;
	float angle;
	float pullPower;
	std::vector<Sprite*> bowArray;

	void createDebug();
	void createArrowSprite();
	virtual Sprite* createBow();

	void bowRotateUpdate(float dt);

	void createLevelUpDialog();
	
	virtual void rebootCallback(Ref *pSEnder, Widget::TouchEventType type);
	virtual void debugCallback(Ref *pSEnder, Widget::TouchEventType type);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	bool onContactBegin(PhysicsContact&);

	void nextLevelCallBack(Ref* pSender);
	void replayCallback(Ref* pSender);

protected:
	enum Tag{
		T_Background = 1,
		T_Ground = 2,
		T_Bowman_Head = 3,
		T_Arrow = 4,
		T_Line = 5,
		T_Victim = 6,
		T_Bow = 7,

	};

	enum Z_Order
	{
		Z_Background = 1,
		Z_Box = 3,
		Z_Pylon = 3 ,
		Z_Bowman_Body = 2,
		Z_Bowman_Head = 2,
		Z_Victim = 3,
		Z_Line = 3,
		Z_Bow = 4
	};


};


#endif // !BOWMANPLAYGAMESCENE_H_

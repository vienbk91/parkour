#ifndef BOWMANLEVELTWO_H_
#define BOWMANLEVELTWO_H_

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "MyBodyParser.h"
#include "CustomFollow.h"
#include "BowManPlayGameScene.h"
#include "BowManMenuScene.h"


USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class BowManLevelTwo : public cocos2d::Layer
{
public:

	static cocos2d::Scene* createScene();
	virtual bool init();
	virtual void setWorld(PhysicsWorld *world);
	CREATE_FUNC(BowManLevelTwo);
	virtual void onEnterTransitionDidFinish();

private:
	PhysicsWorld *myWorld;
	PhysicsJointPin* jointLine;


	Node* nodeBow;
	Node* nodeFather;
	Node* nodeBowMan;
	Node* nodeBackground;

	CustomFollow* camera;

	Sprite* bowmanHeadSprite;

	Vec2 touchBeginPosition;
	Vec2 touchEndMovePosition;
	Vec2 touchEndPosition;
	float angle;
	float pullPower;
	std::vector<Sprite*> bowArray;
	
	void createDebugButton();
	void createBackground();
	void createGround();

	Sprite* createBow();
	void createArrowSprite();

	void bowRotateUpdate(float dt);

	virtual void rebootCallback(Ref *pSEnder, Widget::TouchEventType type);
	virtual void debugCallback(Ref *pSEnder, Widget::TouchEventType type);
	
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

	void backgroundUpdate(float);

	bool onContactBegin(PhysicsContact&);
	
	void createLevelUpDialog();
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
		T_NodeFather = 8 , 
		T_NodeBowMan = 9 ,
		T_NodeBackground = 10 ,
		T_NodeBow = 11

	};

	enum Z_Order
	{
		Z_Background = 1,
		Z_NodeBackground = 1 ,
		Z_NodeFather = 2 ,
		Z_NodeBowMan = 2 ,
		Z_Box = 2,
		Z_Pylon = 2,
		Z_Victim = 2,
		Z_Line = 2,
		Z_Bowman_Body = 2,
		Z_Bowman_Head = 2,
		Z_Bow = 3
	};


};


#endif // !BOWMANLEVELTWO_H_

#include "breakout\BreakoutMainScene.h"

#define WINSIZE Director::getInstance()->getVisibleSize()
#define BLOCK_NUMBER 5

USING_NS_CC;

Scene* BreakoutMainScene::createScene()
{
	auto scene = Scene::createWithPhysics();
	// Dinh nghia 1 khong gian vat ly
	auto world = scene->getPhysicsWorld();
	world->setGravity(Vect(0.0f , 0.0f));
	// Hien thi boder debug
	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	
	auto layer = BreakoutMainScene::create();
	scene->addChild(layer);

	return scene;
}

bool BreakoutMainScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	score = 0;
	checkLoseFlag = false;
	checkMissBall = false;

	createBound();
	createBall();
	createPaddle();
	createBlock();
	
	auto listener = EventListenerTouchOneByOne::create();

	listener->onTouchBegan = CC_CALLBACK_2(BreakoutMainScene::onTouchBegan , this);
	listener->onTouchMoved = CC_CALLBACK_2(BreakoutMainScene::onTouchMoved , this);
	listener->onTouchEnded = CC_CALLBACK_2(BreakoutMainScene::onTouchEnded , this);
	listener->onTouchCancelled = CC_CALLBACK_2(BreakoutMainScene::onTouchCancelled , this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener , this);


	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BreakoutMainScene::onContactBegin , this);

	dispatcher->addEventListenerWithSceneGraphPriority(contactListener , this);


	this->schedule(schedule_selector(BreakoutMainScene::updateGame) , 3.0f);

	return true;
}

void BreakoutMainScene::createBound()
{
	// Create Bound
	cocos2d::log("Create Bound");
	screenBorder = Sprite::create();
	
	auto boundBody = PhysicsBody::createEdgeBox(Size(WINSIZE.width- 5 , WINSIZE.height - 5), PHYSICSBODY_MATERIAL_DEFAULT);
	boundBody->getShape(0)->setDensity(1.0f); // Mat do
	boundBody->getShape(0)->setFriction(0.0f); // Ma sat
	boundBody->getShape(0)->setRestitution(1.0f); // Dan hoi
	boundBody->setContactTestBitmask(0x00000001);
	screenBorder->setPhysicsBody(boundBody);
	
	screenBorder->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	screenBorder->setPosition(WINSIZE.width/2 , WINSIZE.height/2);
	
	screenBorder->setTag(Tag::T_ScreenBorder);
	this->addChild(screenBorder);
}

void BreakoutMainScene::createBall()
{
	// Create Ball
	cocos2d::log("Create Ball");
	// Tao qua bong va thiet lap khung vat ly cho no
	ball = Sprite::create("breakout_img/breakout_ball.png");
	ball->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	ball->setPosition(Vec2(WINSIZE.width/2 , WINSIZE.height/2 + 50));
	
	auto ballBody = PhysicsBody::createCircle(ball->getContentSize().width/2 , PHYSICSBODY_MATERIAL_DEFAULT);
	ballBody->getShape(0)->setDensity(1.0f); // trong luc
	ballBody->getShape(0)->setFriction(0.0f);
	ballBody->getShape(0)->setRestitution(1.0f);
	ballBody->setDynamic(true);
	ballBody->setContactTestBitmask(0x00000001);
	
	ballBody->setGravityEnable(false); // Khong set gia toc
	
	
	// Tao 1 luc tac dong
	Vect force = Vect(900000.0f, -900000.0f);
	ballBody->applyImpulse(force);
	
	ball->setPhysicsBody(ballBody);

	ball->setTag(Tag::T_Ball);
	this->addChild(ball);
}


void BreakoutMainScene::createPaddle()
{
	// Create Paddle
	paddle = Sprite::create("breakout_img/Paddle.png");
	

	auto paddleBody = PhysicsBody::createEdgeBox(Size(paddle->getContentSize().width, paddle->getContentSize().height) , PHYSICSBODY_MATERIAL_DEFAULT);
	paddleBody->getShape(0)->setDensity(1.0f); // Ty trong,.mat do
	paddleBody->getShape(0)->setFriction(0.0f); // Ma sat
	paddleBody->getShape(0)->setRestitution(1.0f); // Dan hoi
	paddleBody->setGravityEnable(false);
	paddleBody->setDynamic(false); // Tinh khi tuong tac
	paddleBody->setContactTestBitmask(0x00000001);

	paddle->setPhysicsBody(paddleBody);

	paddle->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	paddle->setPosition(Vec2(WINSIZE.width/2 , paddle->getContentSize().height / 2 + 10));
	
	paddle->setTag(Tag::T_Paddle);
	this->addChild(paddle);
}


void BreakoutMainScene::createBlock()
{
	for (int i = 0; i < BLOCK_NUMBER; i++)
	{
		auto block = Sprite::create("breakout_img/blocks.png");

		auto blockBody = PhysicsBody::createBox(Size(block->getContentSize().width , block->getContentSize().height) , PHYSICSBODY_MATERIAL_DEFAULT);
		blockBody->getShape(0)->setRestitution(0.0f); // dan hoi
		blockBody->getShape(0)->setFriction(0.0f); // ma sat
		blockBody->getShape(0)->setDensity(1.0f); // mat do
		blockBody->setContactTestBitmask(0x00000001);
		blockBody->setDynamic(false);
		blockBody->setGravityEnable(false);
	
		block->setPhysicsBody(blockBody);

		float offsetPosX = block->getContentSize().width/2 + 200*(i) + block->getContentSize().width;
		block->setPosition(Vec2(offsetPosX , 450));

		block->setTag(Tag::T_Block);

		this->addChild(block);
	}
}


bool BreakoutMainScene::onTouchBegan(Touch* touch , Event* event)
{
	// Cac ham touch tiep theo chi duoc thuc hien khi onTouchBegan tra ve true
	return true; 
}

void BreakoutMainScene::onTouchMoved(Touch* touch , Event* event)
{
	auto target = (Sprite*)event->getCurrentTarget();
	Rect targetBox = target->getBoundingBox();

	//touch point
	Point touchPoint = Vec2(touch->getLocationInView().x , touch->getLocationInView().y);

	paddle->setPositionX(touchPoint.x);
}

void BreakoutMainScene::onTouchEnded(Touch* touch , Event* event)
{
}

void BreakoutMainScene::onTouchCancelled(Touch* touch , Event* event)
{
}


bool BreakoutMainScene::onContactBegin(PhysicsContact& contact)
{
	auto nodeA = contact.getShapeA()->getBody()->getNode();
	auto nodeB = contact.getShapeB()->getBody()->getNode();

	int tagA = nodeA->getTag();
	int tagB = nodeB->getTag();


	cocos2d::log("score %d " , score);

	if (tagA ==Tag::T_Block) {
		this->removeChild(nodeA , true);
		score += 1;
	} 
	if (tagB == Tag::T_Block) {
		this->removeChild(nodeB , true);
		score += 1;
	}

	if(score %5 == 0)
	{
		checkMissBall = true;
	}


	if(tagA == Tag::T_Paddle && tagB == Tag::T_Ball  || tagA == Tag::T_Ball &&  tagB == Tag::T_Paddle)
	{
		Vect force = Vect(500000.0f, 500000.0f);
		ball->getPhysicsBody()->applyImpulse(force);
	}

	if(tagA == Tag::T_ScreenBorder || tagB == Tag::T_ScreenBorder)
	{
		if(ball->getPositionY() <= paddle->getPositionY())
		{
			cocos2d::log("Thua roi day");
			Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
			checkLoseFlag = true;
			auto gameover = BreakoutGameOver::create(Color4B(0, 0, 0, 180) , score);
			getParent()->addChild(gameover);
			Director::getInstance()->pause();
			
		} else {
			Vect force = Vect(300000.0f, 300000.0f);
			ball->getPhysicsBody()->applyImpulse(force);
		}
	}

	return true;
}

void BreakoutMainScene::updateGame(float dt)
{
	if(score %5 == 0 && checkMissBall == true && checkLoseFlag == false)
	{
		cocos2d::log("luot choi moi: score: %d ", score);
		checkMissBall = false;
		createBlock();
	}
}
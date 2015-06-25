/*
 * PlayScene.cpp
 *
 *  Created on: 2015/01/19
 *      Author: chu
 */

#include "PlayScene.h"

#define WINSIZE Director::getInstance()->getWinSize()

USING_NS_CC;

using namespace cocos2d;
using namespace std;
using namespace ui;


// Tao Scene chua noi dung game
Scene* PlayScene::createScene() {

	auto scene = Scene::createWithPhysics();

	auto layer = PlayScene::create();
	scene->addChild(layer);

	return scene;
}

// Khoi tao
bool PlayScene::init() {

	if (!Layer::init()) {
		return false;
	}

	score = 0;

	// Su kien touch man hinh
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(PlayScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(PlayScene::onTouchEnded, this);
	touchListener->onTouchCancelled =
			CC_CALLBACK_2(PlayScene::onTouchCancelled, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,
			this); // this o day chinh la PlayScene

	return true;
}

void PlayScene::setWorld(PhysicsWorld *world){
	myWorld = world;
};

void PlayScene::onEnter() {

	Layer::onEnter(); // super

	auto scene = dynamic_cast<Scene*>(this->getParent());
	auto world = scene->getPhysicsWorld();
	world->setGravity(Vec2(0, -100));

	world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	this->setWorld(scene->getPhysicsWorld());

	onStopFlag = false;

	createBackground();
	createGround();
	createRunner();
	createRock();
	createCoin();
	createStatus();
	createDebug();


	// Tao 1 bo lang nghe su kien va cham trong the gioi vat ly cua scene
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin =
			CC_CALLBACK_1(PlayScene::onContactBegin , this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener,
			this);

	//scheduleUpdate();

	schedule(schedule_selector(PlayScene::update), 0.02f);

}

// Khoi tao background
void PlayScene::createBackground() {

	backgroundLayer = BackgroundLayer::create();
	backgroundLayer->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	backgroundLayer->setTag(TagOfLayer::BACKGROUND_LAYER);
	backgroundLayer->setPosition(Vec2::ANCHOR_MIDDLE);
	addChild(backgroundLayer);
}

// Tao khung vat ly cho nen dat
void PlayScene::createGround() {

	PhysicsMaterial material;
	material.density = 0.0f;
	material.friction = 0.0f;
	material.restitution = 0.0f;

	auto body = PhysicsBody::createBox(
			Size(backgroundLayer->getBoundingBox().getMaxX(),
					Global::g_groundHeight), material);
	body->setDynamic(false);
	auto node = Node::create();
	node->setAnchorPoint(Point::ANCHOR_MIDDLE);

	node->setPhysicsBody(body);
	node->setPosition(
			Vec2(backgroundLayer->getContentSize().width / 2,
					Global::g_groundHeight / 2));

	addChild(node);
}

void PlayScene::createRunner() {

	runnerSprite = RunnerSprite::create();
	runnerSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	runnerSprite->setPosition(
			Vec2(
					runnerSprite->getContentSize().width / 2 + 50
							+ Global::g_runnerStartX,
					Global::g_groundHeight
							+ runnerSprite->getContentSize().height / 2));

	auto body = PhysicsBody::createBox(Size(runnerSprite->getContentSize().width - 10,runnerSprite->getContentSize().height),PHYSICSBODY_MATERIAL_DEFAULT);
	//auto body = PhysicsBody::createCircle(runnerSprite->getContentSize().width / 2 , PHYSICSBODY_MATERIAL_DEFAULT);

	body->getShape(0)->setDensity(46000.0f); // mat do
	body->getShape(0)->setFriction(0.0f);
	body->getShape(0)->setRestitution(0.0f);

	body->setDynamic(true);
	body->setContactTestBitmask(0x1);
	body->setRotationEnable(false);
	runnerSprite->setPhysicsBody(body);

	runnerSprite->setTag(TagOfSprite::RUNNER_SPRITE);

	addChild(runnerSprite);
}

void PlayScene::createRock() {
	// Tao rock

	rock = Rock::create();

	rock->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	rock->setPosition(
			runnerSprite->getPositionX()
					+ Director::getInstance()->getWinSize().width - 20,
			Global::g_groundHeight + rock->getContentSize().height / 2);

	auto body = PhysicsBody::createBox(
			Size(rock->getContentSize().width, rock->getContentSize().height),
			PHYSICSBODY_MATERIAL_DEFAULT);
	body->getShape(0)->setDensity(0.0f);
	body->getShape(0)->setFriction(0.0f);
	body->getShape(0)->setRestitution(0.0f);

	body->setDynamic(false);
	body->setContactTestBitmask(0x1); // Neu ko co dong nay thi ko the check va cham
	body->setRotationEnable(false);

	rock->setPhysicsBody(body);
	rock->setTag(TagOfSprite::ROCK_SPRITE);

	addChild(rock);


	// Tao line lam man chan truoc rock va se dung de check va cham khi runner bi chan boi rock

	Vec2 vec[2] = { Vec2(0 ,0), Vec2(0 , rock->getContentSize().height) };

	auto bodyLine = PhysicsBody::createEdgeChain( vec , 2 , PHYSICSBODY_MATERIAL_DEFAULT);

	bodyLine->getShape(0)->setDensity(0.0f);
	bodyLine->getShape(0)->setFriction(0.0f);
	bodyLine->getShape(0)->setRestitution(0.0f);

	bodyLine->setDynamic(false);
	bodyLine->setContactTestBitmask(0x1); // Neu ko co dong nay thi ko the check va cham
	bodyLine->setRotationEnable(false);



	nodeLine = Node::create();
	nodeLine->setAnchorPoint(Point::ANCHOR_MIDDLE);
	nodeLine->setPhysicsBody(bodyLine);

	nodeLine->setPositionX(rock->getPositionX());
	nodeLine->setPositionY(rock->getPositionY() - rock->getContentSize().height / 2);

	nodeLine->setTag(TagOfSprite::LINE_STOP);

	addChild(nodeLine , 100);

}

void PlayScene::createCoin() {
	coin = Coin::create();

	coin->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	coin->setPosition(
			runnerSprite->getPositionX()
					+ Director::getInstance()->getWinSize().width - 20,
			Global::g_groundHeight + rock->getContentSize().height
					+ coin->getContentSize().height / 2 + 50);

	auto body = PhysicsBody::createCircle(coin->getContentSize().width * 0.5,
			PHYSICSBODY_MATERIAL_DEFAULT);

	body->getShape(0)->setDensity(0.0f); // Ty trong
	body->getShape(0)->setFriction(0.0f); // Ma sat
	body->getShape(0)->setRestitution(0.0f); // Dan hoi

	body->setDynamic(false);
	body->setContactTestBitmask(0x1);
	body->setCollisionBitmask(0x000000); // Co nhan tac dung khi va cham hay khong
	body->setRotationEnable(true);
	coin->setPhysicsBody(body);

	coin->setTag(TagOfSprite::COIN_SPRITE);
	addChild(coin);

}

void PlayScene::createStatus(){

	Size visibleSize = Director::getInstance()->getVisibleSize();

	labelScore = Label::createWithTTF("Score : 0", "fonts/arial.ttf", 20);
	labelScore->setPosition(Vec2(visibleSize.width - 100 , visibleSize.height - 28));

	this->addChild(labelScore);

}


void PlayScene::createDebug()
{
	/////////////////////////////////////////////////
	// DEBUG BUTTON
	/////////////////////////////////////////////////

	auto debug = Button::create();
	debug->loadTextureNormal("parkour_img/CloseNormal.png");
	debug->setPosition(Vec2(WINSIZE.width - 180, WINSIZE.height - 40));
	debug->addTouchEventListener(CC_CALLBACK_2(PlayScene::debugCallback, this));
	this->addChild(debug, 99);
}


void PlayScene::debugCallback(Ref *pSEnder, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;

	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		if (myWorld->getDebugDrawMask() == PhysicsWorld::DEBUGDRAW_ALL)
		{
			myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
		}
		else
		{
			myWorld->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		}

		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}

bool PlayScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event) {
	cocos2d::log("Toch Touch");

	// Vect dinh nghia huong tac dong cua luc
	Vect force = Vect(8.0f, 3 * 7000000000.0f);

	runnerSprite->getPhysicsBody()->applyImpulse(force);

	//auto action = MoveTo::create(1 , Vec2(runnerSprite->getPositionX() + 10 , runnerSprite->getPositionY() + 200));
	//runnerSprite->runAction(action);

	return true;

}

void PlayScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void PlayScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event) {

}

void PlayScene::onTouchCanceled(cocos2d::Touch* touch, cocos2d::Event* event) {

}

// Ham update time de background chay lien tuc

void PlayScene::update(float dt) {
	cocos2d::log("update");

	if(onStopFlag == true) return;



	cocos2d::log("currentPosX : %f ", runnerSprite->getPositionX());

	// Thuc hien cho background chay nguoc lai
	backgroundLayer->setPositionX(backgroundLayer->getPositionX() - 2.0f);

	if (backgroundLayer->getPositionX()
			+ (backgroundLayer->getContentSize().width) <= 0) {
		backgroundLayer->setPosition(0, 0);
	}

	// cho rock dich chuyen theo background
	rock->setPositionX(rock->getPositionX() - 2.0f);

	nodeLine->setPositionX(rock->getPositionX() - rock->getContentSize().width/2 - 4 );
	if (rock->getPositionX() <= -(rock->getContentSize().width / 2)) {

		rock->removeFromParent();
		cocos2d::log("Xoa rock");
		createRock();
		cocos2d::log("Tao rock moi");

	}
	coin->setPositionX(coin->getPositionX() - 2.0f);
	if (coin->getPositionX() <= -(coin->getContentSize().width / 2)) {

		coin->removeFromParent();
		cocos2d::log("Xoa coin");
		createCoin();
		cocos2d::log("tao Coin moi");
	}
}

bool PlayScene::onContactBegin(cocos2d::PhysicsContact &contact) {

	auto nodeA = (Sprite*) contact.getShapeA()->getBody()->getNode();
	int tagA = nodeA->getTag();
	auto nodeB = (Sprite*) contact.getShapeB()->getBody()->getNode();
	int tagB = nodeB->getTag();

	cocos2d::log("contact a=%d b=%d", nodeA->getTag(), nodeB->getTag());

	if ((tagA == TagOfSprite::COIN_SPRITE & tagB == TagOfSprite::RUNNER_SPRITE)
			|| (tagB == TagOfSprite::COIN_SPRITE
					& tagA == TagOfSprite::RUNNER_SPRITE)) {
		cocos2d::log("Va cham vao coin");
		
		
		// Thay doi thong bao diem cho Label
		score++;

		std::stringstream text;
		text << "Score : " << score << std::endl;
		cocos2d::log("%s", text.str().c_str());
		
		labelScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		labelScore->setPosition(Vec2(Director::getInstance()->getVisibleSize().width - 100 , Director::getInstance()->getVisibleSize().height - 30));
		labelScore->setString(text.str().c_str());



		// Xu ly xoa coin khi va cham
		removeCointCollision();
		

		cocos2d::log("Score: %d ", score);
		// xu ly viec va cham va an tien coin

	} else if ((tagA == TagOfSprite::LINE_STOP
			& tagB == TagOfSprite::RUNNER_SPRITE)
			|| (tagB == TagOfSprite::LINE_STOP
					& tagA == TagOfSprite::RUNNER_SPRITE)) {
		cocos2d::log("Va cham vao rock");

		onStopFlag = true;

		// Xu ly game over bang cach stop game va chuyen qua scene gameover

		auto gameOver = ParkourGameOver::create(Color4B(0, 0, 0, 180));

		getParent()->addChild(gameOver);

		Director::getInstance()->pause();
	}

	return true;
}

// Ham xu ly va cham giua runner va coin
// Xoa sprite coin va tang diem
void PlayScene::removeCointCollision() {

	auto posX = coin->getPositionX();

	coin->removeFromParent();
	createCoin();
}

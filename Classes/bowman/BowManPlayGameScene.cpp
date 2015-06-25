#include "bowman\BowManPlayGameScene.h"

#define WINSIZE Director::getInstance()->getVisibleSize()
#define BOW_INIT_POS Point(120,120)
#define GROUND_HEIGHT 65


#define PI 3.141592653589793238462643383279502884L /* pi */

USING_NS_CC;

Scene* BowManPlayGameScene::createScene() {

	// Khai bao scene co gan thuoc tinh vat ly
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -1000));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = BowManPlayGameScene::create();
	layer->setWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool BowManPlayGameScene::init() {
	if (!Layer::init()) {
		return false;
	}

	return true;
}

void BowManPlayGameScene::setWorld(PhysicsWorld *world){
	myWorld = world;
};


void BowManPlayGameScene::onEnterTransitionDidFinish() {
	Layer::onEnter();

	/////////////////////////////////////////////////
	// DEBUG BUTTON
	/////////////////////////////////////////////////
	
	auto restart = Button::create();
	restart->loadTextureNormal("CloseNormal.png");
	restart->setPosition(Vec2(WINSIZE.width - 40, WINSIZE.height - 40));
	restart->addTouchEventListener(CC_CALLBACK_2(BowManPlayGameScene::rebootCallback, this));
	this->addChild(restart, 99);

	auto debug = Button::create();
	debug->loadTextureNormal("CloseNormal.png");
	debug->setPosition(Vec2(WINSIZE.width - 180, WINSIZE.height - 40));
	debug->addTouchEventListener(CC_CALLBACK_2(BowManPlayGameScene::debugCallback, this));
	this->addChild(debug, 99);
	
	/////////////////////////////////////////////////
	// BACKGROUND GAME
	/////////////////////////////////////////////////

	auto background = Sprite::create("img/background/bglv1.png");
	background->setScale(float(WINSIZE.width / background->getContentSize().width), float(WINSIZE.height / background->getContentSize().height));
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
	background->setTag(Tag::T_Background);
	this->addChild(background, Z_Order::Z_Background);
	

	/////////////////////////////////////////////////
	// GROUND GAME
	/////////////////////////////////////////////////

	auto groundNode = Node::create();

	auto groundBody = PhysicsBody::createEdgeBox(Size(WINSIZE.width * 4, GROUND_HEIGHT), PHYSICSBODY_MATERIAL_DEFAULT);
	groundBody->getShape(0)->setDensity(1.0f);
	groundBody->getShape(0)->setFriction(0.0f);
	groundBody->getShape(0)->setRestitution(0.0f);
	groundBody->setDynamic(false);
	groundBody->setGravityEnable(false);
	groundBody->setContactTestBitmask(0x00000001);

	
	groundNode->setPhysicsBody(groundBody);
	groundNode->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	groundNode->setPosition(Vec2(WINSIZE.width * 2 , GROUND_HEIGHT/2 ));
	groundNode->setTag(Tag::T_Ground);
	this->addChild(groundNode);
	
	
	/////////////////////////////////////////////////
	// BOWMAN BODY SPRITE
	/////////////////////////////////////////////////

	auto bowmanBodySprite = Sprite::create("img/bowman/bow_body.png");

	bowmanBodySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bowmanBodySprite->setPosition(BOW_INIT_POS);
	this->addChild(bowmanBodySprite, Z_Order::Z_Bowman_Body);
	
	/////////////////////////////////////////////////
	// BOWMAN HEAD SPRITE
	/////////////////////////////////////////////////

	auto bowmanHeadSprite = Sprite::create("img/bowman/bow_head.png");
	bowmanHeadSprite->setTag(Tag::T_Bowman_Head);

	bowmanHeadSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bowmanHeadSprite->setPosition(BOW_INIT_POS);
	this->addChild(bowmanHeadSprite, Z_Order::Z_Bowman_Head);
	
	/////////////////////////////////////////////////
	// BOX AND PYLON GAME
	/////////////////////////////////////////////////
	auto boxSprite = Sprite::create("img/char/box.png");
	boxSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	boxSprite->setPosition(Vec2(WINSIZE.width - 200, GROUND_HEIGHT + boxSprite->getContentSize().height / 2));
	this->addChild(boxSprite, Z_Order::Z_Bow);

	auto pylonSprite = Sprite::create("img/char/pylon.png");
	pylonSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	pylonSprite->setPosition(Vec2(boxSprite->getPositionX() + boxSprite->getContentSize().width / 2 - 10, boxSprite->getPositionY() + boxSprite->getContentSize().height / 2));
	this->addChild(pylonSprite, Z_Order::Z_Pylon);

	/////////////////////////////////////////////////
	// LINE SPRITE
	/////////////////////////////////////////////////

	auto lineSprite = Sprite::create("img/char/line2.png");
	
	auto lineBody = PhysicsBody::createBox(
		Size(lineSprite->getContentSize().width, lineSprite->getContentSize().height),
		PHYSICSBODY_MATERIAL_DEFAULT
		);

	lineBody->getShape(0)->setDensity(0.0f);
	lineBody->getShape(0)->setFriction(0.0f);
	lineBody->getShape(0)->setRestitution(0.0f);
	lineBody->setDynamic(false);
	lineBody->setContactTestBitmask(0x00000001);
	lineSprite->setPhysicsBody(lineBody);

	lineSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lineSprite->setPosition(Vec2(
		pylonSprite->getPositionX() - pylonSprite->getContentSize().width + 20,
		pylonSprite->getPositionY() + pylonSprite->getContentSize().height - lineSprite->getContentSize().height / 2 - 34
		));
	lineSprite->setTag(Tag::T_Line);
	this->addChild(lineSprite, 99);
	
	
	/////////////////////////////////////////////////
	// VICTIM SPRITE
	/////////////////////////////////////////////////
	
	Sprite* victimSprite = Sprite::create("img/victim/victim1.png");
	
	// Body
	MyBodyParser::getInstance()->parseJsonFile("img/json/victimbody1.json");
	auto victimBody = MyBodyParser::getInstance()->bodyFormJson(victimSprite, "victim");
	if (victimBody != nullptr)
	{
		victimBody->setContactTestBitmask(0x00000001);
		victimBody->setDynamic(true);
		victimBody->setGravityEnable(true);
	}
	victimSprite->setPhysicsBody(victimBody);
	victimSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	victimSprite->setPosition(Vec2(
		lineSprite->getPositionX() - 5, 
		lineSprite->getPositionY() - lineSprite->getContentSize().height / 2 - victimSprite->getContentSize().height / 2 + 15
		));
	
	victimSprite->setTag(Tag::T_Victim);
	this->addChild(victimSprite, 99);


	/////////////////////////////////////////////////
	// JOINT VICTIM AND LINE
	/////////////////////////////////////////////////

	jointLine = PhysicsJointPin::construct(lineBody, victimBody, lineSprite->getPosition() - Vec2(0, 70));
	jointLine->setCollisionEnable(false);
	jointLine->getBodyB()->setRotationEnable(false);
	myWorld->addJoint(jointLine);


	/////////////////////////////////////////////////
	// SCHEDULE BOW ROTATE
	/////////////////////////////////////////////////

	// Su dung ham update de check goc bay cua mui ten lien tuc
	this->schedule(schedule_selector(BowManPlayGameScene::bowRotateUpdate), 0.01f);

	/////////////////////////////////////////////////
	// TOUCH EVENT
	/////////////////////////////////////////////////
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BowManPlayGameScene::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(BowManPlayGameScene::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BowManPlayGameScene::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);

	/////////////////////////////////////////////////
	// COLLISION EVENT
	/////////////////////////////////////////////////
	
	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BowManPlayGameScene::onContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);

}


Sprite* BowManPlayGameScene::createBow()
{
	auto bowSprite = Sprite::create("img/char/bow.png");
	

	// Thiet lap khung vat ly cho bow
	PhysicsBody* bowBody = PhysicsBody::createBox(
		Size(40, 10),
		PHYSICSBODY_MATERIAL_DEFAULT
		);

	bowBody->getShape(0)->setDensity(100.0f); // Mat do
	bowBody->getShape(0)->setFriction(1.0f); // Ma sat
	bowBody->getShape(0)->setRestitution(1.0f); // Dan hoi

	bowBody->setDynamic(true);
	bowBody->setGravityEnable(false);
	bowBody->setContactTestBitmask(0x00000001);
	bowBody->setCollisionBitmask(0x00000010);
	bowBody->setCategoryBitmask(0x00000001);
	bowSprite->setPhysicsBody(bowBody);

	bowSprite->setVisible(false);
	bowSprite->setTag(Tag::T_Bow);
	return bowSprite;
}


void BowManPlayGameScene::createArrowSprite()
{
	/////////////////////////////////////////////////
	// ARROW SPRITE
	/////////////////////////////////////////////////

	Sprite* bowmanHeadSprite = (Sprite*)this->getChildByTag(Tag::T_Bowman_Head);

	Sprite* arrowSprite = Sprite::create("img/char/arrow1.png");
	arrowSprite->setTag(Tag::T_Arrow);

	arrowSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	arrowSprite->setPosition(Vec2(
		bowmanHeadSprite->getContentSize().width,
		bowmanHeadSprite->getContentSize().height / 2 + 13
		));

	bowmanHeadSprite->addChild(arrowSprite);
}

void BowManPlayGameScene::bowRotateUpdate(float dt)
{
	for (auto &bow : bowArray)
	{
		if (bow != nullptr && bow->getPhysicsBody() != nullptr && bow->getPhysicsBody()->getVelocity() != Vec2::ZERO && bow->getPhysicsBody()->isGravityEnabled() == true) 
		{
			// Chieu duong la chieu quay theo chieu kim dong ho
			bow->setRotation(-bow->getPhysicsBody()->getVelocity().getAngle() * 180 / PI);
		}
	}
}


// Xu ly bat dau su kien touch
bool BowManPlayGameScene::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	/////////////////////////////////////////////////
	// TOUCH BEGAN
	/////////////////////////////////////////////////
	bool res = false;

	/////////////////////////////////////////////////
	// BOW SPRITE
	/////////////////////////////////////////////////

	Sprite* bowmanHeadSprite = (Sprite*)this->getChildByTag(Tag::T_Bowman_Head);
	Sprite* arrowSprite = (Sprite*)bowmanHeadSprite->getChildByTag(Tag::T_Arrow);


	if ( bowmanHeadSprite != nullptr && bowmanHeadSprite->getBoundingBox().containsPoint(touch->getLocation()))
	{
		/////////////////////////////////////////////////
		// CREATE ARROW
		/////////////////////////////////////////////////

		if (arrowSprite == nullptr)
		{
			createArrowSprite();
			cocos2d::log("Tao ra arrow");
		}

		/////////////////////////////////////////////////
		// CREATE BOW AND POSITION
		/////////////////////////////////////////////////

		auto bowSprite = createBow();

		bowArray.push_back(bowSprite);
		bowArray.back()->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
		bowArray.back()->setPosition(Vec2(
			BOW_INIT_POS.x + bowmanHeadSprite->getContentSize().width / 2 + bowArray.back()->getContentSize().width / 2 - 60,
			BOW_INIT_POS.y + 13
			));

		cocos2d::log("Tao bow");
		this->addChild(bowArray.back(), Z_Order::Z_Bow);

		touchBeginPosition = touch->getLocation();
		res = true;
	}




	return res; // res = true thi moi chuyen qua touch move,touch end
}

// Xu ly khi touch and move
void BowManPlayGameScene::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{

	/////////////////////////////////////////////////
	// TOUCH MOVE AND ROTATE BOWMAN,ARROW
	/////////////////////////////////////////////////

	auto bowmanHeadSprite = (Sprite*)this->getChildByTag(Tag::T_Bowman_Head);
	Sprite* arrowSprite = (Sprite*)bowmanHeadSprite->getChildByTag(Tag::T_Arrow);

	touchEndMovePosition = touch->getLocation();

	// Vector tao boi diem touch dau va diem touch cuoi
	Vec2 vectorPull = Vec2(); // Vector keo
	vectorPull = touchEndMovePosition - touchBeginPosition;

	angle = CC_RADIANS_TO_DEGREES(vectorPull.getAngle()); // Goc giua 2 vector: Ox va vectorPull

	/*
	Rotate lay diem goc la Anchor Point
	Quay theo chieu kim dong ho la chieu duong , nguoc chieu kim dong ho la chieu am
	Goc quay thi: xOx' = 180 , x'Ox = -180
	Vi arrow la child cua headbow nen khi headbow xoay, no cung xoay theo
	*/

	if (angle >= 135 && angle <= 180)
	{
		bowmanHeadSprite->setRotation(180 - angle);
	}
	else if (angle <= -135 && angle >= -180)
	{
		bowmanHeadSprite->setRotation((180 + angle) * (-1));
	}

	/////////////////////////////////////////////////
	// CHANGE BOWMAN AND ARROW WHEN ROTATE
	/////////////////////////////////////////////////

	// Xu lu thay doi hinh dang headbow va arrow tuy theo luc ban
	pullPower = vectorPull.getLength();
	//cocos2d::log("pow = %f", pullPower);

	if (pullPower <= 30)
	{
		bowmanHeadSprite->setTexture("img/bowman/headbow1.png");
		arrowSprite->setTexture("img/char/arrow1.png");

	}
	else if (pullPower <= 60)
	{
		bowmanHeadSprite->setTexture("img/bowman/headbow2.png");
		arrowSprite->setTexture("img/char/arrow2.png");
	}
	else if (pullPower <= 90)
	{
		bowmanHeadSprite->setTexture("img/bowman/headbow3.png");
		arrowSprite->setTexture("img/char/arrow3.png");
	}
	else
	{
		bowmanHeadSprite->setTexture("img/bowman/headbow4.png");
		arrowSprite->setTexture("img/char/arrow4.png");
	}
}



// Xu ly khi tha tay ra
void BowManPlayGameScene::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	/////////////////////////////////////////////////
	// TOUCH END
	/////////////////////////////////////////////////
	cocos2d::log("Touch end");

	Sprite* bowmanHeadSprite = (Sprite*)this->getChildByTag(Tag::T_Bowman_Head);
	Sprite* arrowSprite = (Sprite*)bowmanHeadSprite->getChildByTag(Tag::T_Arrow);

	/////////////////////////////////////////////////
	// PHAN CHIA CAP DO LUC BAN
	/////////////////////////////////////////////////

	float xUnit = 500000.0f; // Power Unit

	touchEndPosition = touch->getLocation();
	Vect force = touchBeginPosition - touchEndPosition; // Vector nguoc huong voi vector keo


	/////////////////////////////////////////////////
	// XET HUONG BAN CUA BOW 
	/////////////////////////////////////////////////

	// Gioi han goc ban cua bow
	bowArray.back()->setVisible(true);
	bowArray.back()->getPhysicsBody()->setGravityEnable(true);
	
	if (CC_RADIANS_TO_DEGREES(force.getAngle()) >= 60)
	{
		// Neu goc keo > 60 thi gioi han tai 60 voi cuong do luc bang cuong do luc keo
		Vect unit = Vect(1, 1 / cos(60));
		force = unit;
	}
	else if (CC_RADIANS_TO_DEGREES(force.getAngle()) <= -60)
	{
		Vect unit = Vect(1, -1 / cos(60));
		force = unit;
	}
	cocos2d::log("force %f", CC_RADIANS_TO_DEGREES(force.getAngle()));
	bowArray.back()->getPhysicsBody()->applyImpulse(force * xUnit); // Tao 1 luc keo bang (-xUnit) lan vector keo


	/////////////////////////////////////////////////
	// BAN XONG DUA BOWMAN VE VI TRI BAN DAU
	/////////////////////////////////////////////////
	
	if (arrowSprite != nullptr)
	{
		// Xoa arrow
		bowmanHeadSprite->removeChildByTag(Tag::T_Arrow);
		cocos2d::log("Xoa arrow neu co");
	}
	// Chuyen bowmanHead ve dang ban dau
	bowmanHeadSprite->setTexture("img/bowman/headbow1.png");
	// Xoay bowmanHead ve goc (0,0)
	bowmanHeadSprite->setRotation(0.0f);

}


bool BowManPlayGameScene::onContactBegin(PhysicsContact& contact)
{
	/////////////////////////////////////////////////
	// KHAI BAO
	/////////////////////////////////////////////////
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

	auto victimSprite = (Sprite*)this->getChildByTag(Tag::T_Victim);
	
	if (nodeA == nullptr)
	{
		cocos2d::log("nodeA null");
		return false;
	}
	if (nodeB == nullptr)
	{
		cocos2d::log("nodeB null");
		return false;
	}

	int tagA = nodeA->getTag();
	int tagB = nodeB->getTag();
	cocos2d::log("TagA: %d , TagB: %d ", tagA, tagB);

	/////////////////////////////////////////////////
	//GROUND COLLISION
	/////////////////////////////////////////////////
	if (tagA == Tag::T_Ground)
	{
		nodeB->setPhysicsBody(nullptr);
		cocos2d::log("Xoa body sau khi cham voi ground");
	}
	if (tagB == Tag::T_Ground)
	{
		nodeA->setPhysicsBody(nullptr);
		cocos2d::log("Xoa body sau khi cham voi ground");
	}
	
	/////////////////////////////////////////////////
	// VICTIM COLLISION
	/////////////////////////////////////////////////
	
	if (tagA == Tag::T_Victim && tagB == Tag::T_Bow)
	{
		
		nodeA->setTexture("img/victim/victim2.png");
		nodeB->setTexture("img/char/bodybow.png");
		nodeB->removeFromPhysicsWorld();
	}
	if (tagB == Tag::T_Victim && tagA == Tag::T_Bow)
	{
		
		nodeB->setTexture("img/victim/victim2.png");

		nodeA->setTexture("img/char/bodybow.png");
		nodeA->removeFromPhysicsWorld();

	}

	/////////////////////////////////////////////////
	// LINE COLLISION
	/////////////////////////////////////////////////

	if (tagA == Tag::T_Line && tagB == Tag::T_Bow)
	{
		jointLine->removeFormWorld();
		nodeA->removeFromPhysicsWorld();
		
		cocos2d::log("Va cham voi day, xoa body day");
		this->unschedule(schedule_selector(BowManPlayGameScene::bowRotateUpdate));
		for (int i = 0; i < bowArray.size(); i++)
		{
			cocos2d::log("%d", i);
			bowArray.at(i)->removeFromParentAndCleanup(true);
		}

		//setTouchEnabled(false);
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
		createLevelUpDialog();

	}
	if (tagB == Tag::T_Line && tagA == Tag::T_Bow)
	{
		jointLine->removeFormWorld();
		nodeB->removeFromPhysicsWorld();
		
		cocos2d::log("Va cham voi day , xoa body day");
		this->unschedule(schedule_selector(BowManPlayGameScene::bowRotateUpdate));
		for (int i = 0; i < bowArray.size() ; i++)
		{
			cocos2d::log("%d", i);
			bowArray.at(i)->removeFromParentAndCleanup(true);
		}

		//setTouchEnabled(false);
		Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
		createLevelUpDialog();
	}

	return true;
}


void BowManPlayGameScene::rebootCallback(Ref *pSEnder, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->replaceScene(BowManPlayGameScene::createScene());
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void BowManPlayGameScene::debugCallback(Ref *pSEnder, Widget::TouchEventType type){
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

void BowManPlayGameScene::createLevelUpDialog()
{
	/////////////////////////////////////////////////
	// LEVEL UP DIALOG
	/////////////////////////////////////////////////

	Sprite* levelupDialog = Sprite::create("img/dialog/levelup_dialog.png");
	levelupDialog->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	levelupDialog->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));

	this->addChild(levelupDialog, 99);

	/////////////////////////////////////////////////
	// BUTTON DIALOG
	/////////////////////////////////////////////////
	// Start Game
	Sprite* nextLevel1 = Sprite::create("img/button/next_right_icon1.png");
	Sprite* nextLevel2 = Sprite::create("img/button/next_right_icon2.png");

	MenuItemSprite* nextLevelBtn = MenuItemSprite::create(
		nextLevel1,
		nextLevel2,
		CC_CALLBACK_1(BowManPlayGameScene::nextLevelCallBack, this)
		);
	nextLevelBtn->setScale(2.0f);
	nextLevelBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	nextLevelBtn->setPosition(Vec2(
		WINSIZE.width / 2 - 50 - nextLevelBtn->getContentSize().width / 2,
		WINSIZE.height / 2 - 20
		));

	// Score Game
	Sprite* replay1 = Sprite::create("img/button/replay1.png");
	Sprite* replay2 = Sprite::create("img/button/replay2.png");

	MenuItemSprite* replayBtn = MenuItemSprite::create(
		replay1,
		replay2,
		CC_CALLBACK_1(BowManPlayGameScene::replayCallback, this)
		);
	replayBtn->setScale(2.0f);
	replayBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	replayBtn->setPosition(Vec2(
		WINSIZE.width / 2 + 50 + nextLevelBtn->getContentSize().width / 2, 
		WINSIZE.height / 2 - 20
		));

	Menu* levelupMenu = Menu::create(
		nextLevelBtn,
		replayBtn,
		NULL
		);
	levelupMenu->setPosition(Vec2::ZERO);

	this->addChild(levelupMenu, 99);

}



void BowManPlayGameScene::nextLevelCallBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(BowManLevelTwo::createScene());
}

void BowManPlayGameScene::replayCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(BowManPlayGameScene::createScene());
}

#include "bowman\BowManLevelTwo.h"

#define WINSIZE Director::getInstance()->getVisibleSize()
#define BOW_INIT_POS Point(480,120)
#define GROUND_HEIGHT 130


#define PI 3.141592653589793238462643383279502884L /* pi */

USING_NS_CC;


/////////////////////////////////////////////////
//USING CAMERA
/////////////////////////////////////////////////

Scene* BowManLevelTwo::createScene() {

	// Khai bao scene co gan thuoc tinh vat ly
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vect(0, -1000));
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	auto layer = BowManLevelTwo::create();
	layer->setWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;
}

bool BowManLevelTwo::init() {
	if (!Layer::init()) {
		return false;
	}

	return true;
}

void BowManLevelTwo::setWorld(PhysicsWorld *world){
	myWorld = world;
};


void BowManLevelTwo::onEnterTransitionDidFinish() {
	Layer::onEnter();

	createDebugButton();
	createBackground();
	createGround();

	/////////////////////////////////////////////////
	// BOWMAN BODY SPRITE
	/////////////////////////////////////////////////
	nodeBowMan = Node::create();
	nodeBowMan->setPosition(Vec2::ZERO);
	nodeBowMan->setTag(Tag::T_NodeBowMan);
	this->addChild(nodeBowMan , Z_Order::Z_NodeBowMan);

	auto nodeBMBody = PhysicsBody::createBox(Size(1, 1), PhysicsMaterial(0, 0, 0));
	nodeBowMan->setPhysicsBody(nodeBMBody);
	nodeBowMan->getPhysicsBody()->setDynamic(true);
	nodeBowMan->getPhysicsBody()->setGravityEnable(false);


	auto bowmanBodySprite = Sprite::create("img/bowman/bow_body.png");

	bowmanBodySprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bowmanBodySprite->setPosition(BOW_INIT_POS);
	nodeBowMan->addChild(bowmanBodySprite, Z_Order::Z_Bowman_Body);

	/////////////////////////////////////////////////
	// BOWMAN HEAD SPRITE
	/////////////////////////////////////////////////

	bowmanHeadSprite = Sprite::create("img/bowman/bow_head.png");
	bowmanHeadSprite->setTag(Tag::T_Bowman_Head);

	bowmanHeadSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	bowmanHeadSprite->setPosition(BOW_INIT_POS);
	nodeBowMan->addChild(bowmanHeadSprite, Z_Order::Z_Bowman_Head);

	/////////////////////////////////////////////////
	// NODE FATHER
	/////////////////////////////////////////////////
	nodeFather = Node::create();
	nodeFather->setPosition(Vec2::ZERO);
	nodeFather->setTag(Tag::T_NodeFather);
	this->addChild(nodeFather , Z_Order::Z_NodeFather);


	auto nodeFatherBody = PhysicsBody::createBox(Size(1, 1), PhysicsMaterial(0, 0, 0));
	nodeFather->setPhysicsBody(nodeFatherBody);
	nodeFather->getPhysicsBody()->setDynamic(true);
	nodeFather->getPhysicsBody()->setGravityEnable(false);

	/////////////////////////////////////////////////
	// BOX AND PYLON AND VICTIM
	/////////////////////////////////////////////////

	auto boxSprite = Sprite::create("img/char/box.png");
	boxSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	boxSprite->setPosition(Vec2(
		WINSIZE.width * 2 - 400 , // max *4
		GROUND_HEIGHT/2 + boxSprite->getContentSize().height / 2
		));
	nodeFather->addChild(boxSprite, Z_Order::Z_Bow);


	auto pylonSprite = Sprite::create("img/char/pylon.png");
	pylonSprite->setAnchorPoint(Vec2::ANCHOR_BOTTOM_RIGHT);
	pylonSprite->setPosition(Vec2(
		boxSprite->getPositionX() + boxSprite->getContentSize().width / 2 - 10, 
		boxSprite->getPositionY() + boxSprite->getContentSize().height / 2
		));
	nodeFather->addChild(pylonSprite, Z_Order::Z_Pylon);


	auto lineSprite = Sprite::create("img/char/line2.png");
	auto lineBody = PhysicsBody::createBox(
		Size(lineSprite->getContentSize().width , lineSprite->getContentSize().height ), //- 40
		PhysicsMaterial(0.0f ,0.0f ,0.0f )
		);
	lineBody->setDynamic(true);
	lineBody->setGravityEnable(false);
	lineBody->setContactTestBitmask(0x00000001);
	lineSprite->setPhysicsBody(lineBody);

	lineSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	lineSprite->setPosition(Vec2(
		pylonSprite->getPositionX() - pylonSprite->getContentSize().width + 20,
		pylonSprite->getPositionY() + pylonSprite->getContentSize().height - lineSprite->getContentSize().height / 2 - 34
		));
	lineSprite->setTag(Tag::T_Line);
	nodeFather->addChild(lineSprite, Z_Order::Z_Line);


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
		victimBody->setGravityEnable(false);
	}
	victimSprite->setPhysicsBody(victimBody);
	victimSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	victimSprite->setPosition(Vec2(
		lineSprite->getPositionX() - 5,
		lineSprite->getPositionY() - lineSprite->getContentSize().height / 2 - victimSprite->getContentSize().height / 2 + 15
		));

	victimSprite->setTag(Tag::T_Victim);
	nodeFather->addChild(victimSprite, Z_Order::Z_Victim);

	/////////////////////////////////////////////////
	// JOINT VICTIM AND LINE
	/////////////////////////////////////////////////

	jointLine = PhysicsJointPin::construct(lineBody, victimBody, lineSprite->getPosition() - Vec2(0, 70));
	jointLine->setCollisionEnable(false);
	jointLine->getBodyB()->setRotationEnable(false);
	myWorld->addJoint(jointLine);



	/////////////////////////////////////////////////
	// BOW NODE
	/////////////////////////////////////////////////

	nodeBow = Node::create();
	nodeBow->setPosition(Vec2::ZERO);
	nodeBow->setTag(Tag::T_NodeBow);
	this->addChild(nodeBow , 99);

	auto nodeBowBody = PhysicsBody::createBox(Size(10, 10), PhysicsMaterial(0, 0, 0));
	nodeBow->setPhysicsBody(nodeBowBody);
	nodeBow->getPhysicsBody()->setDynamic(true);
	nodeBow->getPhysicsBody()->setGravityEnable(false);

	
	/////////////////////////////////////////////////
	// SCHEDULE BOW ROTATE
	/////////////////////////////////////////////////
	
	// Su dung ham update de check goc bay cua mui ten lien tuc
	this->schedule(schedule_selector(BowManLevelTwo::bowRotateUpdate), 0.01f);


	/////////////////////////////////////////////////
	// TOUCH EVENT
	/////////////////////////////////////////////////
	auto touchListener = EventListenerTouchOneByOne::create();
	touchListener->onTouchBegan = CC_CALLBACK_2(BowManLevelTwo::onTouchBegan, this);
	touchListener->onTouchMoved = CC_CALLBACK_2(BowManLevelTwo::onTouchMoved, this);
	touchListener->onTouchEnded = CC_CALLBACK_2(BowManLevelTwo::onTouchEnded, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);


	/////////////////////////////////////////////////
	// COLLISION EVENT
	/////////////////////////////////////////////////

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(BowManLevelTwo::onContactBegin, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
}

void BowManLevelTwo::createGround()
{
	auto groundNode = Node::create();

	auto groundBody = PhysicsBody::createEdgeBox(
		Size(WINSIZE.width * 16, GROUND_HEIGHT), 
		PhysicsMaterial(1.0f , 0.0f , 0.0f)
		);
	groundBody->setDynamic(false);
	groundBody->setGravityEnable(false);
	groundBody->setContactTestBitmask(0x00000001);

	groundNode->setPhysicsBody(groundBody);
	groundNode->setAnchorPoint(Vec2::ZERO);
	groundNode->setPosition(Vec2::ZERO);
	groundNode->setTag(Tag::T_Ground);
	this->addChild(groundNode);
}


void BowManLevelTwo::createBackground()
{
	/////////////////////////////////////////////////
	// BACKGROUND GAME
	/////////////////////////////////////////////////
	nodeBackground = Node::create();
	nodeBackground->setPosition(Vec2::ZERO);
	nodeBackground->setTag(Tag::T_NodeBackground);
	this->addChild(nodeBackground, Z_Order::Z_NodeBackground);

	auto nodeBgBody = PhysicsBody::createBox(Size(1, 1), PhysicsMaterial(0, 0, 0));
	nodeBackground->setPhysicsBody(nodeBgBody);
	nodeBackground->getPhysicsBody()->setDynamic(true);
	nodeBackground->getPhysicsBody()->setGravityEnable(false);


	auto background = Sprite::create("img/background/bglv3.png");
	// Tinh theo winsize
	float scaleX = float(WINSIZE.width * 4 / background->getContentSize().width);
	float scaleY = float(WINSIZE.height / background->getContentSize().height);

	background->setScaleX(scaleX); // phong to anh co chieu dai bang 2 lan winsize
	background->setScaleY(scaleY); // phong to anh co chieu cao bang winsize
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);
	background->setTag(Tag::T_Background);
	nodeBackground->addChild(background, Z_Order::Z_Background);

}



Sprite* BowManLevelTwo::createBow()
{
	auto bowSprite = Sprite::create("img/char/bow.png");

	// Thiet lap khung vat ly cho bow
	PhysicsBody* bowBody = PhysicsBody::createBox(
		Size(40, 10),
		PhysicsMaterial(100.0f , 1.0f , 1.0f)
		);

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

void BowManLevelTwo::createArrowSprite()
{
	/////////////////////////////////////////////////
	// ARROW SPRITE
	/////////////////////////////////////////////////

	Sprite* arrowSprite = Sprite::create("img/char/arrow1.png");
	arrowSprite->setTag(Tag::T_Arrow);

	arrowSprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
	arrowSprite->setPosition(Vec2(
		bowmanHeadSprite->getContentSize().width,
		bowmanHeadSprite->getContentSize().height / 2 + 13
		));

	bowmanHeadSprite->addChild(arrowSprite);
}


void BowManLevelTwo::bowRotateUpdate(float dt)
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

bool BowManLevelTwo::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::log("Touch Begin");

	/////////////////////////////////////////////////
	// TOUCH BEGAN
	/////////////////////////////////////////////////
	bool res = false;

	/////////////////////////////////////////////////
	// BOW SPRITE
	/////////////////////////////////////////////////

	Sprite* arrowSprite = (Sprite*)bowmanHeadSprite->getChildByTag(Tag::T_Arrow);


	if (bowmanHeadSprite != nullptr && bowmanHeadSprite->getBoundingBox().containsPoint(touch->getLocation()))
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

	
		nodeBow->setPosition(Vec2(0,0));

		bowArray.back()->setPosition(Vec2(
			BOW_INIT_POS.x + bowmanHeadSprite->getContentSize().width / 2 + bowArray.back()->getContentSize().width / 2 - 60,
			BOW_INIT_POS.y + 13
			));
		log("bowX = %f , bowY = %f ", BOW_INIT_POS.x + bowmanHeadSprite->getContentSize().width / 2 + bowArray.back()->getContentSize().width / 2 - 60, BOW_INIT_POS.y + 13);
		cocos2d::log("Tao bow");
		nodeBow->addChild(bowArray.back(), Z_Order::Z_Bow);
		

		touchBeginPosition = touch->getLocation();
		res = true;
	}

	return res; // res = true thi moi chuyen qua touch move,touch end
}

void BowManLevelTwo::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::log("Touch Move");

	/////////////////////////////////////////////////
	// TOUCH MOVE AND ROTATE BOWMAN,ARROW
	/////////////////////////////////////////////////

	auto bowmanHeadSprite = (Sprite*)nodeBowMan->getChildByTag(Tag::T_Bowman_Head);
	Sprite* arrowSprite = (Sprite*)bowmanHeadSprite->getChildByTag(Tag::T_Arrow);

	touchEndMovePosition = touch->getLocation();

	// Vector tao boi diem touch dau va diem touch cuoi
	Vec2 vectorPull = Vec2(); // Vector keo
	vectorPull = touchEndMovePosition - touchBeginPosition;

	angle = CC_RADIANS_TO_DEGREES(vectorPull.getAngle()); // Goc giua 2 vector: Ox va vectorPull

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

void BowManLevelTwo::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event)
{
	cocos2d::log("Touch end");

	/////////////////////////////////////////////////
	// TOUCH END
	/////////////////////////////////////////////////
	
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
	// CAMERA FOLLOW BOW
	/////////////////////////////////////////////////
	log("bowX = %f , bowY = %f", bowArray.back()->getPositionX(), bowArray.back()->getPositionY());

	camera = CustomFollow::create(
		bowArray.back(),
		CustomFollowType::kCustomFollowXOnly
		);
	camera->retain();
	nodeBow->runAction(camera);

	/////////////////////////////////////////////////
	// SCHEDULE BACKGROUND UPDATE
	/////////////////////////////////////////////////

	// Ham xu ly khi ten duoc ban ra.
	this->schedule(schedule_selector(BowManLevelTwo::backgroundUpdate), 0.01f);


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

// Background di chuyen theo mui ten khi ban
void BowManLevelTwo::backgroundUpdate(float dt)
{
	//nodeBackground->setPositionX( nodeBackground->getPositionX() + velocity.x * dt * (-1));
	
	auto lineSprite = (Sprite*)nodeFather->getChildByTag(Tag::T_Line);
	auto victimSprite = (Sprite*)nodeFather->getChildByTag(Tag::T_Victim);


	if (bowArray.back()->getPhysicsBody() != nullptr)
	{
		Vec2 velocity = bowArray.back()->getPhysicsBody()->getVelocity();
		nodeBackground->getPhysicsBody()->setVelocity(Vect(velocity.x * (-1), 0));
		nodeFather->getPhysicsBody()->setVelocity(Vect(velocity.x * (-1), 0));
		lineSprite->getPhysicsBody()->setVelocity(Vect(velocity.x * (-1), 0));
		victimSprite->getPhysicsBody()->setVelocity(Vect(velocity.x * (-1), 0));
		nodeBowMan->getPhysicsBody()->setVelocity(Vect(velocity.x * (-1), 0));

	}
	else
	{
		nodeBackground->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBowMan->getPhysicsBody()->setVelocity(Vect(0, 0));
		lineSprite->getPhysicsBody()->setVelocity(Vect(0, 0));
		victimSprite->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeFather->getPhysicsBody()->setVelocity(Vect(0, 0));
	}
	
}

bool BowManLevelTwo::onContactBegin(PhysicsContact& contact)
{
	cocos2d::log("Va cham");

	auto victimSprite = (Sprite*)nodeFather->getChildByTag(Tag::T_Victim);

	/////////////////////////////////////////////////
	// KHAI BAO
	/////////////////////////////////////////////////
	auto nodeA = (Sprite*)contact.getShapeA()->getBody()->getNode();
	auto nodeB = (Sprite*)contact.getShapeB()->getBody()->getNode();

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
	if (tagA == Tag::T_Ground && tagB == Tag::T_Bow)
	{
		nodeB->setPhysicsBody(nullptr);
		nodeBackground->setPosition(Vec2(0, 0));

		cocos2d::log("Xoa body sau khi cham voi ground");
	}
	if (tagB == Tag::T_Ground && tagA == Tag::T_Bow)
	{
		nodeA->setPhysicsBody(nullptr);
		nodeBackground->setPosition(Vec2(0, 0));

		cocos2d::log("Xoa body sau khi cham voi ground");
	}

	if (tagA == Tag::T_Ground && tagB == Tag::T_Victim)
	{
		nodeB->setPhysicsBody(nullptr);

		nodeBackground->setPosition(Vec2(0, 0));

		// Sau khi touch end thi ko cho tap nua neu chua xay ra va cham
		//Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
		//Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
		cocos2d::log("Xoa body sau khi cham voi ground");
	}

	if (tagB == Tag::T_Ground && tagA == Tag::T_Victim)
	{
		nodeA->setPhysicsBody(nullptr);

		nodeBackground->setPosition(Vec2(0, 0));

		// Sau khi touch end thi ko cho tap nua neu chua xay ra va cham
		//Director::getInstance()->getEventDispatcher()->pauseEventListenersForTarget(this);
		//Director::getInstance()->getEventDispatcher()->resumeEventListenersForTarget(this);
		cocos2d::log("Xoa body sau khi cham voi ground");
	}

	/////////////////////////////////////////////////
	// VICTIM COLLISION
	/////////////////////////////////////////////////

	if (tagA == Tag::T_Victim && tagB == Tag::T_Bow)
	{
		this->unschedule(schedule_selector(BowManLevelTwo::backgroundUpdate));

		nodeBackground->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBowMan->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBow->getPhysicsBody()->setVelocity(Vect(0, 0));
		victimSprite->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeFather->getPhysicsBody()->setVelocity(Vect(0, 0));

		nodeBow->stopAction(camera);

		nodeA->setTexture("img/victim/victim2.png");
		nodeB->setTexture("img/char/bodybow.png");
		
		nodeB->removeFromPhysicsWorld();
	}
	if (tagB == Tag::T_Victim && tagA == Tag::T_Bow)
	{
		this->unschedule(schedule_selector(BowManLevelTwo::backgroundUpdate));

		nodeBackground->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBowMan->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBow->getPhysicsBody()->setVelocity(Vect(0, 0));
		victimSprite->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeFather->getPhysicsBody()->setVelocity(Vect(0, 0));

		nodeBow->stopAction(camera);

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
		
		victimSprite->getPhysicsBody()->setGravityEnable(true);

		cocos2d::log("Va cham voi day, xoa body day");
		this->unschedule(schedule_selector(BowManLevelTwo::bowRotateUpdate));
		this->unschedule(schedule_selector(BowManLevelTwo::backgroundUpdate));

		nodeBackground->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBowMan->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBow->getPhysicsBody()->setVelocity(Vect(0, 0));
		victimSprite->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeFather->getPhysicsBody()->setVelocity(Vect(0, 0));



		cocos2d::log("Xoa cac mui ten truoc do");

		nodeBow->stopAction(camera);
		for (int i = 0; i < bowArray.size(); i++)
		{
			bowArray.at(i)->removeFromParentAndCleanup(true);
		}

		createLevelUpDialog();

	}
	if (tagB == Tag::T_Line && tagA == Tag::T_Bow)
	{
		jointLine->removeFormWorld();
		nodeB->removeFromPhysicsWorld();

		victimSprite->getPhysicsBody()->setGravityEnable(true);

		cocos2d::log("Va cham voi day , xoa body day");
		this->unschedule(schedule_selector(BowManLevelTwo::bowRotateUpdate));
		this->unschedule(schedule_selector(BowManLevelTwo::backgroundUpdate));


		nodeBackground->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBowMan->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeBow->getPhysicsBody()->setVelocity(Vect(0, 0));
		victimSprite->getPhysicsBody()->setVelocity(Vect(0, 0));
		nodeFather->getPhysicsBody()->setVelocity(Vect(0, 0));



		cocos2d::log("Xoa cac mui ten truoc do");
		nodeBow->stopAction(camera);
		for (int i = 0; i < bowArray.size(); i++)
		{
			bowArray.at(i)->removeFromParentAndCleanup(true);
		}

		createLevelUpDialog();
	}

	return true;
}


void BowManLevelTwo::createLevelUpDialog()
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
		CC_CALLBACK_1(BowManLevelTwo::nextLevelCallBack, this)
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
		CC_CALLBACK_1(BowManLevelTwo::replayCallback, this)
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

void BowManLevelTwo::nextLevelCallBack(Ref* pSender)
{
	Director::getInstance()->replaceScene(BowManMenuScene::createScene());
}

void BowManLevelTwo::replayCallback(Ref* pSender)
{
	Director::getInstance()->replaceScene(BowManLevelTwo::createScene());
}




void BowManLevelTwo::createDebugButton()
{
	/////////////////////////////////////////////////
	// DEBUG BUTTON
	/////////////////////////////////////////////////

	auto restart = Button::create();
	restart->loadTextureNormal("CloseNormal.png");
	restart->setPosition(Vec2(WINSIZE.width - 40, WINSIZE.height - 40));
	restart->addTouchEventListener(CC_CALLBACK_2(BowManLevelTwo::rebootCallback, this));
	this->addChild(restart, 99);

	auto debug = Button::create();
	debug->loadTextureNormal("CloseNormal.png");
	debug->setPosition(Vec2(WINSIZE.width - 120, WINSIZE.height - 40));
	debug->addTouchEventListener(CC_CALLBACK_2(BowManLevelTwo::debugCallback, this));
	this->addChild(debug, 99);
}


void BowManLevelTwo::rebootCallback(Ref *pSEnder, Widget::TouchEventType type){
	switch (type)
	{
	case cocos2d::ui::Widget::TouchEventType::BEGAN:
		break;
	case cocos2d::ui::Widget::TouchEventType::MOVED:
		break;
	case cocos2d::ui::Widget::TouchEventType::ENDED:
	{
		Director::getInstance()->replaceScene(BowManLevelTwo::createScene());
		break;
	}
	case cocos2d::ui::Widget::TouchEventType::CANCELED:
		break;
	default:
		break;
	}
}
void BowManLevelTwo::debugCallback(Ref *pSEnder, Widget::TouchEventType type){
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

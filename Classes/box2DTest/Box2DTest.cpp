/*
 * Box2DTest.cpp
 *
 *  Created on: 2015/02/06
 *      Author: chu
 */

#include "box2DTest\Box2DTest.h"

// Vi box2D su dung don vi mm nen ta phai chuyen tu pixel sang mm
#define SCALE_RATIO 3.2

USING_NS_CC;

Scene* Box2DTest::createScene() {

	auto scene = Scene::create();
	auto layer = Box2DTest::create();

	scene->addChild(layer);

	return scene;
}

bool Box2DTest::init() {
	if (!Layer::init()) {
		return false;
	}

	Size visbleSize = Director::getInstance()->getVisibleSize();

	////////////////////////////////////////////////////////////////////////////////////
	// Phan khoi tao
	////////////////////////////////////////////////////////////////////////////////////

	// Khoi tao khong gian vat ly voi Box2D
	
	b2Vec2 gravity = b2Vec2(0.0f, -10.0f); // Khoi tao vector gia toc cho qua bong va huong thang xuong dat vi truc y huong len tren
	world = new b2World(gravity); // khoi tao 1 the gioi vat ly voi vector gia toc
	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);
	cocos2d::log(" Hinh thanh khong gian vat ly box2D ");

	// Khoi tao doi tuong ball

	dragOffsetStartX = 0;
	dragOffsetStartY = 0;
	dragOffsetEndX = 0;
	dragOffsetEndY = 0;
	existBall = false;
	ballX = 500;
	ballY = 200;
	powerMultiplier = 10;

	ball = Sprite::create("box2dtest_img/ball2.png");
	ball->setPosition(Vec2(ballX,  ballY));
	this->addChild(ball);
	
	cocos2d::log("Khoi tao doi tuong Ball ");

	// Dung khung bao quanh 3 phia man hinh
	addWall(visbleSize.width , 10 , visbleSize.width/2 , 0); // San nha
	addWall(10 , visbleSize.height , 0  , visbleSize.height/2); // Trai
	addWall(10 , visbleSize.height , visbleSize.width , visbleSize.height/2); // Phai


	for (int i = 0; i < 31; i++)
	{
		points[i] = Sprite::create("box2dtest_img/dot.png");
		this->addChild(points[i]);
	}


	// Bat su kien touch man hinh
	auto listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);

	listener->onTouchBegan = CC_CALLBACK_2(Box2DTest::onTouchBegan , this);
	listener->onTouchMoved = CC_CALLBACK_2(Box2DTest::onTouchMoved , this);
	listener->onTouchEnded = CC_CALLBACK_2(Box2DTest::onTouchEnded , this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener , this);


	scheduleUpdate();

	return true;
}

void Box2DTest::update(float dt){
   int positionIterations = 10;  
   int velocityIterations = 10;
   
   deltaTime = dt;
   world->Step(dt, velocityIterations, positionIterations);  
   for (b2Body *body = world->GetBodyList(); body != NULL; body = body->GetNext())   
     if (body->GetUserData()) 
     {  
       Sprite *sprite = (Sprite *) body->GetUserData();  
       sprite->setPosition(Vec2(body->GetPosition().x * SCALE_RATIO,body->GetPosition().y * SCALE_RATIO));  
       sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(body->GetAngle())); 
     }  
    world->ClearForces();
    world->DrawDebugData();       
 
}  

// Khoi tao khung vat ly box2d cho wall
void Box2DTest::addWall(float w , float h , float px , float py)
{
	b2PolygonShape floorShape; // Hinh khoi cua body
	floorShape.SetAsBox(w/SCALE_RATIO , h/SCALE_RATIO);

	b2FixtureDef floorFixture; // Dinh nghia cac thuoc tinh vat ly

	floorFixture.density = 0; // trong luong
	floorFixture.friction = 10; // mat sat
	floorFixture.restitution = 0.5f; // dan hoi
	floorFixture.shape = &floorShape; // hinh dang,tro vao floorShape

	b2BodyDef floorBodyDef;
	floorBodyDef.position.Set(px/SCALE_RATIO , py/SCALE_RATIO);

	b2Body* floorBody = world->CreateBody(&floorBodyDef);
	floorBody->CreateFixture(&floorFixture);
}


// Tao hinh dang va co the body cho ball
void Box2DTest::defineBall()
{
	// Tao hinh dang cho ball(shape)
	bodyShape.m_radius = 45/SCALE_RATIO;
	fixtureDef.density = 10;
	fixtureDef.restitution = 0.6;
	fixtureDef.friction = 0.8;
	fixtureDef.shape = &bodyShape;
	
	// Tao 1 co the cho ball(body)
	bodyDef.type = b2_dynamicBody;
	bodyDef.userData = ball;
	bodyDef.position.Set(ball->getPosition().x / SCALE_RATIO , ball->getPosition().y / SCALE_RATIO);

	ballBody = world->CreateBody(&bodyDef);
	ballBody->CreateFixture(&fixtureDef);
	ballBody->SetGravityScale(10);

}

bool Box2DTest::onTouchBegan(Touch* touch , Event* event)
{
	// Luu toa do diem touch dau tien
	dragOffsetStartX = touch->getLocation().x;
	dragOffsetStartY = touch->getLocation().y;

	Vec2 touchLocation = touch->getLocation();// Lay toa do diem touch

	// Luu toa do diem touch lai
	ballX = touchLocation.x;
	ballY = touchLocation.y;

	// Kiem tra diem touch co qua bong chua, neu chua co thi xoa body bong da tao o ham defineBall()
	if(existBall)
	{
		world->DestroyBody(ballBody);
	}

	// Va dat lai no tai vi tri touch
	ball->setPosition(Point(ballX , ballY));

	return true;
}

void Box2DTest::onTouchMoved(Touch* touch , Event* event)
{
	Vec2 touchLocation = touch->getLocation();
	
	// Luu lai diem cuoi
	dragOffsetEndX = touchLocation.x;
	dragOffsetEndY = touchLocation.y;

	// Khoang di chuyen cua bong
	float dragDistanceX = dragOffsetStartX - dragOffsetEndX;
	float dragDistanceY = dragOffsetStartY - dragOffsetEndY;

	// Goi ham mo phong duong di cua bong
	Box2DTest::simulateTrajectory(b2Vec2(
		(dragDistanceX * powerMultiplier)/SCALE_RATIO ,
		(dragDistanceY * powerMultiplier)/SCALE_RATIO
		));

}
void Box2DTest::onTouchEnded(Touch* touch , Event* event)
{
	existBall = true;
	Box2DTest::defineBall(); // Tao body qua bong tai diem touch cuoi
	Vec2 touchLocation = touch->getLocation(); // Lay diem touch

	// Luu diem touch cuoi
	dragOffsetEndX = touchLocation.x;
	dragOffsetEndY = touchLocation.y;

	// Khoang di chuyen cua bong
	float dragDistanceX = dragOffsetStartX - dragOffsetEndX;
	float dragDistanceY = dragOffsetStartY - dragOffsetEndY;

	// Tao di chuyen cho qua bong
	ballBody->SetLinearVelocity(b2Vec2(
		(dragDistanceX * powerMultiplier) / SCALE_RATIO ,
		(dragDistanceY * powerMultiplier) / SCALE_RATIO
		));

}

void Box2DTest::simulateTrajectory(b2Vec2 coord)
{
	// Dinh nghia physics body cho bong
	Box2DTest::defineBall();

	// Tao 1 chuyen dong cho body voi 1 van toc khong doi co phuong va do lon = vector truyen vao
	ballBody->SetLinearVelocity(b2Vec2(coord.x , coord.y));

	for (int i = 1 ; i < 31; i++)
	{
		world->Step(deltaTime , 10 , 10);
		points[i]->setPosition(Vec2(ballBody->GetPosition().x * SCALE_RATIO , ballBody->GetPosition().y * SCALE_RATIO));
		world->ClearForces();
	}
	world->DestroyBody(ballBody);
}
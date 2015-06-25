#include "box2DTest\Box2DExample.h"

Box2DExample::Box2DExample()
{
}

Box2DExample::~Box2DExample()
{
}

Scene* Box2DExample::createScene()
{
	auto scene = Scene::create();
	auto layer = Box2DExample::create();

	scene->addChild(layer);

	return scene;
}

bool Box2DExample::init()
{

	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	b2Vec2 gravity; // Toa do xac dinh trong luc trong moi truong vat ly
	gravity.Set(0.0f , -10.0f); // Huong xuong duoi

	auto world = new b2World(gravity);

	world->SetAllowSleeping(true);
	world->SetContinuousPhysics(true);




	LabelBMFont* bmpFont1 = LabelBMFont::create("ワンダー\nプラネット", "box2dtest_img/123.fnt");
	LabelBMFont* bmpFont2 = LabelBMFont::create("ワンワンダー", "box2dtest_img/123.fnt");

	bmpFont1->setPosition(Vec2(visibleSize.width * 0.75 , visibleSize.height * 0.75));
	bmpFont2->setPosition(Vec2(visibleSize.width * 0.25 , visibleSize.height * 0.25));

	this->addChild(bmpFont1);
	this->addChild(bmpFont2);


	return true;
}

void Box2DExample::initPhysics()
{
	
}
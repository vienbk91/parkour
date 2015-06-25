#include "bowman\BowManMainScene.h"

USING_NS_CC;

using namespace std;
using namespace cocos2d;


Scene* BowManMainScene::createScene()
{
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(1280, 720, ResolutionPolicy::SHOW_ALL);

	auto scene = Scene::create();
	auto layer = BowManMainScene::create();

	scene->addChild(layer);

	return scene;
}

bool BowManMainScene::init()
{
	if( !Layer::init()){
		return false;
	}

	

	Size visibleSize = Director::getInstance()->getVisibleSize(); 


	// Tạo background
	Sprite* gunboundBG = Sprite::create("img/background/bg4.png");

	gunboundBG->setScaleX(float(visibleSize.width / gunboundBG->getContentSize().width));
	gunboundBG->setScaleY(float(visibleSize.height / gunboundBG->getContentSize().height));
	gunboundBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	gunboundBG->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));

	this->addChild(gunboundBG);

	cocos2d::log("Auto move scene using schedule with delay time 1.0f");
	scheduleOnce(schedule_selector(BowManMainScene::loadingCallBack) , 1.0f);

	return true;
}

void BowManMainScene::loadingCallBack(float dt){

	// Thực hiện chuyển trang sau thời gian 5s
	auto bowmanMenu = BowManMenuScene::createScene();
	// Sử dụng hiệu ứng effect khi chuyển trang
	TransitionScene *moveScene = TransitionFade::create(4.0f , bowmanMenu);
	Director::getInstance()->replaceScene(moveScene);

	this->unschedule(schedule_selector(BowManMainScene::loadingCallBack));

	cocos2d::log("Remove schedule");


	return;
}
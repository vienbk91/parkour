#include "LoadingScene.h"

#define T_TIMER 100
#define T_PRECENT 20

USING_NS_CC;

Scene* LoadingScene::createScene()
{

    auto scene = Scene::create();
    auto layer = LoadingScene::create();
    scene->addChild(layer);

    return scene;
}

bool LoadingScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
	Size size = Director::getInstance()->getVisibleSize();

	Sprite* pBar = Sprite::create("uitest_img/progressBar.png");
	pBar->setScaleX(0.75f);

	ProgressTimer* pTimer = ProgressTimer::create(pBar);

	pTimer->setPercentage(0);// Bat dau voi 0%

	pTimer->setType(ProgressTimerType::BAR); // Dinh dang load cho timer dang bar
	//pTimer->setType(ProgressTimerType::RADIAL); // Dinh dang load cho timer dang radial tron

	pTimer->setBarChangeRate(Vec2(1 , 0)); // Xet huong mo rong cua bar

	pTimer->setMidpoint(Vec2(0,0)); // Xet diem tieu chuan cua timer

	// Thiet lap vi tri cho timer
	pTimer->setPosition(size.width /2 , size.height / 2);
	pTimer->setTag(T_TIMER);

	addChild(pTimer);

	// Tao text hien thi thong bao chay progressbar

	Label* precentTxt = Label::createWithTTF("" , "Arial" , 35);

	precentTxt->setPosition(Vec2(pTimer->getPositionX() , pTimer->getPositionY() + 50));

	precentTxt->setTag(T_PRECENT);

	addChild(precentTxt);



	//this->scheduleUpdate();
	this->schedule(schedule_selector(LoadingScene::update) , 0.01f);
    
    return true;
}

void LoadingScene::update(float delta){

	// Tang 1% trong moi lan update cua schedile
	ProgressTimer* timer = (ProgressTimer*)this->getChildByTag(T_TIMER);
	int precent = timer->getPercentage();

	timer->setPercentage(precent + 1);

	// Thay doi text hien thi

	Label* precentTxt = (Label*)this->getChildByTag(T_PRECENT);
	precentTxt->setString(String::createWithFormat("%d%%", precent)->getCString());

	if(precent >= 100){
		this->unscheduleUpdate();
		auto menuScene = ScrollViewScene::createScene();
		Director::getInstance()->replaceScene(menuScene);
	}

}

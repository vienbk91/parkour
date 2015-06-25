#include "bowman\BowManSelectMap.h"


#define WINSIZE Director::getInstance()->getVisibleSize()
#define MAP_W_SIZE 340 // Width
#define MAP_H_SIZE 410 // Height
#define MENU_W_SIZE 860
#define MENU_H_SIZE 500


USING_NS_CC;
using namespace ui;


Scene* BowManSelectMap::createScene()
{
	auto scene = Scene::create();

	auto layer = BowManSelectMap::create();

	scene->addChild(layer);

	return scene;
}

bool BowManSelectMap::init()
{
	if (!Layer::init())
	{
		return false;
	}


	// Khoi tao background cho menu_select_map
	Sprite* background = Sprite::create("img/background/bg_select_map.png");
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));
	background->setScale(float(WINSIZE.width / background->getContentSize().width), float(WINSIZE.height / background->getContentSize().height));
	this->addChild(background);


	///////////////////////////////////////////////////////////
	// ScrollView
	///////////////////////////////////////////////////////////

	scrollMenu = ui::ScrollView::create();
	scrollMenu->setBackGroundColor(Color3B::GREEN);
	scrollMenu->setOpacity(10); // set trong suot
	scrollMenu->setBackGroundColorType(ui::Layout::BackGroundColorType::NONE);
	scrollMenu->setContentSize(Size(WINSIZE.width - 100, WINSIZE.height - 120));
	cocos2d::log("sc_w : %f , sc_h : %f ", WINSIZE.width - 100, WINSIZE.height - 140);
	scrollMenu->setBounceEnabled(false);
	scrollMenu->setDirection(ui::ScrollView::Direction::HORIZONTAL); // Scroll se chuyen dong theo chieu ngang
	scrollMenu->setAnchorPoint(Vec2::ANCHOR_MIDDLE); // Dat scroll vao giua man hinh
	scrollMenu->setPosition(Vec2(WINSIZE.width / 2, WINSIZE.height / 2));

	this->addChild(scrollMenu);

	// Add 4 map vao scrollView

	///////////////////////////////////////////////////////////
	// Map1 
	///////////////////////////////////////////////////////////

	Sprite* map1Sprite1 = Sprite::create("img/map/map1.png");
	Sprite* map1Sprite2 = Sprite::create("img/map/map1_click.png");
	MenuItemSprite* map1Btn = MenuItemSprite::create(map1Sprite1, map1Sprite2, CC_CALLBACK_1(BowManSelectMap::map1Callback, this));
	map1Btn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	map1Btn->setPosition(Vec2(scrollMenu->getContentSize().width/4 , scrollMenu->getContentSize().height / 2));

	Menu* menu1 = Menu::create(map1Btn, NULL);
	menu1->setContentSize(Size(scrollMenu->getContentSize().width / 2, scrollMenu->getContentSize().height));
	menu1->setAnchorPoint(Vec2::ZERO);
	menu1->setPosition(Vec2::ZERO);
	scrollMenu->addChild(menu1);

	///////////////////////////////////////////////////////////
	// Map2_ lock
	///////////////////////////////////////////////////////////

	Sprite* map2Sprite1 = Sprite::create("img/map/map2_lock.png");
	Sprite* map2Sprite2 = Sprite::create("img/map/map2_lock.png");
	MenuItemSprite* map2Btn = MenuItemSprite::create(map2Sprite1, map2Sprite2, CC_CALLBACK_1(BowManSelectMap::map2Callback, this));
	// Vị trí của map2Btn phụ thuộc vào cha nó là Menu, nên gần hay xa map1Btn còn phụ thuộc vào Menu
	// Nếu xét PP như dưới thì map2Btn nằm ngay đầu của Menu và còn lần 1 đoạn sang menu1
	map2Btn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	map2Btn->setPosition(Vec2(scrollMenu->getContentSize().width / 4, scrollMenu->getContentSize().height / 2));

	Menu* menu2 = Menu::create(map2Btn, NULL);
	menu2->setContentSize(Size(scrollMenu->getContentSize().width / 2, scrollMenu->getContentSize().height));
	menu2->setAnchorPoint(Vec2::ZERO);
	menu2->setPosition(Vec2(menu1->getContentSize().width , 0));
	scrollMenu->addChild(menu2);



	///////////////////////////////////////////////////////////
	// Map3_ lock
	///////////////////////////////////////////////////////////

	Sprite* map3Sprite1 = Sprite::create("img/map/map3_lock.png");
	Sprite* map3Sprite2 = Sprite::create("img/map/map3_lock.png");
	
	MenuItemSprite* map3Btn = MenuItemSprite::create(map3Sprite1, map3Sprite2, CC_CALLBACK_1(BowManSelectMap::map3Callback, this));
	map3Btn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	map3Btn->setPosition(Vec2(Vec2(scrollMenu->getContentSize().width / 4, scrollMenu->getContentSize().height / 2)));

	Menu* menu3 = Menu::create(map3Btn, NULL);
	menu3->setContentSize(Size(scrollMenu->getContentSize().width/2, scrollMenu->getContentSize().height));
	menu3->setAnchorPoint(Vec2::ZERO);
	menu3->setPosition(Vec2(menu1->getContentSize().width + menu2->getContentSize().width , 0));
	scrollMenu->addChild(menu3);

	///////////////////////////////////////////////////////////
	// Map4_ lock
	///////////////////////////////////////////////////////////

	Sprite* map4Sprite1 = Sprite::create("img/map/map4_lock.png");
	Sprite* map4Sprite2 = Sprite::create("img/map/map4_lock.png");
	MenuItemSprite* map4Btn = MenuItemSprite::create(map4Sprite1, map4Sprite2, CC_CALLBACK_1(BowManSelectMap::map4Callback, this));
	map4Btn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	map4Btn->setPosition(Vec2(scrollMenu->getContentSize().width/4 , scrollMenu->getContentSize().height / 2));

	Menu* menu4 = Menu::create(map4Btn, NULL);
	menu4->setContentSize(Size(scrollMenu->getContentSize().width/2  ,scrollMenu->getContentSize().height));
	menu4->setAnchorPoint(Vec2::ZERO);
	menu4->setPosition(Vec2(menu1->getContentSize().width + menu2->getContentSize().width + menu3->getContentSize().width , 0));
	scrollMenu->addChild(menu4);

	// Thiet lap kich thuoc cua scroll lai 1 lan nua
	// inner : noi bo , ben trong
	float innerHeight = scrollMenu->getContentSize().height;
	float innerWidth = menu4->getPositionX() + scrollMenu->getContentSize().width/2; // Vi do rong cua moi menu la 1/2 scroll va diem dat cua no la (0,0)

	scrollMenu->setInnerContainerSize(Size(innerWidth, innerHeight));


	///////////////////////////////////////////////////////////
	// Tao checkbox
	///////////////////////////////////////////////////////////

	Sprite* radioState1 = Sprite::create("img/button/raido_box2.png"); // check
	radioState1->setScale(0.2f);
	Sprite* radioState2 = Sprite::create("img/button/raido_box1.png"); // not check
	radioState2->setScale(0.2f);

	radioState1->setPosition(Vec2(WINSIZE.width / 2 - 15 , 20));
	radioState2->setPosition(Vec2(WINSIZE.width / 2 + 15 , 20));

	this->addChild(radioState1);
	this->addChild(radioState2);

	///////////////////////////////////////////////////////////
	// Xu ly doi check box neu scroll duoc di chuyen
	///////////////////////////////////////////////////////////

	scheduleUpdate();

	return true;

}


void BowManSelectMap::update(float dt)
{
	// Xu ly check toa do cua scroll de thay doi radiobox
	//float x = scrollMenu->getInnerContainer()->getPositionX();
}


void BowManSelectMap::map1Callback(Ref* pSender)
{
	cocos2d::log("Map1 Callback - chuyen den playGame");

	auto playGame = BowManPlayGameScene::createScene();
	Director::getInstance()->replaceScene(playGame);

}

void BowManSelectMap::map2Callback(Ref* pSender)
{
	cocos2d::log("Map2 Callback");
}

void BowManSelectMap::map3Callback(Ref* pSender)
{
	cocos2d::log("Map3 Callback");
}

void BowManSelectMap::map4Callback(Ref* pSender)
{
	cocos2d::log("Map4 Callback");
}
/*
 * BowManMenuScene.cpp
 *
 *  Created on: 2015/02/05
 *      Author: chu
 */

#include "bowman\BowManMenuScene.h"


Scene* BowManMenuScene::createScene()
{
	auto scene = Scene::create();

	auto layer = BowManMenuScene::create();

	scene->addChild(layer);

	return scene;
}


bool BowManMenuScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::log("Welcome to new BowManMenuScene");

	//  Tạo background
	Sprite* background = Sprite::create("img/background/gunbound_bg1.png");
	background->setScaleX(float(visibleSize.width / background->getContentSize().width));
	background->setScaleY(float(visibleSize.height / background->getContentSize().height));
	background->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	background->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));

	this->addChild(background);

	// Tao các button chính cho game

	// Start Game
	Sprite* startGame1 = Sprite::create("img/button/play_btn2.png");
	Sprite* startGame2 = Sprite::create("img/button/play_btn3.png");

	MenuItemSprite* startGameBtn = MenuItemSprite::create(
		startGame1 , 
		startGame2 , 
		CC_CALLBACK_1(BowManMenuScene::startGameCallBack , this)
		);
	startGameBtn->setScale(1.5f);
	startGameBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	startGameBtn->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2 + 80));

	// Score Game
	Sprite* scoreGame1 = Sprite::create("img/button/score_btn4.png");
	Sprite* scoreGame2 = Sprite::create("img/button/score_btn5.png");

	MenuItemSprite* scoreGameBtn = MenuItemSprite::create(
		scoreGame1 ,
		scoreGame2 ,
		CC_CALLBACK_1(BowManMenuScene::scoreGameCallBack , this)
		);
	scoreGameBtn->setScale(1.5f);
	scoreGameBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	scoreGameBtn->setPosition(Vec2(visibleSize.width / 2 , startGameBtn->getPositionY() - startGameBtn->getContentSize().height/2 - scoreGameBtn->getContentSize().height/2 - 40));

	
	// Sound Game
	Sprite* soundGame1 = Sprite::create("img/button/music_btn.png");
	Sprite* soundGame2 = Sprite::create("img/button/music_btn1.png");
	Sprite* soundGame3 = Sprite::create("img/button/music_btn2.png");

	MenuItemSprite* soundGameBtn = MenuItemSprite::create(
		soundGame1 ,
		soundGame2 ,
		soundGame3 ,
		CC_CALLBACK_1(BowManMenuScene::soundGameCallBack , this)
		);
	soundGameBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	soundGameBtn->setPosition(Vec2(origin.x + 20 + soundGameBtn->getContentSize().width/2 , visibleSize.height - 20 - soundGameBtn->getContentSize().height/2 ));

	// Help Game
	Sprite* helpGame1 = Sprite::create("img/button/help_btn.png");
	Sprite* helpGame2 = Sprite::create("img/button/help_btn1.png");

	MenuItemSprite* helpGameBtn = MenuItemSprite::create(
		helpGame1 ,
		helpGame2 ,
		CC_CALLBACK_1(BowManMenuScene::helpGameCallBack , this)
		);
	helpGameBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	helpGameBtn->setPosition(Vec2(
			origin.x + 20 + soundGameBtn->getContentSize().width/2 ,
			soundGameBtn->getPositionY() - soundGameBtn->getContentSize().height/2 - helpGameBtn->getContentSize().height/2 - 20
			));

	// Info Game

	Sprite* inforGame1 = Sprite::create("img/button/info_btn.png");
	Sprite* inforGame2 = Sprite::create("img/button/info_btn1.png");

	MenuItemSprite* inforGameBtn = MenuItemSprite::create(
		inforGame1 ,
		inforGame2 ,
		CC_CALLBACK_1(BowManMenuScene::inforGameCallBack , this)
		);
	inforGameBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	inforGameBtn->setPosition(Vec2(
			origin.x + 20 + soundGameBtn->getContentSize().width/2 ,
			helpGameBtn->getPositionY() - helpGameBtn->getContentSize().height/2 - inforGameBtn->getContentSize().height/2 - 20
			));

	Sprite* menuGame1 = Sprite::create("img/button/menu_icon.png");
	Sprite* menuGame2 = Sprite::create("img/button/menu_icon.png");
	MenuItemSprite* menuBtn = MenuItemSprite::create(
		menuGame1 ,
		menuGame2 ,
		CC_CALLBACK_1(BowManMenuScene::menuCallback , this)
		);

	menuBtn->setPosition(Vec2(
		origin.x + 20 + soundGameBtn->getContentSize().width / 2,
		inforGameBtn->getPositionY() - inforGameBtn->getContentSize().height / 2 - menuBtn->getContentSize().height / 2 - 20
		));

	Menu* startMenu = Menu::create(
		startGameBtn ,
		scoreGameBtn ,
		soundGameBtn ,
		helpGameBtn ,
		inforGameBtn ,
		menuBtn ,
		NULL
		);
	startMenu->setAnchorPoint(Vec2::ZERO);
	startMenu->setPosition(Vec2(0,0));

	this->addChild(startMenu);

	return true;
}


void BowManMenuScene::startGameCallBack(Ref* pSender)
{
	// Callback được gọi khi click btn Play
	cocos2d::log("startGame CallBack");
	createInputDialog();

}
void BowManMenuScene::scoreGameCallBack(Ref* pSender){
	// Callback được gọi khi click btn Score
	cocos2d::log("scoreGame CallBack");
}
void BowManMenuScene::helpGameCallBack(Ref* pSender){
	// Callback được gọi khi click btn help
	cocos2d::log("helpGame CallBack");
}
void BowManMenuScene::soundGameCallBack(Ref* pSender){
	// Callback được gọi khi click btn sound
	cocos2d::log("soundGame CallBack");
}
void BowManMenuScene::inforGameCallBack(Ref* pSender){
	// Callback được gọi khi click btn info
	cocos2d::log("infoGame CallBack");
}

void BowManMenuScene::menuCallback(Ref* pSender){
	cocos2d::log("List CallBack");
	Director::getInstance()->replaceScene(ListViewGameScene::createScene());
}

void BowManMenuScene::createInputDialog()
{
	// Hien thi dialog nhap ten cua nhan vat choi
	Size visibleSize = Director::getInstance()->getVisibleSize();
	
	/////////////////////////////
	// Dialog Background
	/////////////////////////////
	Sprite* dialogBG = Sprite::create("img/dialog/inputname_dialog1.png");
	dialogBG->setScale(2.0f);
	dialogBG->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	dialogBG->setPosition(Vec2(visibleSize.width/2 , visibleSize.height/2));

	this->addChild(dialogBG);

	/////////////////////////////
	// Set EditBox Input
	/////////////////////////////

	Size inputBoxSize = Size(238 * 2 , 37 * 2);

	inputName = ui::EditBox::create(inputBoxSize , "img/dialog/input.png");
	inputName->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2 - 5 ));
	inputName->setFontName("fonts/syunka2pbb.ttf");
    inputName->setFontSize(15 * 2);
	inputName->setFontColor(Color3B::WHITE);
    inputName->setPlaceHolder("Name:");
	inputName->setPlaceholderFontName("fonts/Marker Felt.ttf");
    inputName->setPlaceholderFontColor(Color3B::WHITE);
    inputName->setMaxLength(20);
    inputName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    
	this->addChild(inputName);


	/////////////////////////////
	// Set Button
	/////////////////////////////

	Sprite* okSprite1 = Sprite::create("img/dialog/ok_button1.png");
	Sprite* okSprite2 = Sprite::create("img/dialog/ok_button2.png");
	MenuItemSprite* okBtn = MenuItemSprite::create(
		okSprite1 , 
		okSprite2 , 
		CC_CALLBACK_1(BowManMenuScene::inputNameCallback , this)
	);
	okBtn->setScale(2.0f);
	okBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	okBtn->setPosition(Vec2(visibleSize.width/2, visibleSize.height / 2 - 45 * 2 ));
	Menu* okMenu = Menu::create(okBtn , NULL);
	okMenu->setPosition(Vec2::ZERO);

	this->addChild(okMenu);

}

// Goi ham callback sau khi nhap ten
void BowManMenuScene::inputNameCallback(Ref* pSender)
{
	// Xu ly luu ten nguoi dung vao csdl va su dung cho viec thuc hien story

	/////////////////////////////
	// Xu ly luu ten vao csdl
	/////////////////////////////

	createDB();

	std::string userName = inputName->getText();
	if (insertNameToDB(userName))
	{
		/////////////////////////////
		// Chuyen qua phan story cua game
		/////////////////////////////

		cocos2d::log("OK");
		auto storyGame = BowManStoryScene::createScene();
		Director::getInstance()->replaceScene(storyGame);
	}
	else
	{
		cocos2d::log("DB Error");
	}
}


void BowManMenuScene::createDB()
{
	// Luu ten nhan vat vao co so du lieu
	// Tao 1 csdl: bowMan.db3 va 1 bang user
	// Cac truong trong user la: id , userName , userScore

	auto bowManDB = SqlUtil::openData("bowMan.db3");
	SqlUtil::createTable(bowManDB, "user", "id", "integer", { "userName varchar(50)", "userScore varchar(50)"});
}

bool BowManMenuScene::insertNameToDB(string userName)
{
	auto bowManDB = SqlUtil::openData("bowMan.db3");
	int result = SqlUtil::insertRow(bowManDB, "user", { "userName" , "userScore" }, { userName , "" });
	if (result == SQLITE_DONE)
	{
		return true;
	}

	return false;
}

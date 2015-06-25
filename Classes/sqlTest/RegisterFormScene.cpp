/*
 * RegisterFormScene.cpp
 *
 *  Created on: 2015/02/03
 *      Author: chu
 */


#include "RegisterFormScene.h"
#include <string>
#include <string.h>


USING_NS_CC;
using namespace std;

Scene* RegisterFormScene::createScene()
{

    auto scene = Scene::create();
    auto layer = RegisterFormScene::create();
    scene->addChild(layer);

    return scene;
}

bool RegisterFormScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// Tao form input de nhap ten va email dang ky


	Size editBoxSize = Size(200,25); // Kich thuoc dung chung cho cac input

	editName = ui::EditBox::create(editBoxSize,"sqltest_img/green_edit.png");
    editName->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height / 2 + 80 ));
    editName->setFontName("Arial");
    editName->setFontSize(15);
    editName->setFontColor(Color3B::RED);
    editName->setPlaceHolder("Name:");
    editName->setPlaceholderFontColor(Color3B::WHITE);
    editName->setMaxLength(8);
    editName->setReturnType(ui::EditBox::KeyboardReturnType::DONE);
    this->addChild(editName);

	editPassword = ui::EditBox::create(editBoxSize, "sqltest_img/orange_edit.png");
    editPassword->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2 + 40));
    editPassword->setFont("Arial", 15);
    editPassword->setFontColor(Color3B::GREEN);
    editPassword->setPlaceHolder("Password:");
    editPassword->setMaxLength(6);
    editPassword->setInputFlag(ui::EditBox::InputFlag::PASSWORD);
    editPassword->setInputMode(ui::EditBox::InputMode::SINGLE_LINE);
    this->addChild(editPassword);

	editEmail = ui::EditBox::create(Size(editBoxSize.width, editBoxSize.height), "sqltest_img/yellow_edit.png");
	editEmail->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2 ));
	editEmail->setAnchorPoint(Vec2(0.5, 1.0f));
	editEmail->setFont("Paint Boy" , 15); // fontname , size
	editEmail->setPlaceHolder("Email:");
	editEmail->setInputMode(ui::EditBox::InputMode::EMAIL_ADDRESS);
	this->addChild(editEmail);

	cocos2d::log("mail(x,y) = ( %f , %f )" , origin.x+visibleSize.width/2 , origin.y+visibleSize.height/2 );

	auto okButton = MenuItemImage::create(
		"sqltest_img/ok.png" ,
		"sqltest_img/ok.png" ,
		CC_CALLBACK_1(RegisterFormScene::registerCallback , this)
	);

	okButton->setScale(0.25);
	okButton->setPosition(Vec2(-50 , -50));

	auto cancelButton = MenuItemImage::create(
		"sqltest_img/cancel.png" ,
		"sqltest_img/calcel.png" ,
		CC_CALLBACK_1(RegisterFormScene::cancelCallback , this)
		);
	cancelButton->setScale(0.25);
	cancelButton->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	cancelButton->setPosition(Vec2(50, -50));

	Menu* menu = Menu::create(
		okButton , 
		cancelButton ,
		NULL
		);

	this->addChild(menu);
	menu->setAnchorPoint(Vec2::ZERO);
    return true;
}


void RegisterFormScene::registerCallback(Ref* pSender)
{
	// Todo
	auto name = editName->getText();
	auto passWord = editPassword->getText();
	auto email = editEmail->getText();
	cocos2d::log("name = %s" , name);

	//////////////////////////////////////////////////////////////////////
	// Tao csdl
	// dbName: user.sqlite
	// Khoi tao bang du lieu tableName : user
	// Cac truong trong bang la user_name , user_pass , user_email
	///////////////////////////////////////////////////////////////////////

	sqlite3 *pDB = NULL;

	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "user.sqlite";

	std::string sql;
	int result;
	result = sqlite3_open(path.c_str(),&pDB);
	
	if(result != SQLITE_OK){
		cocos2d::log("open database failed, number%d",result);
	} else {
		cocos2d::log("openDB succesfull");
	}


	// Create db
		// Create table
	result = sqlite3_exec(
		pDB ,
		"create table if not exists user(ID integer primary key autoincrement,user_name text,user_pass text,user_email)" ,
		NULL,
		NULL,
		NULL
		);
	if(result != SQLITE_OK){
		cocos2d::log("create table failse , number = %d ", result);
	} else {
		cocos2d::log("create table succesfull");
	}

	// select row,colum
	char **re;
	int r,c;
	sqlite3_get_table(pDB,"select * from user",&re,&r,&c,NULL);


	// Insert data

	std::stringstream idString;
	idString << r + 1;

	sql = "insert into user values(" + idString.str() + ",'" + string(name) + "','" + string(passWord) + "','" + string(email) + "')";
	result=sqlite3_exec(pDB , sql.c_str() , NULL , NULL , NULL);
	
	if(result != SQLITE_OK){
		cocos2d::log("insert data failed!");
	}else{
		cocos2d::log("insert successful");
		cocos2d::log("Parkour Game");
		auto parkourScene = ParkourMenu::createScene();
		Director::getInstance()->replaceScene(parkourScene);
	}

	sqlite3_close(pDB);
}

void RegisterFormScene::cancelCallback(Ref* pSender)
{
	// Todo

	cocos2d::log("Register Form");
	auto listView = ListViewGameScene::createScene();
	Director::getInstance()->replaceScene(listView);
}


void RegisterFormScene::createDB()
{
	//////////////////////////////////////////////////////////////////////
	// Tao csdl
	// dbName: user.sqlite
	// Khoi tao bang du lieu tableName : user
	// Cac truong trong bang la user_name , user_pass , user_email
	///////////////////////////////////////////////////////////////////////

	// Create db
	sqlite3 *pDB = NULL;

	std::string path = FileUtils::getInstance()->getWritablePath();
	path += "user.sqlite";

	std::string sql;
	int result;
	result=sqlite3_open(path.c_str(),&pDB);
	
	if(result!=SQLITE_OK){
		cocos2d::log("open database failed, number%d",result);
	}

	// Create table
	result = sqlite3_exec(
		pDB ,
		"create table user(ID integer primary key autoincrement,user_name text,user_pass text,user_email)" ,
		NULL,
		NULL,
		NULL
		);
	if(result != SQLITE_OK){
		cocos2d::log("create table failse , number = %d ", result);
	} else {
		cocos2d::log("OK");
	}
}

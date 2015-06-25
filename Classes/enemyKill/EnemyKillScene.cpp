/*
 * FirstGameScene.cpp
 *
 *  Created on: 2015/01/14
 *      Author: chu
 */

#include "enemyKill\EnemyKillScene.h"
#include "enemyKill\EnemyKillGameOver.h"
#include <string>

USING_NS_CC;

using namespace cocos2d;
using namespace std;

Scene* EnemyKillScene::createScene()
{


    auto scene = Scene::createWithPhysics();

    // Goi ra 1 khong gian vat ly
    auto world = scene->getPhysicsWorld();

    // Lenh nay cho phep nhin thay cac khung body vat ly ap dung vao cac doi tuong
    world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    // Thiet lap trong luc
    world->setGravity(Vect(0.0f , 0.0f));


	auto layer = EnemyKillScene::create();
	scene->addChild(layer);


	return scene;
}

bool EnemyKillScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}

	// 設備のサイズと座標点
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	player = Sprite::create("enemykill_img/Player.png");

	player->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	player->setPosition(Vec2(player->getContentSize().width/2 , visibleSize.height/2));


	// Tao 1 bo khung vat ly co dang hinh tron cho doi tuong player
	auto playerBody = PhysicsBody::createCircle(player->getContentSize().width/2);
	// Dat co = 1 de sau nay xet va cham giua cac doi tuong
	player->setTag(1);
	playerBody->setContactTestBitmask(0x1); // Cau lenh nay quan trong
	player->setPhysicsBody(playerBody);

	this->addChild(player);

	createBack();

	this->schedule(schedule_selector(EnemyKillScene::logicGame) , 1.0);

	score = 0;

	labelScore = Label::create("0", "Arial", 50);
	labelScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelScore->setPosition(Vec2(visibleSize.width/2 - 10 , visibleSize.height/2 - 10));

	this->addChild(labelScore);

	// ディパッチャオブジェクトを作成する
	auto dispatcher = Director::getInstance()->getEventDispatcher();

	// 画面のタップイベントを得るオブジェクトを生成する
	auto listenerTouch = EventListenerTouchOneByOne::create();

	// Thiet lap nuot su kien Touch khi no duoc thuc thi,ngan ko cho cac doi tuong bat su kien khac su dung event nay
	listenerTouch->setSwallowTouches(true);

	// タップイベントのコールバックメッソドを宣言する

	listenerTouch->onTouchBegan = CC_CALLBACK_2(EnemyKillScene::onTouchBegan , this);
	listenerTouch->onTouchMoved = CC_CALLBACK_2(EnemyKillScene::onTouchMoved , this); // Khong xu ly nhung nen khai bao de su kien Touch dc day du
	listenerTouch->onTouchEnded = CC_CALLBACK_2(EnemyKillScene::onTouchEnded , this);

	// ディパッチャオブジェクトでタップイベントを得て、処理する
	dispatcher->addEventListenerWithSceneGraphPriority(listenerTouch , this);

	// Tao 1 bo lang nghe su kien va cham giua dan,quai vat va player

	auto contactListener = EventListenerPhysicsContact::create();

	// su dung onContactBegin de xu ly va cham

	contactListener->onContactBegin = CC_CALLBACK_1(EnemyKillScene::onContactBegin , this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener , this);

	return true;
}

bool EnemyKillScene::onContactBegin(PhysicsContact& contact){
	// Lay doi tuong va cham thu nhat va ep kieu con tro Sprite
	auto bullet = (Sprite*)contact.getShapeA()->getBody()->getNode();
	int tag1 = bullet->getTag();

	auto target = (Sprite*)contact.getShapeB()->getBody()->getNode();
	int tag2 = target->getTag();


	// 1:
	// 2:
	// 3: vien dan

	if((tag1==2 & tag2==3)||(tag1==3 & tag2==2)){
		score++;

		this->removeChild(bullet,true); // Xoa dan
		this->removeChild(target,true); // Xoa quai

		cocos2d::log("Score: %d " , score);

		std::stringstream text;
		text << score << std::endl;
		cocos2d::log("%s", text.str().c_str());

		labelScore->setString(text.str().c_str());
	}

	if((tag1==1 & tag2==2)||(tag1==2 & tag2==1)){
		// Xu ly tinh diem va chuyen
		cocos2d::log("Xu ly game over");
		cocos2d::log("Score: %d " , score);
		Director::getInstance()->replaceScene(EnemyKillGameOver::createScene(EnemyKillScene::score));
	}

	return true;
}

bool EnemyKillScene::onTouchBegan(Touch* touch , Event* event){

	return true;
}

void EnemyKillScene::onTouchMoved(Touch* touch , Event* event){

}

void EnemyKillScene::onTouchEnded(Touch* touch , Event* event){

	// タップした所の座標を得る
	Vec2 location = touch->getLocationInView();
	location = Director::getInstance()->convertToGL(location);

	Size visibleSize = Director::getInstance()->getVisibleSize();


	// 弾スプライトを設定する
	Sprite* projectile = Sprite::create("enemykill_img/Projectile.png");
	// プレイーの位置の隣所に弾の配置を設定する
	projectile->setPosition(Vec2(player->getContentSize().width/2 + 5 , visibleSize.height/2));

	auto projectileBody = PhysicsBody::createCircle(projectile->getContentSize().width/2);


	// Them bo khung vat ly hinh tron vao cho vien dan
	projectile->setTag(3);
	projectileBody->setContactTestBitmask(0x1);
	projectile->setPhysicsBody(projectileBody);


	int offX = location.x - projectile->getPositionX();
	int offY = location.y - projectile->getPositionY();

	if(offX < 0) return;

	this->addChild(projectile);

	int realX = visibleSize.width + projectile->getContentSize().width/2;

	float ratio = float(offY) / float(offX);

	int realY = ((realX-projectile->getPosition().x) * ratio) + projectile->getPosition().y;


	Vec2 realDest = Vec2(realX , realY);

	int offRealX = realX - projectile->getPositionX();
	int offRealY = realY - projectile->getPositionY();

	float length = sqrt((offRealX * offRealX) + (offRealY * offRealY));

	float velocity = 480/1; // 速度は480picel/1秒

	float realMoveDuration = length / velocity;

	auto move= MoveTo::create(realMoveDuration,realDest);
	auto finish = CallFuncN::create(CC_CALLBACK_1(EnemyKillScene::spriteMoveFinished , this));
	auto run = Sequence::create(move,finish,NULL);
	projectile->runAction(run);

}

void EnemyKillScene::logicGame(float dt){
	//Todo
	this->addTarget();
}


void EnemyKillScene::addTarget(){
	// Khoi tao quai

	Sprite* target = Sprite::create("enemykill_img/Target.png");
	Size visibleSize = Director::getInstance()->getVisibleSize();
	int minY = target->getContentSize().height/2;
	int maxY = visibleSize.height - target->getContentSize().height/2;

	int rangeY = maxY - minY;
	int rand1 = rand() % rangeY;
	int actualY =  rand1 + minY;

	target->setPosition(Vec2(visibleSize.width - (target->getContentSize().width/2), actualY));

	// Them bo khung vat ly hinh tron cho quai vat
	auto targetBody = PhysicsBody::createCircle(target->getContentSize().width/2);

	target->setTag(2);

	targetBody->setContactTestBitmask(0x1);
	target->setPhysicsBody(targetBody);

	addChild(target);

	// Tinh toan toc do di chuyen cua quai

	int minDuration = (int)2.0; // khoang thoi gian min
	int maxDuration = (int)4.0; // khoang thoi gian max

	int rangeDuration = maxDuration - minDuration;

	int rand2 = rand() % rangeDuration;

	int actualDuration = rand2 + minDuration;

	// Di chuyen quai voi toc do actualDuration toi diem Point(0,y)
	auto actionMove = MoveTo::create(float(actualDuration) , Vec2(0 + target->getContentSize().width/2 , actualY));


	// Ket thuc viec di chuyen cua quai vat khi den diem cuoi
	auto actionMoveDone = CallFuncN::create(CC_CALLBACK_1(EnemyKillScene::spriteMoveFinished , this));


	// Chay 2 action tren 1 cach tuan tu
	target->runAction(Sequence::create(actionMove , actionMoveDone , NULL));

}

void EnemyKillScene::spriteMoveFinished(cocos2d::Node* node){
	auto sprite = (Sprite*)node;
	 this->removeChild(sprite, true);
}

bool EnemyKillScene::checkCollisionSprite(Sprite* sprite1 , Sprite* sprite2)
{
	//Todo
	// Tao cac RectBox dung de xet va cham
	Rect sprite1RectBox = Rect(
		sprite1->getPosition().x - sprite1->getContentSize().width/2 ,
		sprite1->getPosition().y - sprite1->getContentSize().height/2 ,
		sprite1->getContentSize().width ,
		sprite1->getContentSize().height
		);
	
	Rect sprite2RectBox = Rect(
		sprite2->getPosition().x - sprite2->getContentSize().width/2 ,
		sprite2->getPosition().y - sprite2->getContentSize().height/2 ,
		sprite2->getContentSize().width ,
		sprite2->getContentSize().height
		);

	if(sprite1RectBox.intersectsRect(sprite2RectBox)){
		return true;
	}

	return false;
}


void EnemyKillScene::createBack()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto menuBackButton = MenuItemImage::create(
		"enemykill_img/back_btn.png" ,
		"enemykill_img/back_btn1.png" ,
		CC_CALLBACK_1(EnemyKillScene::backCallback , this)
		);

	menuBackButton->setScale(0.25f);
	menuBackButton->setPosition(Vec2(-10 + menuBackButton->getContentSize().width / 2, visibleSize.height - menuBackButton->getContentSize().height / 2));
	Menu* menuBack = Menu::create(menuBackButton, NULL);
	menuBack->setAnchorPoint(Vec2::ZERO);
	menuBack->setPosition(Vec2::ZERO);

	this->addChild(menuBack , 99);
}

void EnemyKillScene::backCallback(Ref* pSender){
	auto listView = ListViewGameScene::createScene();
	Director::getInstance()->replaceScene(listView);
}

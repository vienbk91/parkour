/*
 * MenuScene.cpp
 *
 *  Created on: 2015/01/16
 *      Author: chu
 */

#include "ScrollViewScene.h"

USING_NS_CC;

using namespace cocos2d;
using namespace std;
using namespace ui;
using namespace extension;

Scene* ScrollViewScene::createScene() {

	auto scene = Scene::create();
	auto layer = ScrollViewScene::create();
	scene->addChild(layer);

	return scene;
}

bool ScrollViewScene::init() {
	if (!Layer::init()) {
		return false;
	}
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	auto background = Sprite::create("uitest_img/HelloWorld.png");
	Size backgroundSize = background->getContentSize();
	background->setAnchorPoint(Vec2::ZERO);
	background->setPosition(Vec2::ZERO);

	this->addChild(background);

	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Khoi tao scroll voi thu vien UI
	//////////////////////////////////////////////////////////////////////////////////////////////////
	
	ui::ScrollView* scrollViewUI = ui::ScrollView::create();
	scrollViewUI->setContentSize(visibleSize);
	scrollViewUI->setBackGroundColor(Color3B::BLUE);
	scrollViewUI->setBackGroundColorType(Layout::BackGroundColorType::SOLID);
	scrollViewUI->setBounceEnabled(false);
	scrollViewUI->setDirection(ui::ScrollView::Direction::VERTICAL);
	scrollViewUI->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	scrollViewUI->setPosition(Vec2(visibleSize.width/2 ,visibleSize.height/2));
	scrollViewUI->setContentSize(Size(visibleSize.width - 100 , visibleSize.height - 50));// khoi tao kich thuoc view co ban cho scrollView bang kich thuoc man hinh


	this->addChild(scrollViewUI);
	
	// Khoi tao menu button
	Sprite* pBtnSprite1 = Sprite::create("uitest_img/start_n.png");
	Sprite* pBtnSprite2 = Sprite::create("uitest_img/start_s.png");

	MenuItemSprite* pStartMenuBtn = MenuItemSprite::create(pBtnSprite1 , pBtnSprite2 ,CC_CALLBACK_1( ScrollViewScene::startCallback , this));

	Menu* menu = Menu::create(pStartMenuBtn , NULL);
	menu->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menu->setPosition(Vec2(scrollViewUI->getContentSize().width / 2 , menu->getContentSize().height / 2) ); // Vi y = 0 nen se nam o phia duoi cung cua scroll

	scrollViewUI->addChild(menu);

	// Khoi tao 1 sprite anh

	Sprite* sprite = Sprite::create("uitest_img/PlayBG.png");
	float scaleX = scrollViewUI->getContentSize().width / sprite->getContentSize().width;
	sprite->setScaleX(scaleX);

	sprite->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	sprite->setPosition(Vec2(scrollViewUI->getContentSize().width / 2 , menu->getContentSize().height + sprite->getContentSize().height / 2 ));

	scrollViewUI->addChild(sprite);

	// Khoi tao text 
	auto string_txt = "日本の地獄は自慢の地獄\n罪にあわせておもてなし\n(はい!)\n日本の地獄はじゅうろくしょう地獄!\n全部合わせて、にひゃくななじゅうにもあるーーーーーー!!\n\nここは地獄!地獄!素敵な地獄!\n地獄、じご、じご、じごくだよ～!!\n\nここは地獄!地獄!楽しい地獄!\n地獄、じご、じご、じごくだよ～!!\n\n等活(とうかつ)黒縄(こくじょう)衆合(しゅうごう)\n叫喚(きょうかん)\n大叫喚(だいきょうかん)\n焦熱(しょうねつ)に 大焦熱(だいしょうねつ) 阿鼻!！\n不喜処(ふきしょ)(に)瓮熟処(おうじゅくしょ)、\n如飛虫堕処(にょひちゅうだしょ)\n受苦無有数量処(じゅくむうすうりょうしょ)\n屎泥処(しでいしょ)(に)、刀輪処(とうりんしょ)\n多苦処(たくしょ)(に)闇冥処(あんみゅうしょ)(に)極苦処(ごくくしょ)\n\n頞部陀(あぶだ)、刺部陀(にらぶだ)\n頞听陀(あただ)、臛臛婆(かかば)、虎虎婆(ここば)\n嗢鉢羅(うばら)、(に)、鉢特摩(はどま)(に)摩訶鉢特摩(まかはどま)\n\n衆病処(しゅうびょうしょ)、(ったら) 雨鉄処(うてつしょ)、(ったら)\n悪杖処(あくじょうしょ)、黒色鼠狼処(こくしょくそうろうしょ)、\n針山、血の池、まだまだ色々!\n\n地獄はあるかもしれないよ!!\nこの世の行い気をつけてー!\n\nここは地獄!地獄!素敵な地獄!\n地獄、じご、じご、じごくだよ～!!\n\nここは地獄!地獄!楽しい地獄!\n地獄、じご、じご、じご、じご、じご、\nじご、じご、じご、じご、じご、じごくだよ～!!\n\n嗚呼～ \n";
    auto label = Label::createWithTTF(string_txt, "fonts/syunka2pbb.ttf", 15);

	//label->setDimensions(Size(visibleSize.width,0));
	label->setDimensions(scrollViewUI->getContentSize().width, label->getContentSize().height); // set kich thuoc
    label->setHorizontalAlignment(TextHAlignment::LEFT);
	label->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	label->setPosition(Vec2( scrollViewUI->getContentSize().width / 2 , label->getContentSize().height / 2 + sprite->getContentSize().height + menu->getContentSize().height )); // Se hien thi phia tren Image
	
	scrollViewUI->addChild(label);


	// Thiet lap kich thuoc cua scroll lai 1 lan nua
	// inner : noi bo , ben trong
	float innerWidth = scrollViewUI->getContentSize().width;
	float innerHeight = label->getContentSize().height + menu->getContentSize().height + sprite->getContentSize().height;

	scrollViewUI->setInnerContainerSize(Size(innerWidth , innerHeight));

	return true;
}

void ScrollViewScene::startCallback(Ref* pSender){
	auto listViewGame = ListViewGameScene::createScene();
	Director::getInstance()->replaceScene(listViewGame);


}
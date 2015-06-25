#pragma execution_character_set("utf-8") // Hien thi tieng nhat

#include "bowman\BowManStoryScene.h"


#define WINSIZE Director::getInstance()->getVisibleSize() // Kich thuoc man hinh
#define DELAYTIME_STORY 10.0 // Thoi gian chay animation history
#define DELAYTIME_TALK 10.0 // Thoi gian chay talk character

USING_NS_CC;

// Contructor - Ham khoi tao
BowManStoryScene::BowManStoryScene()
{
}
// Destructor - Ham huy diet
BowManStoryScene::~BowManStoryScene()
{
}

Scene* BowManStoryScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BowManStoryScene::create();

	scene->addChild(layer);

	return scene;
}


bool BowManStoryScene::init()
{
	if(!Layer::init())
	{
		return false;
	}

	// Khoi tao story1
	story1();

	return true;
}


void BowManStoryScene::story1()
{
	cocos2d::log("Story1 - Dan chung lam than");

	//////////////////////////////////////////////////
	// BACKGROUND
	/////////////////////////////////////////////////
	
	Sprite* storyBg1 = Sprite::create("img/background/story1.png");
	storyBg1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyBg1->setScale(float(WINSIZE.width / storyBg1->getContentSize().width), float(WINSIZE.height / storyBg1->getContentSize().height));
	storyBg1->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	
	storyBg1->setTag(Tag_Background::Tbg_Story1);
	this->addChild(storyBg1);

	//////////////////////////////////////////////////
	// SKIP BUTTON
	/////////////////////////////////////////////////
	
	MenuItemImage* skipBtn = MenuItemImage::create(
		"img/button/skip_btn1.png",
		"img/button/skip_btn.png",
		CC_CALLBACK_1(BowManStoryScene::skipCallback, this)
		);
	skipBtn->setTag(Tag_Skip::T_SkipStory1);
	skipBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	skipBtn->setPosition(Vec2(WINSIZE.width - 10 - skipBtn->getContentSize().width / 2, 10 + skipBtn->getContentSize().height / 2));
	Menu* skipMenu = Menu::create(skipBtn, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	this->addChild(skipMenu);

	//////////////////////////////////////////////////
	// TEXT ANIMATION
	/////////////////////////////////////////////////
	auto storyString1 = "あいうえお";
	storyLabel1 = Label::createWithTTF(storyString1, "fonts/syunka2pbb.ttf", 24);
	storyLabel1->setColor(Color3B(255,255,255));
	storyLabel1->setString("昔々からある国で怖い王様がいるので\n\n国民の皆、貧乏な生活になりました。");
	storyLabel1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyLabel1->setPosition(Vec2(WINSIZE.width / 2, -(storyLabel1->getContentSize().height / 2)));	
	storyLabel1->setTag(Tag_Label::Tlb_Story1);
	this->addChild(storyLabel1);

	// Ham callback goi den story2
	CallFunc* story2Callback = CallFunc::create(CC_CALLBACK_0(BowManStoryScene::story2 , this));
	
	auto moveAction = MoveTo::create(DELAYTIME_STORY, Vec2(WINSIZE.width / 2, WINSIZE.height + storyLabel1->getContentSize().height / 2));
	Sequence* sequence = Sequence::create(moveAction, story2Callback, NULL);
	sequence->setTag(Tag_Action::T_actionStory1);
	storyLabel1->runAction(sequence);

}

void BowManStoryScene::story2()
{
	cocos2d::log("story2 - Hiep si xuat hien");
	//////////////////////////////////////////////////
	// BACKGROUND
	/////////////////////////////////////////////////

	Sprite* storyBg2 = Sprite::create("img/background/story2.png");
	storyBg2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyBg2->setScale(float(WINSIZE.width / storyBg2->getContentSize().width), float(WINSIZE.height / storyBg2->getContentSize().height));
	storyBg2->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	storyBg2->setTag(Tag_Background::Tbg_Story2);
	this->addChild(storyBg2);

	//////////////////////////////////////////////////
	// SKIP BUTTON
	/////////////////////////////////////////////////
	
	MenuItemImage* skipBtn = MenuItemImage::create(
		"img/button/skip_btn1.png",
		"img/button/skip_btn.png",
		CC_CALLBACK_1(BowManStoryScene::skipCallback, this)
		);
	skipBtn->setTag(Tag_Skip::T_SkipStory2);
	skipBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	skipBtn->setPosition(Vec2(WINSIZE.width - 10 - skipBtn->getContentSize().width / 2, 10 + skipBtn->getContentSize().height / 2));
	Menu* skipMenu = Menu::create(skipBtn, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	this->addChild(skipMenu);

	//////////////////////////////////////////////////
	// TEXT ANIMATION
	/////////////////////////////////////////////////

	string storyString2 = "あいうえお";
	storyLabel2 = Label::createWithTTF(storyString2, "fonts/syunka2pbb.ttf", 24);
	storyLabel2->setColor(Color3B(255, 255, 255));


	string userName;
	userName = getNameUser();
	cocos2d::log("Ten hiep si: %s ", userName.c_str());

	storyString2 = "時に、一人ヘロが出現しました。\n\nこれは ";
	storyString2.append(userName.c_str());
	storyString2.append(" 様です。");

	storyLabel2->setString(storyString2);
	// Add them ten cua nguoi choi vao
	
	// Thuc hien action move cho chu chay tu duoi len tren bang action from->moveTo(time, to);
	storyLabel2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyLabel2->setPosition(Vec2(WINSIZE.width / 2, -(storyLabel2->getContentSize().height / 2)));
	storyLabel2->setTag(Tag_Label::Tlb_Story2);
	this->addChild(storyLabel2);

	// Ham callback goi den story3
	CallFunc* story3Callback = CallFunc::create(CC_CALLBACK_0(BowManStoryScene::story3 , this));
	auto moveAction = MoveTo::create(DELAYTIME_STORY , Vec2(WINSIZE.width / 2, WINSIZE.height + storyLabel2->getContentSize().height / 2));
	Sequence* sequence = Sequence::create(moveAction, story3Callback, NULL);
	sequence->setTag(Tag_Action::T_actionStory2);
	storyLabel2->runAction(sequence);

}


void BowManStoryScene::story3()
{
	cocos2d::log("story3 - Me hiep si bi bat");
	//////////////////////////////////////////////////
	// BACKGROUND
	/////////////////////////////////////////////////
	Sprite* storyBg3 = Sprite::create("img/background/story3.png");
	storyBg3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyBg3->setScale(float(WINSIZE.width / storyBg3->getContentSize().width), float(WINSIZE.height / storyBg3->getContentSize().height));
	storyBg3->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	storyBg3->setTag(Tag_Background::Tbg_Story3);
	this->addChild(storyBg3);

	//////////////////////////////////////////////////
	// SKIP BUTTON
	/////////////////////////////////////////////////

	MenuItemImage* skipBtn = MenuItemImage::create(
		"img/button/skip_btn1.png",
		"img/button/skip_btn.png",
		CC_CALLBACK_1(BowManStoryScene::skipCallback, this)
		);
	skipBtn->setTag(Tag_Skip::T_SkipStory3);
	skipBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	skipBtn->setPosition(Vec2(WINSIZE.width - 10 - skipBtn->getContentSize().width / 2, 10 + skipBtn->getContentSize().height / 2));
	Menu* skipMenu = Menu::create(skipBtn, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	this->addChild(skipMenu);


	//////////////////////////////////////////////////
	// TEXT ANIMATION
	/////////////////////////////////////////////////

	auto storyString3 = "あいうえお";
	storyLabel3 = Label::createWithTTF(storyString3, "fonts/syunka2pbb.ttf", 24);
	storyLabel3->setColor(Color3B(255, 255, 255));
	storyLabel3->setString("ヘロを探さなかったから、ヘロのお母さんが。。。");
	
	// Thuc hien action move cho chu chay tu duoi len tren
	storyLabel3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyLabel3->setPosition(Vec2(WINSIZE.width / 2, -(storyLabel3->getContentSize().height / 2)));
	storyLabel3->setTag(Tag_Label::Tlb_Story3);
	this->addChild(storyLabel3);

	// Ham callback goi den story4
	CallFunc* story4Callback = CallFunc::create(CC_CALLBACK_0(BowManStoryScene::story4 , this));
	auto moveAction = MoveTo::create(DELAYTIME_STORY , Vec2(WINSIZE.width / 2, WINSIZE.height + storyLabel3->getContentSize().height / 2));
	
	Sequence* sequence = Sequence::create(moveAction, story4Callback, NULL);
	sequence->setTag(Tag_Action::T_actionStory3);
	storyLabel3->runAction(sequence);

}


void BowManStoryScene::story4()
{
	cocos2d::log("Story4: Ong lao cho loi khuyen");
	//////////////////////////////////////////////////
	// BACKGROUND
	/////////////////////////////////////////////////

	Sprite* storyBg4 = Sprite::create("img/background/story4.png");
	storyBg4->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyBg4->setScale(float(WINSIZE.width / storyBg4->getContentSize().width), float(WINSIZE.height / storyBg4->getContentSize().height));
	storyBg4->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	storyBg4->setTag(Tag_Background::Tbg_Story4);
	this->addChild(storyBg4);

	//////////////////////////////////////////////////
	// SKIP BUTTON
	/////////////////////////////////////////////////

	MenuItemImage* skipBtn = MenuItemImage::create(
		"img/button/skip_btn1.png",
		"img/button/skip_btn.png",
		CC_CALLBACK_1(BowManStoryScene::skipCallback, this)
		);
	skipBtn->setTag(Tag_Skip::T_SkipStory4);
	skipBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	skipBtn->setPosition(Vec2(WINSIZE.width - 10 - skipBtn->getContentSize().width / 2, 10 + skipBtn->getContentSize().height / 2));
	Menu* skipMenu = Menu::create(skipBtn, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	this->addChild(skipMenu);


	//////////////////////////////////////////////////
	// TEXT ANIMATION
	/////////////////////////////////////////////////

	// Thuc hien animation chay tung chu
	auto storyString4 = "あいうえお";
	auto storyLabel4 = Label::createWithTTF(storyString4, "fonts/syunka2pbb.ttf", 24);
	storyLabel4->setHorizontalAlignment(TextHAlignment::CENTER);
	storyLabel4->setVerticalAlignment(TextVAlignment::CENTER);
	storyLabel4->setColor(Color3B(255, 255, 255));

	storyLabel4->setString("ヘロ！村の皆さんは軍に謙虚されました。\n\n早く助けに行くよ。");
	storyLabel4->setPosition(Vec2(WINSIZE.width / 2, 80));
	this->addChild(storyLabel4);

	// Ham load loi thoai cho story4
	CallFunc* showCharacter = CallFunc::create([& , storyLabel4 ](){
		auto storyLb4 = storyLabel4;
		const int numChars = storyLb4->getStringLength(); // Lay do dai string cua chuoi truyen vao
		for (int i = 0; i < numChars; i++)
		{
			auto charSprite = storyLb4->getLetter(i); // Gan tung chu thanh 1 sprite

			if (charSprite)
			{
				charSprite->setScale(0); // Khong thay doi kich thuoc cua chu

				// Thuc hien action chay chu
				float delaySec = (DELAYTIME_TALK / (numChars - 1)) * i;
				DelayTime *delay = DelayTime::create(delaySec);
				ScaleTo *appear = ScaleTo::create(0, 1);
				Sequence *delayAndShow = Sequence::create(delay, appear, NULL); // Hien thi theo trinh tu

				charSprite->runAction(delayAndShow);
			}
		}
	});
	
	// Thoi gian de showCharacter chay xong
	auto delay = DelayTime::create(DELAYTIME_TALK);
	CallFunc* story5Callback = CallFunc::create(CC_CALLBACK_0(BowManStoryScene::story5, this));
	Sequence* sequence = Sequence::create(showCharacter , delay , story5Callback , NULL);
	sequence->setTag(Tag_Action::T_actionStory4);
	this->runAction(sequence);

}

void BowManStoryScene::story5()
{
	cocos2d::log("Story5: Hiep si tra loi ong lao");

	//////////////////////////////////////////////////
	// BACKGROUND
	/////////////////////////////////////////////////

	Sprite* storyBg5 = Sprite::create("img/background/story5.png");
	storyBg5->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	storyBg5->setScale(float(WINSIZE.width / storyBg5->getContentSize().width), float(WINSIZE.height / storyBg5->getContentSize().height));
	storyBg5->setPosition(WINSIZE.width / 2, WINSIZE.height / 2);
	storyBg5->setTag(Tag_Background::Tbg_Story5);
	this->addChild(storyBg5);

	//////////////////////////////////////////////////
	// SKIP BUTTON
	/////////////////////////////////////////////////

	MenuItemImage* skipBtn = MenuItemImage::create(
		"img/button/skip_btn1.png",
		"img/button/skip_btn.png",
		CC_CALLBACK_1(BowManStoryScene::skipCallback, this)
		);
	skipBtn->setTag(Tag_Skip::T_SkipStory5);
	skipBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	skipBtn->setPosition(Vec2(WINSIZE.width - 10 - skipBtn->getContentSize().width / 2, 10 + skipBtn->getContentSize().height / 2));
	Menu* skipMenu = Menu::create(skipBtn, NULL);
	skipMenu->setPosition(Vec2::ZERO);
	this->addChild(skipMenu);


	//////////////////////////////////////////////////
	// TEXT ANIMATION
	/////////////////////////////////////////////////

	// Thuc hien animation chay tung chu
	auto storyString5 = "あいうえお";
	auto storyLabel5 = Label::createWithTTF(storyString5, "fonts/syunka2pbb.ttf", 24);
	storyLabel5->setHorizontalAlignment(TextHAlignment::CENTER);
	storyLabel5->setVerticalAlignment(TextVAlignment::CENTER);
	storyLabel5->setColor(Color3B(255, 255, 255));
	storyLabel5->setString("はい、分かりました。お祖父さん、ありがとうございます。\nすぐ行ってきます！！！");
	storyLabel5->setPosition(Vec2(WINSIZE.width / 2, 80));
	this->addChild(storyLabel5);

	// Ham load loi thoai cho story5
	CallFunc* showCharacter = CallFunc::create([&, storyLabel5](){
		auto storyLb5 = storyLabel5;
		const int numChars = storyLb5->getStringLength(); // Lay do dai string cua chuoi truyen vao
		for (int i = 0; i < numChars; i++)
		{
			auto charSprite = storyLb5->getLetter(i); // Gan tung chu thanh 1 sprite

			if (charSprite)
			{
				charSprite->setScale(0); // Khong thay doi kich thuoc cua chu

				// Thuc hien action chay chu
				float delaySec = (DELAYTIME_TALK / (numChars - 1)) * i;
				DelayTime *delay = DelayTime::create(delaySec);
				ScaleTo *appear = ScaleTo::create(0, 1);
				Sequence *delayAndShow = Sequence::create(delay, appear, NULL); // Hien thi theo trinh tu

				charSprite->runAction(delayAndShow);
			}
		}
	});

	// Thoi gian de showCharacter chay xong
	auto delay = DelayTime::create(DELAYTIME_TALK);
	CallFunc* closeStoryCallback = CallFunc::create(CC_CALLBACK_0(BowManStoryScene::closeStory, this));
	
	Sequence* sequence = Sequence::create(showCharacter, delay, closeStoryCallback, NULL);
	sequence->setTag(Tag_Action::T_actionStory5);
	this->runAction(sequence);
}

void BowManStoryScene::skipCallback(Ref* pSender)
{
	cocos2d::log("Skip Story");
	MenuItemImage* pSkipMenu = (MenuItemImage*)(pSender);

	int tag = (int)pSkipMenu->getTag();

	cocos2d::log("Story Index: %d ", tag);

	switch (tag)
	{
	case Tag_Skip::T_SkipStory1 :
		// remove action cua story1 truoc khi chuyen qua story2
		storyLabel1->stopActionByTag(Tag_Action::T_actionStory1);
		story2();
		break;
	case Tag_Skip::T_SkipStory2 :
		// remove action cua story1 truoc khi chuyen qua story3
		storyLabel2->stopActionByTag(Tag_Action::T_actionStory2);
		story3();
		break;
	case Tag_Skip::T_SkipStory3 :
		// remove action cua story1 truoc khi chuyen qua story3
		storyLabel3->stopActionByTag(Tag_Action::T_actionStory3);
		story4();
		break;
	case Tag_Skip::T_SkipStory4 :
		// remove action cua story1 truoc khi chuyen qua story4
		this->stopActionByTag(Tag_Action::T_actionStory4);
		story5();
		break;
	case Tag_Skip::T_SkipStory5 :
		// remove action cua story1 truoc khi chuyen qua story4
		this->stopActionByTag(Tag_Action::T_actionStory5);
		closeStory();
		break;
	default:
		break;
	}

}


void BowManStoryScene::closeStory()
{
	cocos2d::log("Chuyen qua ham chon map");
	// Chuyen qua BowManSelectScene
	auto selectMap = BowManSelectMap::createScene();
	Director::getInstance()->replaceScene(selectMap);
}


string BowManStoryScene::getNameUser()
{
	// Check db va open db
	auto bowManDB = SqlUtil::openData("bowMan.db3");

	
	// Lay so luong hang ,cot cua table user
	char **result;
	int row, colum;
	
	sqlite3_stmt *stmt = NULL;
	string userName;

	// Tinh row cua bang user
	int rcAll = sqlite3_get_table(bowManDB, "select * from user", &result, &row, &colum, NULL);
	if (rcAll != SQLITE_OK)
	{
		printf("error: %s!\n", sqlite3_errmsg(bowManDB));
		return NULL;
	}

	// Select userName trong bang user theo row
	std::stringstream query; // query.str() de chuyen no ve string , query.str().c_str() de chuyen no ve char
	query << "select userName from user where id = '" << row << "'";
	
	int rcUserName = sqlite3_prepare_v2(bowManDB, query.str().c_str(), -1, &stmt, NULL);
	if (rcUserName != SQLITE_OK)
	{
		printf("error: %s!\n", sqlite3_errmsg(bowManDB));
		return NULL;
	}

	for (;;)
	{
		int rc = sqlite3_step(stmt);
		if (rc == SQLITE_DONE)
			break;
		if (rc != SQLITE_ROW) {
			printf("error: %s!\n", sqlite3_errmsg(bowManDB));
			break;
		}
		userName = (char*)sqlite3_column_text(stmt, 0);
	}

	return userName;

}




/*
void BowManStoryScene::update1(float dt)
{
	// Xu ly check story1 chay xong thi chuyen qua story2
	if (storyLabel1->getNumberOfRunningActions() > 0)
	{
		return;
	}
	else 
	{
		this->unschedule(schedule_selector(BowManStoryScene::update1));
		cocos2d::log("Stop schedule story1");
		story2();
		this->schedule(schedule_selector(BowManStoryScene::update2), 0.1f);
	}
}

void BowManStoryScene::update2(float dt)
{
	// Xu ly check story2 chay xong thi chuyen qua story3
	if (storyLabel2->getNumberOfRunningActions() > 0)
	{
		return;
	}
	else 
	{
		this->unschedule(schedule_selector(BowManStoryScene::update2));
		cocos2d::log("Stop schedule story2");
		story3();
		this->schedule(schedule_selector(BowManStoryScene::update3), 0.1f);
	}
}


void BowManStoryScene::update3(float dt)
{
	// Xu ly check story3 chay xong thi chuyen qua story4
	if (storyLabel3->getNumberOfRunningActions() > 0)
	{
		return;
	}
	else
	{
		this->unschedule(schedule_selector(BowManStoryScene::update3));
		cocos2d::log("Stop schedule story3");
		story4();
		//this->schedule(schedule_selector(BowManStoryScene::update4), delayTimeStory4);
	}
}

void BowManStoryScene::update4(float dt)
{
	// Xu ly story4 chay xong thi chuyen qua story5

}
*/

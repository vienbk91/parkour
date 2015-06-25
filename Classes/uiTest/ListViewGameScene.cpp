#include "ListViewGameScene.h"

#define MARGIN 20
#define BUTTON_COUNT 15

USING_NS_CC;

Scene* ListViewGameScene::createScene()
{
	// Xet kich thuoc hien thi cho tung game bang cach set DesignResolutionSize cua no
	Director::getInstance()->getOpenGLView()->setDesignResolutionSize(480, 320, ResolutionPolicy::SHOW_ALL);
    
	auto scene = Scene::create();
    auto layer = ListViewGameScene::create();
    scene->addChild(layer);

    return scene;
}

bool ListViewGameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	createBack();
	//////////////////////////////////////////////////////////////////////////////////////////////////
	// Khoi tao listView voi thu vien UI
	//////////////////////////////////////////////////////////////////////////////////////////////////


	ui::ListView* listViewUI = ui::ListView::create();
	ui::Button* buttonUI = ui::Button::create();

	for (int i = 0; i < BUTTON_COUNT ; ++i)
    {
		if (i == 0)
		{
			std::string ccstr = StringUtils::format("Parkour Game");
			_array.push_back(ccstr);
		}
		else if (i == 1)
		{
			std::string ccstr = StringUtils::format("Enemy Kill Game");
			_array.push_back(ccstr);
		}
		else if (i == 2)
		{
			std::string ccstr = StringUtils::format("Loading Scene");
			_array.push_back(ccstr);
		}
		else if (i == 3)
		{
			std::string ccstr = StringUtils::format("Register Form");
			_array.push_back(ccstr);
		}
		else if (i == 4)
		{
			std::string ccstr = StringUtils::format("Box2D Test");
			_array.push_back(ccstr);
		}
		else if (i == 5)
		{
			std::string ccstr = StringUtils::format("ScrollView Test");
			_array.push_back(ccstr);
		}
		else if (i == 6)
		{
			std::string ccstr = StringUtils::format("HttpRequest Test");
			_array.push_back(ccstr);
		}
		else if (i == 7)
		{
			std::string ccstr = StringUtils::format("Sound Test");
			_array.push_back(ccstr);
		}
		else if (i == 8)
		{
			std::string ccstr = StringUtils::format("PageView Test");
			_array.push_back(ccstr);
		}
		else if (i == 9)
		{
			std::string ccstr = StringUtils::format("CocoStudio Test");
			_array.push_back(ccstr);
		}
		else
		{
			std::string ccstr = StringUtils::format("listview_item_%d", i + 1);
			_array.push_back(ccstr);
		}
        
    }

	buttonUI->loadTextures("uitest_img/start.png" , "uitest_img/start.png" , "");

	listViewUI->setItemModel(buttonUI);

	for(int i = 0 ; i < BUTTON_COUNT ; i++){

		buttonUI->setTitleText(_array[i]);
		listViewUI->pushBackDefaultItem();
	}
    
	listViewUI->setItemsMargin(MARGIN); // Khoang cach giua cac item trong list view
	listViewUI->setGravity(ListView::Gravity::CENTER_HORIZONTAL); // Trong luc
	cocos2d::log("Height : %f " , buttonUI->getContentSize().height * BUTTON_COUNT + MARGIN * BUTTON_COUNT );
	listViewUI->setContentSize(Size(visibleSize.width - 100 , visibleSize.height - 100) ); // kich thuoc mat na cua list view
	listViewUI->setBackGroundColorType(Layout::BackGroundColorType::SOLID); // solid : ran, dac , dong mau
	listViewUI->setBackGroundColor(Color3B::GREEN);
	listViewUI->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	listViewUI->setPosition(Vec2(visibleSize.width / 2  , visibleSize.height / 2 ));

	this->addChild(listViewUI);

	listViewUI->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ListViewGameScene::selectedItemEvent, this));

    return true;
}


void ListViewGameScene::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
        {
            ui::ListView* listView = static_cast<ui::ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
           
			int itemClickedIndex = listView->getCurSelectedIndex();

			if(itemClickedIndex == 0){
				cocos2d::log("Parkour Game");
				auto parkourScene = ParkourMenu::createScene();
				Director::getInstance()->replaceScene(parkourScene);
			}
			if(itemClickedIndex == 1){
				cocos2d::log("Enemy Kill Game");
				auto enemyGame = EnemyKillScene::createScene();
				Director::getInstance()->replaceScene(enemyGame);
			}
			if(itemClickedIndex  == 2){
				cocos2d::log("Loading Scene");
				auto loading = LoadingScene::createScene();
				Director::getInstance()->replaceScene(loading);
			}
			if(itemClickedIndex  == 3){
				cocos2d::log("Register Form");
				auto registerForm = RegisterFormScene::createScene();
				Director::getInstance()->replaceScene(registerForm);
			}
			if(itemClickedIndex  == 4){
				cocos2d::log("Box2DTest Form");
				auto box2DTest = Box2DTest::createScene();
				Director::getInstance()->replaceScene(box2DTest);
			}
			if (itemClickedIndex == 5){
				cocos2d::log("ScrollView Test");
				auto box2DTest = ScrollViewScene::createScene();
				Director::getInstance()->replaceScene(box2DTest);
			}
			if (itemClickedIndex == 6){
				cocos2d::log("HttpRequest Test");
				auto httpRequest = HttpRequestTest::createScene();
				Director::getInstance()->replaceScene(httpRequest);
			}
			if (itemClickedIndex == 7){
				cocos2d::log("Sound Test");
				auto soundTest = SoundTest::createScene();
				Director::getInstance()->replaceScene(soundTest);
			}
			if (itemClickedIndex == 8){
				cocos2d::log("PageView Test");
				auto pageViewTest = PageViewTest::createScene();
				Director::getInstance()->replaceScene(pageViewTest);
			}
			if (itemClickedIndex == 9){
				cocos2d::log("Cocos Studio Test");
				auto cocosStudioTest = CocosStudioTest::createScene();
				Director::getInstance()->replaceScene(cocosStudioTest);
			}

            break;
        }
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            break;
        }
        default:
            break;
    }
}

void ListViewGameScene::createBack()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto menuBackButton = MenuItemImage::create(
		"enemykill_img/back_btn.png",
		"enemykill_img/back_btn1.png",
		CC_CALLBACK_1(ListViewGameScene::backCallback, this)
		);

	menuBackButton->setScale(0.25f);
	menuBackButton->setPosition(Vec2(
		-10 + menuBackButton->getContentSize().width / 2, 
		10 + visibleSize.height - menuBackButton->getContentSize().height / 2));
	Menu* menuBack = Menu::create(menuBackButton, NULL);
	menuBack->setAnchorPoint(Vec2::ZERO);
	menuBack->setPosition(Vec2::ZERO);

	this->addChild(menuBack);
}

void ListViewGameScene::backCallback(Ref* pSender){
	auto listView = BowManMainScene::createScene();
	Director::getInstance()->replaceScene(listView);
}

#pragma execution_character_set("utf-8") // Hien thi tieng nhat

#include "uiTest\PageViewTest.h"

USING_NS_CC;
using namespace ui;

#define WINSIZE Director::getInstance()->getVisibleSize()


Scene* PageViewTest::createScene()
{
	auto scene = Scene::create();
	auto layer = PageViewTest::create();

	scene->addChild(layer);

	return scene;
}

bool PageViewTest::init()
{
	if (!Layer::init())
	{
		return false;
	}


	// PageView を作成これにレイアウトを追加していく
	auto pageView = PageView::create();
	pageView->setTouchEnabled(true);
	pageView->setContentSize(Size(WINSIZE.width - 200 , WINSIZE.height - 100));
	pageView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	pageView->setPosition(Vec2(WINSIZE.width/2 , WINSIZE.height/2 ));
	pageView->setBackGroundColor(Color3B::GREEN);
	pageView->setBackGroundColorType(Layout::BackGroundColorType::SOLID);


	// 3ページ作成する
	int pageCount = 7;
	for (int i = 0; i < pageCount ; i++)
	{

		// レイアウトを作成
		auto layout = Layout::create();
		layout->setContentSize(Size(WINSIZE.width/2 , WINSIZE.height/2));


		// 画像
		auto imageView = ImageView::create("uiTest_img/HelloWorld.png");
		imageView->setScale(
			float(layout->getContentSize().width / imageView->getContentSize().width) , 
			float(layout->getContentSize().height / imageView->getContentSize().height)
			);
		imageView->setAnchorPoint(Vec2::ZERO);
		layout->addChild(imageView);

		// テキスト
		auto label = Text::create(StringUtils::format("%dページ", (i + 1)), "fonts/syunka2pbb.ttf" , 30);
		label->setColor(Color3B(Color3B::BLUE));
		label->setPosition(Vec2(layout->getContentSize().width / 2 , layout->getContentSize().height / 2));


		layout->addChild(label);
		pageView->insertPage(layout , i);

	}

	pageView->addEventListenerPageView(this, pagevieweventselector(PageViewTest::pageViewCallback));
    
    this->addChild(pageView);

	return true;
}


void PageViewTest::pageViewCallback(Ref* pSender, ui::PageViewEventType type)
{
	if (type == ui::PageViewEventType::PAGEVIEW_EVENT_TURNING)
	{
		auto pageView = dynamic_cast<ui::PageView*>(pSender);
		log("%d ", pageView->getCurPageIndex() + 1);
	}
}
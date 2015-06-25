#include "uiTest\SelectMenuTest.h"

USING_NS_CC;
using namespace ui;

#define winsize Director::getInstance()->getVisibleSize()


Scene* SelectMenuTest::createScene()
{
	auto scene = Scene::create();
	auto layer = SelectMenuTest::create();

	scene->addChild(layer);
	return scene;
}

bool SelectMenuTest::init()
{
	if (!Layer::init())
	{
		return false;
	}

	// PageView create
	auto menuPageView = PageView::create();
	menuPageView->setTouchEnabled(true);
	menuPageView->setContentSize(Size(winsize.width - 200 , winsize.height-100));
	menuPageView->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	menuPageView->setPosition(Vec2(winsize.width / 2, winsize.height / 2));
	menuPageView->setBackGroundColor(Color3B::GRAY);
	menuPageView->setBackGroundColorType(PageView::BackGroundColorType::SOLID);

	int pageCount = 3;
	for (int i = 0; i < pageCount ; i++)
	{
		auto layout = Layout::create();
		layout->setContentSize(menuPageView->getContentSize());

		// 画像
		button1 = Sprite::create();
		button2 = Sprite::create();
		button3 = Sprite::create();

		button1->setTexture("uitest_img/3.png");
		button2->setTexture("uitest_img/1.png");
		button3->setTexture("uitest_img/2.png");
		
		button1->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		button2->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
		button3->setAnchorPoint(Vec2::ANCHOR_MIDDLE);

		button1->setPosition(Vec2::ZERO);
		button2->setPosition(layout->getContentSize().width / 2, layout->getContentSize().height / 2);
		button3->setPosition(winsize.width - 120 , 0);

		// テキスト
		auto label = Text::create(StringUtils::format("%dページ", (i + 1)), "fonts/syunka2pbb.ttf", 30);
		label->setColor(Color3B(Color3B::BLUE));
		label->setPosition(Vec2(winsize.width - 100 , 50));

		layout->addChild(button1);
		layout->addChild(button2);
		layout->addChild(button3 ,99 );

		layout->addChild(label);
		menuPageView->insertPage(layout, i);
	}

	menuPageView->addEventListenerPageView(this, pagevieweventselector(SelectMenuTest::pageViewCallback));

	this->addChild(menuPageView);

	this->scheduleUpdate();

	return true;
}

void SelectMenuTest::pageViewCallback(Ref* pSender, ui::PageViewEventType type)
{
	if (type == ui::PageViewEventType::PAGEVIEW_EVENT_TURNING)
	{
		auto pageView = dynamic_cast<ui::PageView*>(pSender);
		log("%d ", pageView->getCurPageIndex() + 1);
		index = pageView->getCurPageIndex();

		this->scheduleUpdate();
	}
}

void SelectMenuTest::update(float dt)
{
	log("index = %d", index);

	if (index = 0)
	{
		button1->setTexture("uitest_img/3.png");
		button2->setTexture("uitest_img/1.png");
		button3->setTexture("uitest_img/2.png");

	}
	if (index == 1)
	{
		button1->setTexture("uitest_img/1.png");
		button2->setTexture("uitest_img/2.png");
		button3->setTexture("uitest_img/3.png");
	}
	if (index == 2)
	{
		button1->setTexture("uitest_img/2.png");
		button2->setTexture("uitest_img/3.png");
		button3->setTexture("uitest_img/1.png");
	}
}
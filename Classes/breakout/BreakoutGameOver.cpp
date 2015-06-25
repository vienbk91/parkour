#include "breakout\BreakoutGameOver.h"

USING_NS_CC;


BreakoutGameOver::BreakoutGameOver()
{
}

BreakoutGameOver::~BreakoutGameOver()
{
}


BreakoutGameOver* BreakoutGameOver::create(const Color4B& color , int offset)
{
	BreakoutGameOver* scene = new BreakoutGameOver();
	if(scene && scene->initWithColor(color,offset))
	{
		scene->autorelease();
		return scene;
	}
	CC_SAFE_DELETE(scene);

	return NULL;
}

bool BreakoutGameOver::initWithColor(const Color4B& color , int offset)
{
	if(!LayerColor::initWithColor(color))
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();

	_offset = offset;

	cocos2d::log("Diem: %d" , offset);

	auto labelScore = LabelTTF::create("Score : " , "Arial" , 50);
	labelScore->setFontSize(50);
	labelScore->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	labelScore->setPosition(Vec2(visibleSize.width/2 , visibleSize.height /2));

	std::stringstream text;
	text << "Score : " << _offset << std::endl;
	cocos2d::log("%s", text.str().c_str());

	labelScore->setString(text.str().c_str());

	this->addChild(labelScore);

	return true;
}
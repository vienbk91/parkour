#include "sushiCrush\SushiSprite.h"

USING_NS_CC;

#define TOTAL_SUSHI 6

// Tao ra 1 mang con tro, moi con tro tro toi 1 chuoi
// sushiNomal[i] lua dia chi cua chuoi i
static const char* sushiNomal[TOTAL_SUSHI] = {
	"sushi_1n.png",
	"sushi_2n.png",
	"sushi_3n.png",
	"sushi_4n.png",
	"sushi_5n.png",
	"sushi_6n.png"
};

float SushiSprite::getContentWidth()
{
	static float itemWidth = 0;
	if (itemWidth == 0)
	{
		// Tao ra 1 mang sushi tu mang tren
		auto sprite = Sprite::createWithSpriteFrameName(sushiNomal[0]);
		itemWidth = sprite->getContentSize().width;
	}

	return itemWidth;
}

// Tao 1 sushi co vi tri row ,col va tra ve 1 con tro kieu SushiSprite
SushiSprite* SushiSprite::create(int row, int col)
{
	// Tao moi sushi
	SushiSprite* sushi = new SushiSprite();
	sushi->m_row = row;
	sushi->m_col = col;

	sushi->m_imgIndex = rand() % TOTAL_SUSHI; // Random sushi tu 0 den 5

	// Tao hinh anh tu chuoi cua mang tren
	sushi->initWithSpriteFrameName(sushiNomal[sushi->m_imgIndex]);
	sushi->autorelease(); // Tu dong huy khi can thiet

	return sushi;
}
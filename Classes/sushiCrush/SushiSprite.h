#ifndef _SUSHISPRITE_H_
#define _SUSHISPRITE_H_

#include "cocos2d.h"


USING_NS_CC;

class SushiSprite : public cocos2d::Sprite
{
public:
	static SushiSprite* create(int row, int col); // Tao 1 sushi theo hang,cot cua ma tran
	static float getContentWidth(); // Lay chieu rong cua sprite sushi

	/*
	CC_SYNTHESIZE(int, m_row, Row); dung de tao ra 1 bien m_row co kieu int thong qua 1 phuong thuc cua lop Row
	*/

	CC_SYNTHESIZE(int, m_row, Row); // Vi tri cot cua sushi trong ma tran
	CC_SYNTHESIZE(int, m_col, Col); // Vi tri hang cua sushi trong ma tran
	CC_SYNTHESIZE(int, m_imgIndex, ImgIndex); // Loai sushi

private:

};

#endif /* _SUSHISPRITE_H_ */
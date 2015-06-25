#ifndef _PLAYLAYER_H_
#define _PLAYLAYER_H_

#include "cocos2d.h"
#include "sushiCrush\SushiSprite.h"

USING_NS_CC;

class PlayLayer : public cocos2d::Layer
{
public:
	static Scene* createScene(); // Tao man choi
	
	CREATE_FUNC(PlayLayer);

	// Khoi tao
	virtual bool init() override;

private:
	// SpriteSheet dung de luu cac loat anh tao animation
	SpriteBatchNode* spriteSheet;

	// Ma tran 2 chieu dung con tro cap 2 de luu SushiSprite
	SushiSprite **m_matrix;

	// Kich thuoc ma tran, hang ,cot
	int m_width;
	int m_height;

	// Vi tri can chinh tren man hinh
	float m_matrixLeftBottomX;
	float m_matrixLeftBottomY;

	// Ham tao ma tran
	void initMatrix();


	// Tao sushi va cho roi xuong o vi tri hang cot bat ki
	void createAndDropSushi(int row, int col);

	// Tra lai vi tri toa do cua sushi tai vi tri hang cot trong ma tran
	Vec2 positionOfItem(int row, int col);

};

#endif /* _PLAYLAYER_H_ */
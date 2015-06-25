#ifndef BREAKOUTGAMEOVER_H_
#define BREAKOUTGAMEOVER_H_

#include "cocos2d.h"

USING_NS_CC;


class BreakoutGameOver : public cocos2d::LayerColor
{
public:
	BreakoutGameOver();
	~BreakoutGameOver();

	static BreakoutGameOver* create(const Color4B& color , int offset);
	bool initWithColor(const Color4B& color , int offset);

private:
	int _offset;
};

#endif BREAKOUTGAMEOVER_H_
/*
 * ParkourGameOver.h
 *
 *  Created on: 2015/01/30
 *      Author: chu
 */

#ifndef PARKOURGAMEOVER_H_
#define PARKOURGAMEOVER_H_

#include "cocos2d.h"
#include "extensions\cocos-ext.h"
#include "ui\CocosGUI.h"
#include "uiTest\ListViewGameScene.h"

USING_NS_CC;
USING_NS_CC_EXT;
using namespace ui;

class ParkourGameOver : public LayerColor
{
public:

	static ParkourGameOver* create(const Color4B& color);
	bool initWithColor(const Color4B& color);
private:
	void createDebug();
	virtual void rebootCallback(Ref *pSEnder);
};


#endif /* PARKOURGAMEOVER_H_ */

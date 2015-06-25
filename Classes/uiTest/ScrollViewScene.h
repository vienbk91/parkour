/*
 * MenuScene.h
 *
 *  Created on: 2015/01/16
 *      Author: chu
 */

#ifndef SCROLLVIEWSCENE_H_
#define SCROLLVIEWSCENE_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "extensions\cocos-ext.h"
#include "parkour\PlayScene.h"
#include "parkour\ParkourMenu.h"
#include "ListViewGameScene.h"


USING_NS_CC;
USING_NS_CC_EXT;


using namespace ui;
using namespace extension;

class ScrollViewScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(ScrollViewScene);


private:
	void startCallback(Ref* pSender);
};



#endif /* SCROLLVIEWSCENE_H_ */

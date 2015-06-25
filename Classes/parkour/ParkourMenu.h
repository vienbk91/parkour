/*
 * PaukourMenu.h
 *
 *  Created on: 2015/01/29
 *      Author: chu
 */

#ifndef PAUKOURMENU_H_
#define PAUKOURMENU_H_

#include "cocos2d.h"
#include "PlayScene.h"
#include "uiTest\ListViewGameScene.h"

class ParkourMenu : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(ParkourMenu);

    void onPlay(Ref* pSender);

	void backCallback(Ref* pSender);
};


#endif /* PAUKOURMENU_H_ */

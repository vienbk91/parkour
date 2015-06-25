/*
 * ListViewGameScene.h
 *
 *  Created on: 2015/02/02
 *      Author: chu
 */

#ifndef LISTVIEWGAMESCENE_H_
#define LISTVIEWGAMESCENE_H_

#include "cocos2d.h"
#include "ui\CocosGUI.h"
#include "ui\UIButton.h"
#include "uiTest\ScrollViewScene.h"
#include "parkour\ParkourMenu.h" 
#include "enemyKill\EnemyKillScene.h" 
#include "sqlTest\RegisterFormScene.h" 
#include "uiTest\LoadingScene.h"
#include "box2DTest\Box2DTest.h"
#include "bowman\BowManMainScene.h"
#include "httpRequest\HttpRequestTest.h"
#include "soundTest\SoundTest.h"
#include "uiTest\PageViewTest.h"
#include "cocosStudioTest\CocosStudioTest.h"

USING_NS_CC;

using namespace ui;
using namespace std;

class ListViewGameScene : public cocos2d::Layer
{
public:

    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(ListViewGameScene);

	void selectedItemEvent(Ref *pSender, ListView::EventType type);

protected:
	 std::vector<std::string> _array;
	 void createBack();
	 void backCallback(Ref* pSender);

};


#endif /* LISTVIEWGAMESCENE_H_ */

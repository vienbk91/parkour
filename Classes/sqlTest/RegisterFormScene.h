/*
 * RegisterFormScene.h
 *
 *  Created on: 2015/02/03
 *      Author: chu
 */

#ifndef REGISTERFORMSCENE_H_
#define REGISTERFORMSCENE_H_

#include "cocos2d.h"
#include "ui\UIEditBox\UIEditBox.h"
#include "uiTest\ListViewGameScene.h"
#include "sqlite\sqlite3.h"

USING_NS_CC;
using namespace std;
using namespace cocos2d;


class RegisterFormScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();


    CREATE_FUNC(RegisterFormScene);

protected:

	ui::EditBox* editName;
	ui::EditBox* editPassword;
	ui::EditBox* editEmail;



	void registerCallback(Ref* pSender);
	void cancelCallback(Ref* pSender);


	void createDB();
};


#endif /* REGISTERFORMSCENE_H_ */

#ifndef BOWMANMENUSCENE_H_
#define BOWMANMENUSCENE_H_

#include "cocos2d.h"
#include "BowManHightScore.h"
#include "BowManInforGame.h"
#include "BowManPlayGameScene.h"
#include "BowManSelectMap.h"
#include "BowManStoryScene.h"

#include "ui\CocosGUI.h"
#include "bowman\SqlUtils.h"
#include "uiTest\ListViewGameScene.h"



USING_NS_CC;

class BowManMenuScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();

	CREATE_FUNC(BowManMenuScene);

	ui::EditBox* inputName;

	void startGameCallBack(Ref* pSender);
	void scoreGameCallBack(Ref* pSender);
	void helpGameCallBack(Ref* pSender);
	void soundGameCallBack(Ref* pSender);
	void inforGameCallBack(Ref* pSender);
	void menuCallback(Ref* pSender);


	void createInputDialog();
	void inputNameCallback(Ref* pSender);
	void createDB();
	bool insertNameToDB(string userName);

};

#endif /* BOWMANMENUSCENE_H_ */

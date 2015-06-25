/*
 * LoadingScene.h
 *
 *  Created on: 2015/03/29
 *      Author: Chu Quang Vien
 */

#ifndef LOADINGSCENE_H_
#define LOADINGSCENE_H_

#include "cocos2d.h"
#include "WelcomeScene.h"

USING_NS_CC;

class LoadingScene : public cocos2d::Layer
{
public:
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(LoadingScene);

private:
	virtual void moveCallback(Ref* pSender);

protected:
};


#endif /* LOADINGSCENE_H_ */

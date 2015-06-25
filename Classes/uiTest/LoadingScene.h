#ifndef __LOADINGSCENE_H__
#define __LOADINGSCENE_H__

#include "cocos2d.h"
#include "uiTest\ScrollViewScene.h"

class LoadingScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    
    CREATE_FUNC(LoadingScene);


	void update(float delta);

};

#endif // __LOADINGSCENE_H__
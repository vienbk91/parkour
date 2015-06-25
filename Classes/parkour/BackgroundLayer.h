/*
 * BachgroundLayer.h
 *
 *  Created on: 2015/01/19
 *      Author: chu
 */

#ifndef BACHGROUNDLAYER_H_
#define BACHGROUNDLAYER_H_


#include "cocos2d.h"
#include "parkour\RunnerSprite.h"
#include "Global.h"
#include "Coin.h"
#include "Rock.h"

class BackgroundLayer : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();

    CREATE_FUNC(BackgroundLayer);

	//TMXTiledMap* map1;
	//TMXTiledMap* map2;

	//float mapWidth;
	//int mapIndex;


	//void createBackground();
};

#endif /* BACHGROUNDLAYER_H_ */

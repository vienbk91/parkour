/*
 * Rock.cpp
 *
 *  Created on: 2015/01/28
 *      Author: chu
 */


#include "parkour\Rock.h"

USING_NS_CC;

Rock* Rock::create(){
	auto rockSprite = new Rock();
	rockSprite->initWithFile("parkour_img/rock.png");
	rockSprite->autorelease();


	return rockSprite;
}

void Rock::onEnter(){

	Sprite::onEnter();

}
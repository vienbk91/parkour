/*
 * Rock.h
 *
 *  Created on: 2015/01/28
 *      Author: chu
 */

#ifndef ROCK_H_
#define ROCK_H_

#include "cocos2d.h"
#include "parkour\Global.h"


class Rock : public cocos2d::Sprite
{
public :

	static Rock* create();
	void onEnter();
};

#endif /* ROCK_H_ */

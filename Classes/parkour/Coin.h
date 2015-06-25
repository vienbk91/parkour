/*
 * Coin.h
 *
 *  Created on: 2015/01/28
 *      Author: chu
 */

#ifndef COIN_H_
#define COIN_H_

#include "cocos2d.h"

class Coin : public cocos2d::Sprite
{
public:

    static Coin* create();

    void onEnter();
};

#endif /* COIN_H_ */

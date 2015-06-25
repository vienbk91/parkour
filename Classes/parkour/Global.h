/*
 * Global.h
 *
 *  Created on: 2015/01/19
 *      Author: chu
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

enum TagOfLayer{
	BACKGROUND_LAYER = 0 ,
	STATUS_LAYER = 2
};

enum TagOfSprite{
	RUNNER_SPRITE = 0,
	COIN_SPRITE = 1,
	ROCK_SPRITE = 2 ,
	LINE_STOP = 3,
};

class Global{
public:
	// 地面の高さ
	static const float g_groundHeight;

	//プレーヤーの最初のＸ座標
	static const float g_runnerStartX;
};


#endif /* GLOBAL_H_ */

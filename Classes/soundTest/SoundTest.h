#ifndef _SOUNDTEST_H_
#define _SOUNDTEST_H_

#include "cocos2d.h"
#include "SimpleAudioEngine.h" // Thu vien quan ly am thanh

USING_NS_CC;

class SoundTest : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();
	CREATE_FUNC(SoundTest);


	void menuCloseCallback(Ref* pSender);

	unsigned int soundId;
	bool isEffectPlaying;
private:

};



#endif /* _SOUNDTEST_H_ */
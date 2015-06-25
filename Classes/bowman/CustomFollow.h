#ifndef _CUSTOMFOLLOW_H_
#define _CUSTOMFOLLOW_H_

#include "cocos2d.h"

USING_NS_CC;

enum CustomFollowType{
	kCustomFollowNone ,
	kCustomFollowXOnly ,
	kCustomFollowYOnly
};

class CustomFollow : public cocos2d::Follow
{
public:
	
	static CustomFollow* create(Node* followNode);
	static CustomFollow* create(Node* followNode , CustomFollowType type);
	static CustomFollow* create(Node* followNode , Rect marginRect);
	static CustomFollow* create(Node* followNode, CustomFollowType type, Rect marginRect);


	virtual void step(float dt) override;

private:
	CustomFollowType _type;
	Rect _marginRect;

	CustomFollow();
	~CustomFollow();
};

#endif /* _CUSTOMFOLLOW_H_ */
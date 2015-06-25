#include "bowman\CustomFollow.h"

CustomFollow::CustomFollow()
{
	_type = kCustomFollowNone;
	_marginRect = Rect::ZERO;
}

CustomFollow::~CustomFollow()
{
	CC_SAFE_RELEASE(_followedNode);
}

CustomFollow* CustomFollow::create(Node* followNode)
{
	CustomFollow* follow = new CustomFollow();

	if (follow && follow->initWithTarget(followNode, Rect::ZERO))
	{
		follow->autorelease();
		return follow;
	}

	CC_SAFE_DELETE(follow);
	return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, CustomFollowType type)
{
	CustomFollow* follow = new CustomFollow();
	follow->_type = type;
	if ( follow && follow->initWithTarget(followNode , Rect::ZERO))
	{
		follow->autorelease();
		return follow;
	}
	CC_SAFE_DELETE(follow);
	return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, Rect marginRect)
{
	CustomFollow* follow = new CustomFollow();
	follow->_marginRect = marginRect;
	if (follow && follow->initWithTarget(followNode , Rect::ZERO))
	{
		follow->autorelease();
		return follow;
	}
	CC_SAFE_DELETE(follow);
	return nullptr;
}

CustomFollow* CustomFollow::create(Node* followNode, CustomFollowType type , Rect marginRect)
{
	CustomFollow* follow = new CustomFollow();
	follow->_type = type;
	follow->_marginRect = marginRect;
	if (follow && follow->initWithTarget(followNode, Rect::ZERO))
	{
		follow->autorelease();
		return follow;
	}
	CC_SAFE_DELETE(follow);
	return nullptr;
}

void CustomFollow::step(float dt)
{
	CC_UNUSED_PARAM(dt);

	if (_boundarySet) // Co ton tai ranh gioi
	{
		if (_boundaryFullyCovered)
		{
			return;
		}

		Vec2 tempPos = _halfScreenSize - _followedNode->getPosition();
		// clamf: ham dung de co dinh 1 gia tri nam giua min va max
		// clamf(value , min , max)
		float x = clampf(tempPos.x, _leftBoundary, _rightBoundary);
		float y = clampf(tempPos.y, _bottomBoundary, _topBoundary);

		if (_type == kCustomFollowXOnly)
		{
			// Neu chi follow theo chieu X thi Y bang voi y cua target
			y = _target->getPositionY();
		}
		else if (_type == kCustomFollowYOnly)
		{
			// Neu chi follow theo chieu Y thi X bang x cua target
			x = _target->getPositionX();
		}

		// Neu khong thi set ca 2
		_target->setPosition(Vec2(x, y));

	}
	else
	{
		Vec2 calcPos = _target->convertToWorldSpace(_followedNode->getPosition());

		if (_marginRect.containsPoint(calcPos)){
			return;
		}

		float x = _halfScreenSize.x - _followedNode->getPositionX();
		float y = _halfScreenSize.y - _followedNode->getPositionY();

		//float x = _followedNode->getPositionX();
		//float y = _followedNode->getPositionY();


		if (_type == kCustomFollowXOnly){
			y = _target->getPositionY();
			//log("tarY = %f ", y);
		}
		else if (_type == kCustomFollowYOnly){
			x = _target->getPositionX();
		}

		_target->setPosition(Vec2(x, y));
		//log("tarX= %f , tarY = %f ", _target->getPositionX(), _target->getPositionY());
	}
}
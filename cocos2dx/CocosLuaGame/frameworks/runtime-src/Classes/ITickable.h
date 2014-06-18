#ifndef ITickable_h__
#define ITickable_h__

#include "cocos2d.h"

class ITickable : public cocos2d::Ref
{
public:
	ITickable()
	{
		cocos2d::Director::getInstance()->getScheduler()->scheduleUpdate(this, 0, false);
	}

	virtual ~ITickable()
	{
		cocos2d::Director::getInstance()->getScheduler()->unscheduleAllForTarget(this);
	}

	virtual void update(float dt) = 0;

};

#endif // ITickable_h__

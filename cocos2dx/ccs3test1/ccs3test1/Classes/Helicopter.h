#ifndef Helicopter_h__
#define Helicopter_h__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "B2Sprite.h"

class Helicopter : public B2Sprite
{
public:
	static Helicopter *createBody(b2World *world, const cocos2d::Point &point, float fPTMRatio);

	CC_SYNTHESIZE(bool, m_bFlying, Flying);
	CC_SYNTHESIZE(float, m_velocity, Velocity);
	CC_SYNTHESIZE(cocos2d::Point, m_targetPoint, TargetPoint);
};

#endif // Helicopter_h__

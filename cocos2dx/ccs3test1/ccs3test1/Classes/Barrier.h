#ifndef Barrier_h__
#define Barrier_h__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "B2Sprite.h"

class Barrier : public B2Sprite
{
public:
	virtual ~Barrier();
	static Barrier *createBody(b2World *world, const cocos2d::Point &point, float fPTMRatio);

	CC_SYNTHESIZE(cocos2d::Point, m_mapPosition, MapPosition);
};

#endif // Barrier_h__

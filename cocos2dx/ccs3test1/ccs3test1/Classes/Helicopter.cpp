#include "Helicopter.h"

USING_NS_CC;

Helicopter *Helicopter::createBody(b2World *world, const cocos2d::Point &point, float fPTMRatio)
{
	CCASSERT(world != nullptr, "create helicopter failed: null world");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x / fPTMRatio, point.y / fPTMRatio);

	auto body = world->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = 20.0f / fPTMRatio;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = false;	// important
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);

	auto heli = new Helicopter;
	if (heli && heli->initWithFile("CloseSelected.png"))
	{
		heli->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(heli);
		return nullptr;
	}

	body->SetUserData(heli);

	heli->setB2Body(body);
	heli->setPTMRatio(fPTMRatio);
	heli->setPosition(point);

	heli->setType(kB2SpriteTypeHelicopter);
	heli->setGroup(kB2SpriteTypeNone);
	heli->setFlying(false);
	heli->setVelocity(0.0f);

	return heli;
}


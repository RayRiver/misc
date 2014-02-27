#include "Barrier.h"

USING_NS_CC;

Barrier *Barrier::createBody(b2World *world, const cocos2d::Point &point, const cocos2d::Size &size, float fPTMRatio)
{
	CCASSERT(world != nullptr, "create Barrier failed: null world");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x / fPTMRatio, point.y / fPTMRatio);

	auto body = world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	shape.SetAsBox(size.width / fPTMRatio, size.height / fPTMRatio);
	//b2CircleShape shape;
	//shape.m_radius = 20.0f / fPTMRatio;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;	// important
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);

	auto sprite = new Barrier;
	if (sprite && sprite->init())
	{
		sprite->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	sprite->setContentSize(size);
	sprite->setB2Body(body);
	sprite->setPTMRatio(fPTMRatio);
	sprite->setPosition(point);


	return sprite;
}

Barrier::~Barrier()
{
	auto body = this->getB2Body();
	if (body)
	{
		auto world = body->GetWorld();
		world->DestroyBody(body);
		this->setB2Body(nullptr);
	}
}


EdgeBox * EdgeBox::createBody(b2World *world, const cocos2d::Point &point, float fPTMRatio, float &link_height)
{
	CCASSERT(world != nullptr, "create EdgeBox failed: null world");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x / fPTMRatio, point.y / fPTMRatio);

	

	auto body = world->CreateBody(&bodyDef);
	b2PolygonShape shape;
	//b2Vec2 verts[] = {
	//	{1.0f, 1.0f}
	//};
	//shape.Set(verts, 4);

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;	// important
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);

	auto sprite = new EdgeBox;
	if (sprite && sprite->init())
	{
		sprite->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	sprite->setB2Body(body);
	sprite->setPTMRatio(fPTMRatio);
	sprite->setPosition(point);


	return sprite;
}

EdgeBox::~EdgeBox()
{
	auto body = this->getB2Body();
	if (body)
	{
		auto world = body->GetWorld();
		world->DestroyBody(body);
		this->setB2Body(nullptr);
	}
}

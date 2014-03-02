#include "Bullet.h"

using namespace std;
USING_NS_CC;

Bullet::Bullet()
	: m_velocity(Vect::ZERO)
{

}

BulletManager* BulletManager::createWithTexture(Texture2D* tex, ssize_t capacity/* = DEFAULT_CAPACITY*/)
{
	BulletManager *batchNode = new BulletManager();
	batchNode->initWithTexture(tex, capacity);
	batchNode->autorelease();

	return batchNode;
}

BulletManager* BulletManager::create(const std::string& fileImage, ssize_t capacity/* = DEFAULT_CAPACITY*/)
{
	BulletManager *batchNode = new BulletManager();
	batchNode->initWithFile(fileImage, capacity);
	batchNode->autorelease();

	return batchNode;
}

BulletManager::BulletManager()
{
	this->setPosition(Point::ZERO);
}

BulletManager::~BulletManager()
{

}

Bullet * BulletManager::createObject( const cocos2d::Point &point )
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x / m_fPTMRatio, point.y / m_fPTMRatio);

	auto body = m_world->CreateBody(&bodyDef);
	b2CircleShape circle;
	circle.m_radius = 3.0f / m_fPTMRatio;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = true;	// important
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);

	auto sprite = new Bullet;
	if (sprite && sprite->initWithTexture(this->getTexture()))
	{
		sprite->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(sprite);
		return nullptr;
	}

	body->SetUserData(sprite);

	sprite->setB2Body(body);
	sprite->setPTMRatio(m_fPTMRatio);
	sprite->setPosition(point);


	sprite->setType(kB2SpriteTypeBullet);
	sprite->setGroup(kB2SpriteTypeNone);
	this->addChild(sprite);
	return sprite;
}

void BulletManager::destroyObject( Bullet *object )
{
	m_unused.push_back(object);
}

void BulletManager::update( float dt )
{
	for (vector<B2Sprite *>::iterator it=m_unused.begin(); it!=m_unused.end(); ++it)
	{
		auto sprite = *it;
		m_world->DestroyBody(sprite->getB2Body());
		this->removeChild(sprite, true);
	}
	m_unused.clear();
}

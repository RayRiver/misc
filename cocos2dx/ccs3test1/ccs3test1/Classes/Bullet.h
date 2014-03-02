#ifndef Bullet_h__
#define Bullet_h__

#include <vector>

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#include "B2Sprite.h"

class BulletManager;
class Bullet : public B2Sprite
{
	friend class BulletManager;

public:
	Bullet();
	CC_SYNTHESIZE(cocos2d::Vect, m_velocity, Velocity);
};

class BulletManager : public cocos2d::SpriteBatchNode
{
public:
	BulletManager();
	virtual ~BulletManager();

	static BulletManager* createWithTexture(cocos2d::Texture2D* tex, ssize_t capacity = 29);
    static BulletManager* create(const std::string& fileImage, ssize_t capacity = 29);

	CC_SYNTHESIZE(b2World *, m_world, World);
	CC_SYNTHESIZE(float, m_fPTMRatio, PTMRatio);
	
	Bullet *createObject(const cocos2d::Point &point);
	void destroyObject(Bullet *object);
	void update(float dt);

private:
	std::vector<B2Sprite *> m_unused;
};

#endif // Bullet_h__

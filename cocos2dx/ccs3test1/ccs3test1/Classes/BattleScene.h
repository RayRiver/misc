#ifndef BattleScene_h__
#define BattleScene_h__

#include <map>
#include <vector>

#include "cocos2d.h"
#include "box2d/Box2D.h"

#include "Helicopter.h"
#include "Bullet.h"

class BattleScene 
	: public cocos2d::Layer
	, public b2ContactListener
{
public:
	static cocos2d::Scene* createScene();
	CREATE_FUNC(BattleScene);

	BattleScene();
	virtual ~BattleScene();

	virtual bool init();  
	virtual void update(float dt);
	virtual void draw();

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

	void initPhysics();
	void setPhysicsDebug(bool bPhysicsDebug);

protected:
	kmMat4 m_modelViewMV;
	cocos2d::CustomCommand m_customCommand;
	b2Draw *m_debugDraw;

	b2World *m_world;
	Helicopter *m_player;
	Helicopter *m_enemy;
	BulletManager *m_bulletManager;


	float PTM_RATIO;
	float RISE_ACCELERATION;
	float FALL_ACCELERATION;
	float MAX_RISE_VELOCITY;
};

#endif // BattleScene_h__
#include "BattleScene.h"

#include <vector>

#include "Config.h"
#include "GLES-Render.h"
#include "VisibleRect.h"
#include "B2Sprite.h"
#include "Bullet.h"

using namespace std;
USING_NS_CC;

cocos2d::Scene* BattleScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BattleScene::create();
	scene->addChild(layer);
	return scene;
}

BattleScene::BattleScene()
	: m_world(nullptr)
	, m_player(nullptr)
	, m_enemy(nullptr)
	, m_bulletManager(nullptr)
	, m_debugDraw(nullptr)
	, PTM_RATIO(1)
{
	READ_CONFIG("global", "PTM_RATIO", PTM_RATIO);

	READ_CONFIG("global", "RISE_ACCELERATION", RISE_ACCELERATION);
	READ_CONFIG("global", "FALL_ACCELERATION", FALL_ACCELERATION);
	READ_CONFIG("global", "MAX_RISE_VELOCITY", MAX_RISE_VELOCITY);

}

BattleScene::~BattleScene()
{
	if (m_debugDraw)
	{
		delete m_debugDraw;
		m_debugDraw = nullptr;
	}
	if (m_world)
	{
		delete m_world;
		m_world = nullptr;
	}
}

bool BattleScene::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	this->initPhysics();


	m_player = Helicopter::createBody(m_world, Point(250, 200), PTM_RATIO);
	m_player->setGroup(kB2SpriteGroupPlayer);
	m_player->setVelocity(10.0f);
	this->addChild(m_player);

	m_enemy = Helicopter::createBody(m_world, Point(600, 200), PTM_RATIO);
	m_enemy->setGroup(kB2SpriteGroupEnemy);
	this->addChild(m_enemy);

	m_bulletManager = BulletManager::create("bullet.png");
	this->addChild(m_bulletManager);
	m_bulletManager->setWorld(m_world);
	m_bulletManager->setPTMRatio(PTM_RATIO);

	// touch event listener
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const vector<Touch *> &touches, Event *event)
	{
		auto p = touches[0]->getLocation();
		m_player->setTargetPoint(Point(m_player->getPositionX(), p.y));
		m_player->setFlying(true);
	};
	listener->onTouchesMoved = listener->onTouchesBegan;
	listener->onTouchesEnded = [=](const vector<Touch *> &touches, Event *event)
	{
		m_player->setFlying(false);
	};
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();

	return true;
}

void BattleScene::update( float dt )
{
	//It is recommended that a fixed time step is used with Box2D for stability
	//of the simulation, however, we are using a variable time step here.
	//You need to make an informed choice, the following URL is useful
	//http://gafferongames.com/game-physics/fix-your-timestep/

	int velocityIterations = 8;
	int positionIterations = 1;

	// Instruct the world to perform a single step of simulation. It is
	// generally best to keep the time step and iterations fixed.
	m_world->Step(dt, velocityIterations, positionIterations);

	// update player
	if (m_player->getFlying())
	{
		auto p = m_player->getTargetPoint();

		float dy = p.y - m_player->getPositionY();
		float abs_dy = abs(dy);

		float v = 0.0f;
		if (abs_dy < 0.001f) v = 0.0f;
		else if (abs_dy < m_player->getVelocity()) v = dy;
		else if (dy < 0) v = -m_player->getVelocity();
		else v = m_player->getVelocity();

		m_player->getB2Body()->SetLinearVelocity(b2Vec2(0.0f, v));
	}
	else
	{
		m_player->getB2Body()->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
	}
	/*
	auto body = m_player->getB2Body();
	if (m_player->getFlying())
	{
		const b2Vec2 &v = body->GetLinearVelocity();
		if (v.y < MAX_RISE_VELOCITY)
		{
			body->ApplyLinearImpulse(b2Vec2(0.0f, RISE_ACCELERATION), body->GetWorldCenter(), true);
		}
	}
	else
	{
		body->ApplyLinearImpulse(b2Vec2(0.0f, FALL_ACCELERATION), body->GetWorldCenter(), true);
	}
	*/

	// update bullet manager
	auto v = m_bulletManager->getChildren();
	for (vector<Node *>::iterator it=v.begin(); it!=v.end(); ++it)
	{
		Bullet *bullet = dynamic_cast<Bullet *>(*it);	
		if (bullet)
		{
			if (bullet->getPositionX() > VisibleRect::right().x)
			{
				m_bulletManager->destroyObject(bullet);
			}
		}
	}
	m_bulletManager->update(dt);

	static int frames = 0;
	if (frames % 3 == 0)
	{
		auto bullet = m_bulletManager->createObject(m_player->getPosition());
		bullet->setGroup(kB2SpriteGroupPlayer);
		bullet->setVelocity(Vect(20.0f, 0.0f));
		Vect v = bullet->getVelocity();
		bullet->getB2Body()->SetLinearVelocity(b2Vec2(v.x, v.y));
		frames = 0;
	}
	++frames;


}

void BattleScene::draw()
{
	Layer::draw();

	GL::enableVertexAttribs( cocos2d::GL::VERTEX_ATTRIB_FLAG_POSITION );

	kmGLPushMatrix();
	kmGLGetMatrix(KM_GL_MODELVIEW, &m_modelViewMV);

	m_customCommand.init(_globalZOrder);
	m_customCommand.func = [=]() 
	{
		kmMat4 oldMV;
		kmGLGetMatrix(KM_GL_MODELVIEW, &oldMV);
		kmGLLoadMatrix(&m_modelViewMV);
		m_world->DrawDebugData();
		kmGLLoadMatrix(&oldMV);
	};
	Director::getInstance()->getRenderer()->addCommand(&m_customCommand);

	kmGLPopMatrix();
}

void BattleScene::BeginContact( b2Contact *contact )
{
	if (!contact) return;
	
	auto body_a = contact->GetFixtureA()->GetBody();
	auto body_b = contact->GetFixtureB()->GetBody();
	auto sprite_a = (B2Sprite *)(body_a->GetUserData());
	auto sprite_b = (B2Sprite *)(body_b->GetUserData());
	
	if (!sprite_a || !sprite_b)
	{
		return;
	}

	if (sprite_a->getGroup() == kB2SpriteGroupNone || sprite_b->getGroup() == kB2SpriteGroupNone)
	{
		return;
	}

	if (sprite_a->getGroup() == sprite_b->getGroup())
	{
		return;
	}

	if (sprite_a->getType() == sprite_b->getType())
	{
		return;
	}

	if (sprite_a->getType() == kB2SpriteTypeBullet)
	{
		m_bulletManager->destroyObject(dynamic_cast<Bullet *>(sprite_a));
		auto p = ParticleExplosion::create();
		p->setLife(0.001f);
		p->setScale(0.1f);
		p->setPosition(sprite_a->getPosition());
		this->addChild(p);
	}
	if (sprite_b->getType() == kB2SpriteTypeBullet)
	{
		m_bulletManager->destroyObject(dynamic_cast<Bullet *>(sprite_b));
		auto p = ParticleExplosion::create();
		p->setLife(0.001f);
		p->setScale(0.1f);
		p->setPosition(sprite_b->getPosition());
		this->addChild(p);
	}
}

void BattleScene::EndContact( b2Contact *contact )
{

}

void BattleScene::PreSolve( b2Contact *contact, const b2Manifold *oldManifold )
{

}

void BattleScene::PostSolve( b2Contact *contact, const b2ContactImpulse *impulse )
{

}

void BattleScene::initPhysics()
{
	if (m_world)
	{
		return;
	}

	// a brave new world
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);

	// contact listener
	m_world->SetContactListener(this);

	// debug draw
	this->setPhysicsDebug(true);

	// ground body
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0, 0);
	auto groundBody = m_world->CreateBody(&groundBodyDef);

	b2EdgeShape groundBox;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();

	// bottom
	groundBox.Set(b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	// top
	groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	// left
	groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);

	// right
	groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
	groundBody->CreateFixture(&groundBox,0);
}

void BattleScene::setPhysicsDebug( bool bPhysicsDebug )
{
	if (!m_debugDraw)
	{
		m_debugDraw = new GLESDebugDraw(PTM_RATIO);
		m_world->SetDebugDraw(m_debugDraw);
	}

	if (bPhysicsDebug)
	{
		uint32 flags = 0;
		flags += b2Draw::e_shapeBit;
		//flags += b2Draw::e_jointBit;
		//flags += b2Draw::e_aabbBit;
		//flags += b2Draw::e_pairBit;
		//flags += b2Draw::e_centerOfMassBit;
		m_debugDraw->SetFlags(flags);
	}
	else
	{
		m_debugDraw->SetFlags(0);
	}
}

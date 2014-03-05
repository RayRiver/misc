#include "PhysicsTest.h"

#include <vector>

#include "Config.h"
#include "GLES-Render.h"
#include "VisibleRect.h"
#include "B2Sprite.h"
#include "GB2ShapeCache-x.h"

using namespace std;
USING_NS_CC;

cocos2d::Scene* PhysicsTest::createScene()
{
	auto scene = Scene::create();
	auto layer = PhysicsTest::create();
	scene->addChild(layer);
	return scene;
}

PhysicsTest::PhysicsTest()
	: m_world(nullptr)
	, m_debugDraw(nullptr)
	, PTM_RATIO(1)
{
	READ_CONFIG("global", "PTM_RATIO", PTM_RATIO);

	READ_CONFIG("global", "RISE_ACCELERATION", RISE_ACCELERATION);
	READ_CONFIG("global", "FALL_ACCELERATION", FALL_ACCELERATION);
	READ_CONFIG("global", "MAX_RISE_VELOCITY", MAX_RISE_VELOCITY);

}

PhysicsTest::~PhysicsTest()
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

bool PhysicsTest::init()
{
	if (!Layer::init())	
	{
		return false;
	}

	this->initPhysics();




	// touch event listener
	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	listener->onTouchesBegan = [=](const vector<Touch *> &touches, Event *event)
	{

	};
	listener->onTouchesMoved = listener->onTouchesBegan;
	listener->onTouchesEnded = [=](const vector<Touch *> &touches, Event *event)
	{
		Point p = touches[0]->getLocation();
		this->addPhysicsBody(p);
	};
	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);


	this->scheduleUpdate();

	return true;
}

void PhysicsTest::update( float dt )
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




}

void PhysicsTest::draw()
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

void PhysicsTest::BeginContact( b2Contact *contact )
{
	if (!contact) return;
	

}

void PhysicsTest::EndContact( b2Contact *contact )
{

}

void PhysicsTest::PreSolve( b2Contact *contact, const b2Manifold *oldManifold )
{

}

void PhysicsTest::PostSolve( b2Contact *contact, const b2ContactImpulse *impulse )
{

}

void PhysicsTest::initPhysics()
{
	if (m_world)
	{
		return;
	}

	// a brave new world
	b2Vec2 gravity;
	gravity.Set(0.0f, -9.8f);
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

void PhysicsTest::setPhysicsDebug( bool bPhysicsDebug )
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

string names[] = {
	"drink",
	"hamburger",
	"hotdog",
	"icecream",
	"icecream2",
	"icecream3",
	"orange"
};


void PhysicsTest::addPhysicsBody(const cocos2d::Point &point)
{
	float fPTMRatio = PTM_RATIO;
	b2World *world = m_world;

	string name = names[rand() % 7];

	GB2ShapeCache::sharedGB2ShapeCache()->addShapesWithFile("shapes.plist");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(point.x / fPTMRatio, point.y / fPTMRatio);
	b2Body *body = world->CreateBody(&bodyDef);

	auto sprite = B2Sprite::create((name + ".png").c_str());

//	sprite->setContentSize(size);
	sprite->setB2Body(body);
	sprite->setPTMRatio(fPTMRatio);
	sprite->setPosition(point);
	this->addChild(sprite);

	GB2ShapeCache *sc = GB2ShapeCache::sharedGB2ShapeCache();
	sc->addFixturesToBody(body, name.c_str());
	sprite->setAnchorPoint(sc->anchorPointForShape(name.c_str()));


}

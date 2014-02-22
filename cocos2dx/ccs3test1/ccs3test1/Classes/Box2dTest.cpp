#include "Box2dTest.h"

#include <vector>
#include <algorithm>
#include "cocos-ext.h"
#include "GLES-Render.h"
#include "VisibleRect.h"
#include "B2Sprite.h"

#include "Helicopter.h"
#include "Barrier.h"

#include "json/reader.h"

using namespace std;
using namespace cocos2d::gui;
USING_NS_CC_EXT;
USING_NS_CC;

#define PTM_RATIO 32

const float GRAVITY = -35.0f;
const float CLIMB_FORCE = 90.0f;

enum tags
{
	kTagScrollingLayer = 8888,
};

class b2Sprite : public Sprite
{
public:
	CC_SYNTHESIZE(b2Body *, m_body, Body);
	CC_SYNTHESIZE(b2World *, m_world, World);
	CC_SYNTHESIZE(int, m_type, Type);

	static b2Sprite* create(b2World *world);
	virtual bool init(b2World *world);
	virtual void update(float dt);
	virtual void setPosition(const Point &pos);
};

b2Sprite *b2Sprite::create(b2World *world)
{
	b2Sprite *sprite = new b2Sprite();
	if (sprite && sprite->init(world))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool b2Sprite::init(b2World *world)
{
	if (!Sprite::init())
	{
		return false;
	}

	m_world = world;
	CCASSERT(m_world, "b2Sprite init: world == nullptr");
	this->initWithFile("CloseSelected.png");

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	m_body = m_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 20.0f;

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &circle;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.4f;

	m_body->CreateFixture(&fixtureDef);

	return true;
}

void b2Sprite::update(float dt)
{
	if (m_body && isVisible())
	{
		const b2Vec2 &pos = m_body->GetPosition();
		setPosition(CCPoint(pos.x, pos.y));
	}
}

void b2Sprite::setPosition(const Point &pos)
{
	Sprite::setPosition(pos);

	if (m_body)
	{
		m_body->SetTransform(b2Vec2(pos.x, pos.y), m_body->GetAngle());
	}
}

Scene* Box2dTest::createScene()
{
    auto scene = Scene::create();
    auto layer = Box2dTest::create();
    scene->addChild(layer);
    return scene;
}

Box2dTest::Box2dTest()
	: m_world(nullptr)
	, m_debugDraw(nullptr)
{

}

Box2dTest::~Box2dTest()
{
	if (m_debugDraw) 
	{
		delete m_debugDraw;
		m_debugDraw = nullptr;
	}

	for_each(m_barriers.begin(), m_barriers.end(), [](Barrier *barrier) {
	});
	m_barriers.clear();

	if (m_world) 
	{
	//	delete m_world;
	//	m_world = nullptr;
	}
}

bool Box2dTest::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// add test ui
	auto uilayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui_test.json");
	this->addChild(uilayer);
	auto button = (uilayer->getChildByName("Button_22"));
	button->addTouchEventListener(this, toucheventselector(Box2dTest::debugButton));

	// Box2D
	this->initPhysics();

	for (size_t i = 0; i < 20; ++i)
	{
		m_future_barriers.push_back(Point((i+1)*visibleSize.width, 400));
	}

	auto scrolling_layer = Layer::create();
	this->addChild(scrolling_layer, 0, kTagScrollingLayer);


	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	//listener->setSwallowTouches(true);

	auto heli = Helicopter::createBody(m_world, Point(300, 200), PTM_RATIO);
	this->addChild(heli, 0, 99999);

	listener->onTouchesBegan = [=](const vector<Touch *> &touches, Event *event)
	{
		heli->setFlying(true);
		return;
		auto body = heli->getB2Body();
		body->ApplyForce(b2Vec2(0, 200.0f), body->GetWorldCenter(), true);
	};

	listener->onTouchesEnded = [=](const vector<Touch *> &touches, Event *event)
	{
		heli->setFlying(false);
		return;
		auto body = heli->getB2Body();
		body->ApplyForce(b2Vec2_zero, body->GetWorldCenter(), true);
		return;

		log("onTouchesEnded %d", event->getCurrentTarget()->getTag());	
		for (auto touch : touches)
		{
			auto p = touch->getLocation();
			this->addPhysicsSprite(p);
		}
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	


	this->scheduleUpdate();

    return true;
}

void Box2dTest::update( float dt )
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

	/*
	auto v = this->getChildren();
	for (ssize_t i=0; i<v.size(); ++i)
	{
		auto node = v.at(i);
		node->update(dt);
	}
	*/

	auto heli = dynamic_cast<Helicopter *>(this->getChildByTag(99999));
	if (heli->getFlying())
	{
		auto body = heli->getB2Body();
//		body->ApplyForce(b2Vec2(0.0f, -GRAVITY), body->GetWorldCenter(), true);
//		body->SetLinearVelocity(b2Vec2(0.0f, 0.0f));
		const b2Vec2 &v = body->GetLinearVelocity();
		if (v.y < 12.0f)
		{
			body->ApplyLinearImpulse(b2Vec2(0.0f, 1.1f), body->GetWorldCenter(), true);
		}
	}
	else
	{
		auto body = heli->getB2Body();
		body->ApplyForce(b2Vec2(0.0f, GRAVITY), body->GetWorldCenter(), true);
	}

	m_distance += m_speed;


	auto scrolling_layer = dynamic_cast<Layer *>(this->getChildByTag(kTagScrollingLayer));
	scrolling_layer->setPositionX(scrolling_layer->getPositionX() - m_speed);
	auto pos = heli->getPosition();
	auto gas = Sprite::create("CloseSelected.png");
	gas->setPosition(Point(pos.x+m_distance, pos.y));
	gas->setOpacity(123);
	scrolling_layer->addChild(gas);



	Size visibleSize = Director::getInstance()->getVisibleSize();
	Point origin = Director::getInstance()->getVisibleOrigin();
	size_t count = 0;
	for (list<Point>::iterator it = m_future_barriers.begin(); it != m_future_barriers.end(); ++it)
	{
		auto p = *it;
		if (p.x - m_distance < origin.x + visibleSize.width)
		{
			++count;
		}
		else
		{
			break;
		}
	}


	for (size_t i = 0; i < count; ++i)
	{
		auto p = m_future_barriers.front();
		m_future_barriers.pop_front();
		auto barrier = Barrier::createBody(m_world, Point(p.x-m_distance, p.y), PTM_RATIO);
		barrier->setMapPosition(p);
		this->addChild(barrier);
		m_barriers.push_back(barrier);
	}



	for (list<Barrier *>::iterator it = m_barriers.begin(); it != m_barriers.end(); ++it)
	{
		auto barrier = *it;
		if (barrier->getPositionX() < origin.x)
		{
			this->removeChild(barrier);
			m_barriers.remove(barrier);
			break;
		}

		Point p = Point(barrier->getMapPosition().x - m_distance, barrier->getMapPosition().y);
		barrier->setPosition(p);
	}
}

void Box2dTest::draw()
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

void Box2dTest::BeginContact( b2Contact *contact )
{
	//b2ContactListener::BeginContact(contact);
	log("BeginContact");
	if (contact)
	{
	}
}

void Box2dTest::EndContact( b2Contact *contact )
{
	//b2ContactListener::EndContact(contact);
	log("EndContact");
}

void Box2dTest::PreSolve( b2Contact *contact, const b2Manifold *oldManifold )
{
	log("PreSolve");
	//b2ContactListener::PreSolve(contact, oldManifold);
}

void Box2dTest::PostSolve( b2Contact *contact, const b2ContactImpulse *impulse )
{
	log("PostSolve");
	//b2ContactListener::PostSolve(contact, impulse);
}



void Box2dTest::debugButton( cocos2d::Object *obj, cocos2d::gui::TouchEventType eventType )
{
	auto button = dynamic_cast<Button *>(obj);

	switch(eventType)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		this->setPhysicsDebug(!this->isPhysicsDebug());
		break;
	default:
		break;
	}


}

bool Box2dTest::isPhysicsDebug()
{
	if (m_debugDraw && m_debugDraw->GetFlags() != 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Box2dTest::setPhysicsDebug( bool bPhysicsDebug )
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

void Box2dTest::initPhysics()
{
	// box2d world
	b2Vec2 gravity;
	gravity.Set(0.0f, 0.0f);
	m_world = new b2World(gravity);
	m_world->SetAllowSleeping(true);
	m_world->SetContinuousPhysics(true);

	// contact listener
	//auto m_contactListener = new b2ContactListener();
	//m_world->SetContactListener(m_contactListener);
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
	//groundBox.Set(b2Vec2(VisibleRect::leftTop().x/PTM_RATIO,VisibleRect::leftTop().y/PTM_RATIO), b2Vec2(VisibleRect::leftBottom().x/PTM_RATIO,VisibleRect::leftBottom().y/PTM_RATIO));
	//groundBody->CreateFixture(&groundBox,0);

	// right
	//groundBox.Set(b2Vec2(VisibleRect::rightBottom().x/PTM_RATIO,VisibleRect::rightBottom().y/PTM_RATIO), b2Vec2(VisibleRect::rightTop().x/PTM_RATIO,VisibleRect::rightTop().y/PTM_RATIO));
	//groundBody->CreateFixture(&groundBox,0);
}


#define DICT cocostudio::DictionaryHelper::getInstance()
b2Vec2 *getPolygonVertexes(const char *jsonFile, int &num)
{
	std::string jsonpath;
	jsonpath = CCFileUtils::getInstance()->fullPathForFilename(jsonFile);
	size_t pos = jsonpath.find_last_of('/');
	std::string jsonData = FileUtils::getInstance()->getStringFromFile(jsonpath);

	rapidjson::Document doc;
	doc.Parse<0>(jsonData.c_str());
	if (doc.HasParseError())
	{
		CCASSERT(false, "");
		log("GetParseError %s\n", doc.GetParseError());
	}

	num = DICT->getIntValue_json(doc, "num");
	auto verts = new b2Vec2[num];

	int count = DICT->getArrayCount_json(doc, "vertexes");
	for (int i=0; i<count; ++i)
	{
		const rapidjson::Value &dict = DICT->getSubDictionary_json(doc, "vertexes", i);
		float x = DICT->getFloatValue_json(dict, "x");
		float y = DICT->getFloatValue_json(dict, "y");
		verts[i] = b2Vec2(x/PTM_RATIO, y/PTM_RATIO);
	}

	return verts;
}

void Box2dTest::addPhysicsSprite( const Point &p )
{
	auto s = Helicopter::createBody(m_world, p, PTM_RATIO);
	this->addChild(s);
	return;

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(p.x/PTM_RATIO, p.y/PTM_RATIO);

	auto body = m_world->CreateBody(&bodyDef);

	b2CircleShape circle;
	circle.m_radius = 20.0f/PTM_RATIO;



	int num = 0;
	auto verts = getPolygonVertexes("CloseNormal.shape.json", num);



	/*
	int num = 4;  
	b2Vec2 verts[] = 
	{  
		b2Vec2(-1.1883241653442382f / PTM_RATIO, 17.766151428222656f / PTM_RATIO),  
		b2Vec2(-17.46222381591797f / PTM_RATIO, -0.5210148334503174f / PTM_RATIO),  
		b2Vec2(1.4960304260253907f / PTM_RATIO, -17.969319152832032f / PTM_RATIO),  
		b2Vec2(18.608790588378906f / PTM_RATIO, 0.1500738263130188f / PTM_RATIO),  
	};  
	*/

	b2PolygonShape shape;
	shape.Set(verts, num);
	delete[] verts;

	b2FixtureDef fixtureDef;
	fixtureDef.isSensor = false;	// important
	fixtureDef.shape = &shape;
	fixtureDef.density = 1.0f;
	fixtureDef.restitution = 0.7f;
	fixtureDef.friction = 0.4f;

	body->CreateFixture(&fixtureDef);


	auto sprite = B2Sprite::create("CloseSelected.png");
	this->addChild(sprite);
	sprite->setB2Body(body);
	sprite->setPTMRatio(PTM_RATIO);
	sprite->setPosition(p);


}










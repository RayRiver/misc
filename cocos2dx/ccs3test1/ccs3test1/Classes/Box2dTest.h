#ifndef __BOX2DTEST_SCENE_H__
#define __BOX2DTEST_SCENE_H__

#include "cocos2d.h"
#include "gui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"
#include "box2d/Box2D.h"

#include "renderer/CCRenderer.h"
#include "renderer/CCCustomCommand.h"

class Box2dTest : public cocos2d::Layer, public b2ContactListener
{
public:
	Box2dTest();
	virtual ~Box2dTest();

    static cocos2d::Scene* createScene();
    virtual bool init();  
    CREATE_FUNC(Box2dTest);
	void debugButton(cocos2d::Object *obj, cocos2d::gui::TouchEventType eventType);

	virtual void update(float dt);
	virtual void draw();

	virtual void BeginContact(b2Contact *contact);
	virtual void EndContact(b2Contact *contact);
	virtual void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	virtual void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);

	bool isPhysicsDebug();	
	void setPhysicsDebug(bool bPhysicsDebug);
	void initPhysics();
	void addPhysicsSprite(const cocos2d::Point &pos);

	CC_SYNTHESIZE(b2World *, m_world, World);
	CC_SYNTHESIZE(b2Draw *, m_debugDraw, DebugDraw);

protected:
	kmMat4 m_modelViewMV;
	cocos2d::CustomCommand m_customCommand;
};

#endif // __BOX2DTEST_SCENE_H__

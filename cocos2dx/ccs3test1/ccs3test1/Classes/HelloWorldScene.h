#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "gui/CocosGUI.h"
#include "cocostudio/CocoStudio.h"

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(Object* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	void onEnter();

	void debugButton(cocos2d::Object *obj, cocos2d::gui::TouchEventType eventType);

	void setPhyWorld(cocos2d::PhysicsWorld *world) {m_world = world;}
private:
	cocos2d::PhysicsWorld *m_world;
};

#endif // __HELLOWORLD_SCENE_H__

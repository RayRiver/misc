#include "HelloWorldScene.h"

#include <algorithm>

#include "Box2dTest.h"
#include "BattleScene.h"

using namespace std;
using namespace cocos2d::gui;
USING_NS_CC;

bool g_bAutoPlay = false;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    //auto scene = Scene::create();
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);

    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	layer->setPhyWorld(scene->getPhysicsWorld());

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	{
		auto item1 = MenuItemFont::create("Play", [](Object *obj) {
			g_bAutoPlay = false;
			Director::getInstance()->replaceScene(Box2dTest::createScene());
		});
		item1->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 3/4));

		auto item2 = MenuItemFont::create("Battle", [](Object *obj) {
			//g_bAutoPlay = true;
			//Director::getInstance()->replaceScene(Box2dTest::createScene());
			Director::getInstance()->replaceScene(BattleScene::createScene());
		});
		item2->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 1/2));

		auto item3 = MenuItemFont::create("Exit", [](Object *obj) {
			Director::getInstance()->end();
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		});
		item3->setPosition(Point(origin.x + visibleSize.width/2, origin.y + visibleSize.height * 1/4));




		// create menu, it's an autorelease object
		auto menu = Menu::create(item1, item2, item3, NULL);
		menu->setPosition(Point::ZERO);
		this->addChild(menu);
	}

	return true;

	// add physics border
	auto edgeSp = Sprite::create();
	auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 5);
	edgeSp->setPosition(visibleSize.width/2, visibleSize.height/2);
	edgeSp->setPhysicsBody(body);
	edgeSp->setTag(0);	
	this->addChild(edgeSp);

	// add test ui
	auto uilayer = cocostudio::GUIReader::getInstance()->widgetFromJsonFile("ui_test.json");
	this->addChild(uilayer);
	auto button = (uilayer->getChildByName("Button_22"));
	button->addTouchEventListener(this, toucheventselector(HelloWorld::debugButton));


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("Hello World", "Arial", 44);
    
    // position the label on the center of the screen
    label->setPosition(Point(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1, 88888);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("HelloWorld.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0, 99999);


	auto dispatcher = Director::getInstance()->getEventDispatcher();
	auto listener = EventListenerTouchAllAtOnce::create();
	//listener->setSwallowTouches(true);

	listener->onTouchesEnded = [=](const vector<Touch *> &touches, Event *event)
	{
		log("onTouchesEnded %d", event->getCurrentTarget()->getTag());	
		for (auto touch : touches)
		{
			auto p = touch->getLocation();
			auto sprite = Sprite::create("CloseSelected.png");
			sprite->setTag(1);
			auto body = PhysicsBody::createCircle(20.0f);
			sprite->setPhysicsBody(body);
			sprite->setPosition(p);
			this->addChild(sprite);
		}
	};

	dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}


void HelloWorld::menuCloseCallback(Object* pSender)
{
    //Director::getInstance()->end();
	if (m_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)
	{
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
	}
	else
	{
		m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
	}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::onEnter()
{
	Layer::onEnter();
	
	auto listener = EventListenerPhysicsContact::create();
	listener->onContactBegin = [=](EventCustom *event, const PhysicsContact &contact)
	{
		log("onContactBegin");
		return true;
	};
	Director::getInstance()->getEventDispatcher()->addEventListenerWithFixedPriority(listener, 10);
}

void HelloWorld::debugButton( cocos2d::Object *obj, cocos2d::gui::TouchEventType eventType )
{
	auto button = dynamic_cast<Button *>(obj);

	switch(eventType)
	{
	case TouchEventType::TOUCH_EVENT_ENDED:
		//Director::getInstance()->end();
		if (m_world->getDebugDrawMask() != PhysicsWorld::DEBUGDRAW_NONE)
		{
			m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
		}
		else
		{
			m_world->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
		}
		break;
	default:
		break;
	}


}

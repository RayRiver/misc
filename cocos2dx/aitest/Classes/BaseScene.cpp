#include "BaseScene.h"

#include "ListScene.h"
#include "utils/helper.h"
#include "PathFinder/MapManager.h"
#include "TSP/TSPMap.h"

USING_NS_CC;

bool BaseScene::init()
{
    if ( !Scene::init() )
    {
        return false;
    }

	auto lbl = Label::createWithSystemFont("Back", "Arial", 32);
	auto item = MenuItemLabel::create(lbl, [=](Ref *sender) {
		auto tsp = ListScene::createScene();
		Director::getInstance()->replaceScene(tsp);
	});

	auto menu = Menu::create(item, nullptr);
	menu->setPosition(Director::getInstance()->getVisibleSize().width-50, 30);
	this->addChild(menu, 10000);

    return true;
}

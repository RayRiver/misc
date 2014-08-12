#include "ListScene.h"

#include "utils/helper.h"
#include "PathFinder/MapManager.h"
#include "TSP/TSPMap.h"
#include "Sweeper/SweeperEntryScene.h"

USING_NS_CC;

Scene* ListScene::createScene()
{
    auto scene = Scene::create();
    auto layer = ListScene::create();
    scene->addChild(layer);
    return scene;
}

bool ListScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }

	helper::init();


	auto lbl_pathfinder = Label::createWithSystemFont("Path Finder", "Arial", 32);
	auto menuitem_pathfinder = MenuItemLabel::create(lbl_pathfinder, [=](Ref *sender) {
		auto mapManager = MapManager::instance();
		Director::getInstance()->replaceScene(mapManager);
	});

	auto lbl_tsp = Label::createWithSystemFont("TSP", "Arial", 32);
	auto menuitem_tsp = MenuItemLabel::create(lbl_tsp, [=](Ref *sender) {
		auto tsp = TSPMap::instance();
		Director::getInstance()->replaceScene(tsp);
	});
	auto lbl_sweeper = Label::createWithSystemFont("Sweeper", "Arial", 32);
	auto menuitem_sweeper = MenuItemLabel::create(lbl_sweeper, [=](Ref *sender) {
		auto scene = SweeperEntryScene::create();
		Director::getInstance()->replaceScene(scene);
	});

	auto menu = Menu::create(menuitem_pathfinder, menuitem_tsp, menuitem_sweeper, nullptr);
	menu->alignItemsVerticallyWithPadding(5.0f);
	this->addChild(menu);

	return true;
}

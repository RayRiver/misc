#include "SweeperStatisticsScene.h"

#include "utils/Display.h"

#include "SweeperLiveScene.h"

USING_NS_CC;

SweeperStatisticsScene::SweeperStatisticsScene()
{

}

SweeperStatisticsScene::~SweeperStatisticsScene()
{

}

bool SweeperStatisticsScene::init()
{
	if (!BaseScene::init())
	{
		return false;
	}

	// ´´½¨ÇÐ»»°´Å¥;
	auto label = Label::createWithSystemFont("Switch Live", "Arial", 20);
	auto item = MenuItemLabel::create(label, [=](Ref *) {
		auto scene = SweeperLiveScene::create();
		Director::getInstance()->replaceScene(scene);
	});
	auto menu = Menu::create(item, nullptr);
	menu->setPosition(DISPLAY->right()-100, DISPLAY->top()-20);
	this->addChild(menu);

	return true;
}

void SweeperStatisticsScene::startGeneration()
{

}


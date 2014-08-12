#include "SweeperEntryScene.h"

#include "SweeperConstants.h"
#include "GeneticAlgorithm.h"
#include "SweeperLiveScene.h"

USING_NS_CC;

bool SweeperEntryScene::init()
{
	if (!Scene::init())
	{
		return false;
	}

	// ��ʼ���Ŵ��㷨;
	GeneticAlgorithm::instance()->init(CONSTANTS.CrossoverRate, CONSTANTS.MutateRate, CONSTANTS.SweeperNumber, CONSTANTS.InputNumber);

	return true;
}

void SweeperEntryScene::onEnter()
{
	Scene::onEnter();

	// ����live����;
	auto scene = SweeperLiveScene::create();
	Director::getInstance()->replaceScene(scene);

}


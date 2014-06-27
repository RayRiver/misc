#include "GameScene.h"

#include "VisibleRect.h"
#include "GameCharacter.h"
#include "InputController.h"
#include "InputManager.h"
#include "KeyboardLayer.h"

USING_NS_CC;
using namespace cocostudio;

#define BUTTON_1 1
#define BUTTON_2 2

Scene* GameScene::createScene()
{
    auto scene = Scene::create();
    auto layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }


	//ArmatureDataManager::getInstance()->addArmatureFileInfo("animation/Cowboy.ExportJson");
	//animationController->load("Cowboy");
	ArmatureDataManager::getInstance()->addArmatureFileInfo("animation/animation.ExportJson");
	auto player = GameCharacter::create("animation");
	player->setPosition(VisibleRect::center());
	//player->setScale(0.1f);
	this->addChild(player);
	m_player = player;
    

	m_inputManager = InputManager::create();
	this->addChild(m_inputManager, 10000);

	auto rect = VisibleRect::getVisibleRect();
	m_inputManager->addButton(InputManager::Action::Action1, Point(rect.origin.x + rect.size.width * 6/8, rect.origin.y + rect.size.height * 1/8));
	m_inputManager->addButton(InputManager::Action::Action2, Point(rect.origin.x + rect.size.width * 7/8, rect.origin.y + rect.size.height * 2/8));

	auto inputController = InputController::create();
	m_player->addComponent(inputController);
	inputController->setInputManager(m_inputManager);

	// keyboard simulate control
	m_keyboardLayer = KeyboardLayer::create(m_inputManager);
	this->addChild(m_keyboardLayer);




	this->scheduleUpdate();

    return true;
}

void GameScene::onEnter()
{
	Layer::onEnter();

	m_player->getStateMachine()->doEvent("doStartup");
}

void GameScene::update(float dt)
{

}

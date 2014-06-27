#include "GamePlayer.h"

#include "InputManager.h"

USING_NS_CC;

GamePlayer * GamePlayer::create( InputManager *inputManager )
{
	auto pRet = new GamePlayer();
	if (pRet && pRet->init(inputManager)) 
	{ 
		pRet->autorelease(); 
		return pRet; 
	} 
	else 
	{ 
		delete pRet; 
		pRet = NULL; 
		return NULL;
	} 
}

GamePlayer::GamePlayer()
	: m_inputManager(nullptr)
{

}

GamePlayer::~GamePlayer()
{

}

bool GamePlayer::init( InputManager *inputManager )
{
	if (!GameCharacter::init())
	{
		return false;
	}

	return true;
}

void GamePlayer::update(float dt)
{
	auto direction = m_inputManager->getJoystickDirection();
	auto prevState = m_inputManager->getJoystickPrevState();
	auto state = m_inputManager->getJoystickState();

	auto character_direction = GameCharacter::Direction::Right; 
	if (direction.x < 0)
	{
		character_direction = GameCharacter::Direction::Left;
	}

	if (prevState != state)
	{
		if (state == InputManager::JoystickState::None)
		{
			this->doIdle();
		}
		else if (state == InputManager::JoystickState::Light)
		{
			this->doWalk(character_direction);
		}
		else if (state == InputManager::JoystickState::Heavy)
		{
			this->doRun(character_direction);
		}
	}


	if (m_inputManager->buttonPressedTrigger(InputManager::Action::Action1))
	{
		this->doAttack();
	}
	if (m_inputManager->buttonPressedTrigger(InputManager::Action::Action2))
	{

	}
}

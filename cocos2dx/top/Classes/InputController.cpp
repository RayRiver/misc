#include "InputController.h"

#include "GameCharacter.h"

USING_NS_CC;

const char *InputController::NAME = "InputController";

InputController::InputController()
	: m_inputManager(nullptr)
{
	this->setName(InputController::NAME);	
}

InputController::~InputController()
{

}

void InputController::update( float dt )
{
	if (!m_inputManager) return;

	auto owner = dynamic_cast<GameCharacter *>(this->getOwner());
	if (!owner) return;

	// parse input
	auto direction = m_inputManager->getJoystickDirection();
	auto prevState = m_inputManager->getJoystickPrevState();
	auto currState = m_inputManager->getJoystickState();

	auto character_direction = GameCharacter::Direction::Right; 
	if (direction.x < 0)
	{
		character_direction = GameCharacter::Direction::Left;
	}
	if (owner->getDirection() != character_direction)
	{
		owner->changeDirection(character_direction);
	}


	if (prevState != currState)
	{
		if (currState == InputManager::JoystickState::None)
		{
			owner->doIdle();
		}
		else if (currState == InputManager::JoystickState::Light)
		{
			owner->doWalk();
		}
		else if (currState == InputManager::JoystickState::Heavy)
		{
			owner->doRun();
		}
	}
	/*
	else
	{
		auto state = owner->getStateMachine()->getState();
		if (state == GameCharacter::State::Idle)
		{
			if (currState == InputManager::JoystickState::Light)
			{
				owner->doWalk(character_direction);
			}
			else if (currState == InputManager::JoystickState::Heavy)
			{
				owner->doRun(character_direction);
			}
		}
	}
	*/

	if (m_inputManager->buttonPressedTrigger(InputManager::Action::Action1))
	{
		owner->doAttack();
	}
	if (m_inputManager->buttonPressedTrigger(InputManager::Action::Action2))
	{

	}


}


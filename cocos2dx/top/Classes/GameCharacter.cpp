#include "GameCharacter.h"

#include "AnimationController.h"

USING_NS_CC;

GameCharacter * GameCharacter::create( const char *animationName )
{
	auto pRet = new GameCharacter();
	if (pRet && pRet->init(animationName)) 
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

GameCharacter::GameCharacter()
	: m_direction(Direction::Right)
{

}

GameCharacter::~GameCharacter()
{

}

bool GameCharacter::init( const char *animationName )
{
	if (!Node::init())
	{
		return false;
	}

	auto animationController = AnimationController::create();
	this->addComponent(animationController);

	animationController->load(animationName);
	animationController->setMovementCallback([=](cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID) {
		if (movementID.compare("attack_down") == 0)
		{
			if (movementType == cocostudio::MovementEventType::LOOP_COMPLETE || movementType == cocostudio::MovementEventType::COMPLETE)
			{
				this->doIdle();
			}
		}
	});

	auto fsm = StateMachine::create();
	this->addComponent(fsm);

	// init finite state machine
	fsm->setupState("doStartup", StateMachine::STATE_NONE, State::Idle);	
	fsm->setupState("doIdle", State::Walk, State::Idle);
	fsm->setupState("doIdle", State::Run, State::Idle);
	fsm->setupState("doWalk", State::Idle, State::Walk);
	fsm->setupState("doWalk", State::Run, State::Walk);
	fsm->setupState("doRun", State::Idle, State::Run);
	fsm->setupState("doRun", State::Walk, State::Run);
	fsm->setupState("doAttack", StateMachine::STATE_ALL, State::Attack);

	fsm->registerEnterStateCallback(State::Idle, [this](const char *eventName, int fromState, int toState) {
		this->onIdle();
		return true;
	});
	fsm->registerEnterStateCallback(State::Walk, [this](const char *eventName, int fromState, int toState) {
		this->onWalk();
		return true;
	});
	fsm->registerEnterStateCallback(State::Run, [this](const char *eventName, int fromState, int toState) {
		this->onRun();
		return true;
	});
	fsm->registerEnterStateCallback(State::Attack, [this](const char *eventName, int fromState, int toState) {
		this->onAttack();
		return true;
	});

	this->scheduleUpdate();

	return true;
}

void GameCharacter::update( float dt )
{
	Node::update(dt);
}

AnimationController * GameCharacter::getAnimationController()
{
	return dynamic_cast<AnimationController *>(this->getComponent(AnimationController::NAME));
}

StateMachine * GameCharacter::getStateMachine()
{
	return dynamic_cast<StateMachine *>(this->getComponent(StateMachine::NAME));
}


GameCharacter::Direction GameCharacter::getDirection()
{
	return m_direction;	
}

void GameCharacter::changeDirection( Direction direction )
{
	if (m_direction != direction)
	{
		this->setScaleX(this->getScaleX() * (-1));
		m_direction = direction;
	}
}

void GameCharacter::doIdle()
{
	if (this->getStateMachine()->getState() != State::Idle)
	{
		this->getStateMachine()->doEvent("doIdle");
	}
}

void GameCharacter::doWalk()
{
	if (this->getStateMachine()->getState() != State::Walk)
	{
		this->getStateMachine()->doEvent("doWalk");
	}
}

void GameCharacter::doRun()
{
	if (this->getStateMachine()->getState() != State::Run)
	{
		this->getStateMachine()->doEvent("doRun");
	}
}

void GameCharacter::doAttack()
{
	if (this->getStateMachine()->getState() != State::Attack)
	{
		this->getStateMachine()->doEvent("doAttack");
	}
}

void GameCharacter::onIdle()
{
	log("on idle");
	this->getAnimationController()->play("idle");
}

void GameCharacter::onWalk()
{
	log("on walk");
	this->getAnimationController()->play("walk");
}

void GameCharacter::onRun()
{
	log("on run");
	this->getAnimationController()->play("run");
}

void GameCharacter::onAttack()
{
	log("on attack");
	this->getAnimationController()->play("attack_down");
}


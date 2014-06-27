#ifndef GameCharacter_h__
#define GameCharacter_h__

#include "cocos2d.h"
#include "AnimationController.h"
#include "StateMachine.h"

class GameCharacter : public cocos2d::Node 
{
public:
	enum class Direction
	{
		Right = 1,
		Left = -1,
	};

	enum State
	{
		Idle = 1,
		Walk,
		Run,
		Attack,
	};

public:
	GameCharacter();
	virtual ~GameCharacter();

	static GameCharacter *create(const char *animationName);

	virtual bool init(const char *animationName);
	virtual void update(float dt);

	AnimationController *getAnimationController();
	StateMachine *getStateMachine();

	GameCharacter::Direction getDirection();
	void changeDirection(GameCharacter::Direction direction);

	void doIdle();
	void doWalk();
	void doRun();
	void doAttack();

	void onIdle();
	void onWalk();
	void onRun();
	void onAttack();

protected:
	GameCharacter::Direction m_direction;

};

#endif // GameCharacter_h__

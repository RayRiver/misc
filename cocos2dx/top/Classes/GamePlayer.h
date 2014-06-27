#ifndef GamePlayer_h__
#define GamePlayer_h__

#include "cocos2d.h"

#include "GameCharacter.h"

class InputManager;
class GamePlayer : public GameCharacter
{
public:
	GamePlayer();
	virtual ~GamePlayer();

	static GamePlayer *create(InputManager *inputManager);
	bool init(InputManager *inputManager);

	virtual void update(float dt);

private:
	InputManager *m_inputManager;
};

#endif // GamePlayer_h__

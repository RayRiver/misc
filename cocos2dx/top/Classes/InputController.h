#ifndef InputController_h__
#define InputController_h__

#include "cocos2d.h"

#include "InputManager.h"
#include "EntityComponent.h"

class InputController : public EntityComponent 
{
public:
	static const char *NAME;

public:
	InputController();
	virtual ~InputController();

	CREATE_FUNC(InputController);

	void setInputManager(InputManager *inputManager) { m_inputManager = inputManager; }

	virtual void update(float dt);

protected:
	InputManager *m_inputManager;
};

#endif // InputController_h__

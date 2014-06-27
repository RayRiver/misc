#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class GameCharacter;
class InputManager;
class KeyboardLayer;
class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(GameScene);

	virtual void onEnter();
	virtual void update(float dt);

private:
	GameCharacter *m_player;
	InputManager *m_inputManager;
	KeyboardLayer *m_keyboardLayer;
};

#endif // __GAME_SCENE_H__

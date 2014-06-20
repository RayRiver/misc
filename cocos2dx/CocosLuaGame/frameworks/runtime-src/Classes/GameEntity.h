#ifndef GameEntity_h__
#define GameEntity_h__

#include "cocos2d.h"

class GameEntity : public cocos2d::Sprite
{
public:
	GameEntity();
	virtual ~GameEntity();

	static GameEntity* create();

	

};

#endif // GameEntity_h__

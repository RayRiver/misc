#ifndef EntityComponent_h__
#define EntityComponent_h__

#include "cocos2d.h"
#include "CCLuaValue.h"

class EntityComponent : public cocos2d::Component
{
public:
	EntityComponent();
	virtual ~EntityComponent();

	static EntityComponent* create(void);

	virtual void onEnter();
	virtual void onExit();
	virtual void update(float dt);

	void registerHandler(const char *event_name, cocos2d::LUA_FUNCTION handler);
	void unregisterHandler(const char *event_name);
	void unregisterAllHandlers();

};

#endif // EntityComponent_h__

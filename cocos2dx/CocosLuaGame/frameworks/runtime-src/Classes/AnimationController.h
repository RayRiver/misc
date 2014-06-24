#ifndef AnimationController_h__
#define AnimationController_h__

#include <string>
#include <map>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

#include "EntityComponent.h"

class AnimationController : public EntityComponent 
{
public:
	typedef enum PlayMode
	{
		// loop < 0 : use the value from CCMovementData get from flash design panel
		// loop = 0 : this animation is not loop
		// loop > 0 : this animation is loop
		Default = -1,
		Once = 0,
		Loop = 1,
	};
	//typedef std::map<std::string, std::string> ArmatureMap;

public:
	AnimationController();
	virtual ~AnimationController();

	static AnimationController *create();

	void load(const char *armatureName);
	void play(const char *movementName, int playMode = Default);

	void pause();
	void resume();
	void stop();

	inline cocostudio::Armature *getArmature() { return m_pArmature; }
	bool checkCollider(cocos2d::Rect rect);
	void setMovementEventCallFunc(cocos2d::LUA_FUNCTION handler);	

protected:
	std::string m_animationName;
	cocostudio::Armature *m_pArmature;	
	float m_animationSpeedScale;

};

#endif // AnimationController_h__

#ifndef AnimationController_h__
#define AnimationController_h__

#include <string>
#include <map>

#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"

class AnimationController : public cocos2d::Component 
{
public:
	static const char *NAME;

	typedef enum PlayMode
	{
		// loop < 0 : use the value from CCMovementData get from flash design panel
		// loop = 0 : this animation is not loop
		// loop > 0 : this animation is loop
		Default = -1,
		Once = 0,
		Loop = 1,
	};

public:
	AnimationController();
	virtual ~AnimationController();

	CREATE_FUNC(AnimationController);

	void load(const char *armatureName);
	void play(const char *movementName, int playMode = Default);
	void setMovementCallback(const std::function<void(cocostudio::Armature *armature, cocostudio::MovementEventType movementType, const std::string& movementID)> &callback);

	void pause();
	void resume();
	void stop();

protected:
	std::string m_animationName;
	cocostudio::Armature *m_pArmature;	

};

#endif // AnimationController_h__

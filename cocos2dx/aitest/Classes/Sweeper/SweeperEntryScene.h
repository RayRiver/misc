#ifndef SweeperEntryScene_h__
#define SweeperEntryScene_h__

#include "cocos2d.h"

class SweeperEntryScene : public cocos2d::Scene
{
public:
	CREATE_FUNC(SweeperEntryScene);

	void onEnter();

private:
	bool init();
};

#endif // SweeperEntryScene_h__

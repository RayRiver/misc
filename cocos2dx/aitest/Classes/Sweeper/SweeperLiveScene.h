#ifndef SweeperLiveScene_h__
#define SweeperLiveScene_h__

#include <vector>
#include <map>

#include "BaseScene.h"

#include "utils/Fixed.h"

#include "SweeperObject.h"
#include "MineObject.h"

class SweeperLiveScene : public BaseScene
{
public:
	CREATE_FUNC(SweeperLiveScene);
	SweeperLiveScene();
	~SweeperLiveScene();

	void startGeneration();
	void update(float dt);

private:
	bool init();

	FixedPoint randomFixedPosition();

private:
	cocos2d::Label *m_labelGeneration;

	int m_generationCurrentTicks;

	std::set<MineObject *> m_mines;
	std::vector<SweeperObject *> m_sweepers;

};

#endif // SweeperLiveScene_h__

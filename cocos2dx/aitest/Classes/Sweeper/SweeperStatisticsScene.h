#ifndef SweeperStatisticsScene_h__
#define SweeperStatisticsScene_h__

#include "cocos2d.h"

#include "BaseScene.h"

class SweeperStatisticsScene : public BaseScene
{
public:
	CREATE_FUNC(SweeperStatisticsScene);
	SweeperStatisticsScene();
	~SweeperStatisticsScene();

	void startGeneration();

private:
	bool init();

};

#endif // SweeperStatisticsScene_h__

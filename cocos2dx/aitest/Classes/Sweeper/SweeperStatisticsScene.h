#ifndef SweeperStatisticsScene_h__
#define SweeperStatisticsScene_h__

#include "cocos2d.h"

#include <vector>
#include <set>

#include "utils/Fixed.h"
#include "BaseScene.h"

class SweeperObject;
class MineObject;
class SweeperStatisticsScene : public BaseScene
{
public:
	CREATE_FUNC(SweeperStatisticsScene);
	SweeperStatisticsScene();
	~SweeperStatisticsScene();

	void update(float dt);

	void startGeneration();
	FixedPoint randomFixedPosition();

private:
	bool init();
	void drawStatistics();

private:
	std::vector<SweeperObject *> m_sweepers;	
	std::set<MineObject *> m_mines;

	cocos2d::Label *m_labelGeneration;
	int m_generationCurrentTicks;

	cocos2d::DrawNode *m_coordinateRenderer;
	cocos2d::DrawNode *m_averageFitnessRenderer;
	cocos2d::DrawNode *m_bestFitnessRenderer;
	cocos2d::DrawNode *m_worstFitnessRenderer;
	cocos2d::Label *m_labelBestFitness;
	cocos2d::Label *m_labelWorstFitness;
	cocos2d::Label *m_labelAverageFitness;
};

#endif // SweeperStatisticsScene_h__

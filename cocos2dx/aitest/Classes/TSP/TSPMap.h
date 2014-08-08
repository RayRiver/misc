#ifndef TSPMap_h__
#define TSPMap_h__

#include <vector>

#include "cocos2d.h"

#include "BaseScene.h"
#include "TSPAlgorithm.h"

class TSPMap : public BaseScene
{
public:
	~TSPMap();
	static TSPMap *instance();
	static void destroy();

	void start();
	void nextGeneration(float dt);

	// 最短路径;
	inline double bestPossibleRoute() { return m_bestPossibleRoute; }

	// 获取路径的总长度;
	double getTotalLength(const std::vector<int> &path);

private:
	TSPMap();
	bool init();
	void createPoints();
	void renderPoints();
	void calcBestPossibleRoute();

private:
	static TSPMap *s_instance;
	std::vector<cocos2d::Vec2> m_points;

	double m_bestPossibleRoute;

	TSPAlgorithm m_algorithm;

	cocos2d::ui::Widget *m_ui;

	cocos2d::DrawNode *m_pointRenderer;
	cocos2d::DrawNode *m_routeRenderer;
	std::vector<cocos2d::Label *> m_pointLabelRenderers;

	float m_generationInterval;
	float m_crossoverRate;
	float m_mutateRate;
	int m_populationNumber;
	int m_nPoints;
	int m_nBestToAdd;
};

#endif // TSPMap_h__

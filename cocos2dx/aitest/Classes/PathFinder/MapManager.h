#ifndef MapManager_h__
#define MapManager_h__

#include "cocos2d.h"

#include <vector>
#include <map>

#include "BaseScene.h"
#include "PathMap.h"

class GenomeManager;
class MapManager : public BaseScene
{
public:
	enum class GridType
	{
		None = 0,
		Barrier = 1,
		Start = 2,
		End = 3,
	};

public:
	~MapManager();
	static MapManager *instance();
	static void destroy();

	void start();
	void clear();

	inline PathMap &getCurrentMap() { return m_currentMap; }
	inline PathMap &getMemoryMap() { return m_memoryMap; }
	inline void setMemoryMap(const PathMap &m) { m_memoryMap = m; }

private:
	MapManager();
	static MapManager *s_instance;
	bool init();
	void nextGeneration(float dt);

	void createRenderers(const PathMap &m);
	void renderMemory(const PathMap &m);

private:
	GenomeManager *m_genomeManager;
	PathMap m_currentMap, m_memoryMap;
	std::map<int, cocos2d::DrawNode *> m_mapRenderers;
	std::map<int, cocos2d::DrawNode *> m_memoryRenderers;

	cocos2d::ui::Widget *m_ui;

	float m_generationInterval;
	float m_crossoverRate;
	float m_mutateRate;
	int m_populationNumber;
	int m_geneNumber;
};

#endif // MapManager_h__

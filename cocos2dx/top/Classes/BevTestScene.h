#ifndef __BEV_TEST_SCENE_H__
#define __BEV_TEST_SCENE_H__

#include "cocos2d.h"

class TestSprite : public cocos2d::Sprite
{
public:
	enum class State
	{
		Ready,
		Running,
		Finish,
	};

	static TestSprite* create(const std::string& filename);
	virtual bool initWithFile(const std::string& filename);

	inline State getState() { return m_state; }
	inline void setState(State state) { m_state = state; }

	inline bool getMoved() { return m_bMoved; }
	inline void setMoved(bool moved) { m_bMoved = moved; }

private:
	State m_state;
	bool m_bMoved;
};

struct InputData
{
	TestSprite *sprite;
};
struct OutputData
{
	TestSprite *sprite;
};

class BTNode;
class BevTestScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(BevTestScene);

	void behaviorTreeUpdate(float dt);

private:
	InputData m_inputData;
	OutputData m_outputData;

	BTNode *m_bevTreeRoot;
};

#endif // __BEV_TEST_SCENE_H__

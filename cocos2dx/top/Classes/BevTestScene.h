#ifndef __BEV_TEST_SCENE_H__
#define __BEV_TEST_SCENE_H__

#include "cocos2d.h"

struct InputData
{
	int id;
};
struct OutputData
{
	int returnValue;
};

class BevNode;
class BevTestScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();
	virtual bool init();  
	CREATE_FUNC(BevTestScene);

	virtual void update(float dt);

private:
	InputData m_inputData;
	OutputData m_outputData;

	BevNode *m_bevTreeRoot;
};

#endif // __BEV_TEST_SCENE_H__

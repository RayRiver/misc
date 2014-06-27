#include "BevTestScene.h"

#include "BehaviorTree.h"

USING_NS_CC;

class NOD_MoveTo : public BevNodeTerminal
{
public:
	NOD_MoveTo(BevNode *parent)
		: BevNodeTerminal(parent)
	{

	}

protected:
	virtual BevRunningStatus _doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)	
	{
		const InputData &inputData = input.getRealData<InputData>();
		OutputData &outputData = output.getRealData<OutputData>();

		log("do move to action");

		return BevRunningStatus::Finish;
	}
};

class NOD_Turn : public BevNodeTerminal
{
public:
	NOD_Turn(BevNode *parent)
		: BevNodeTerminal(parent)
	{

	}

protected:
	virtual BevRunningStatus _doExecute(const BevNodeInputParam& input, BevNodeOutputParam& output)	
	{
		const InputData &inputData = input.getRealData<InputData>();
		OutputData &outputData = output.getRealData<OutputData>();

		log("do turn action");

		return BevRunningStatus::Finish;
	}
};

class CON_ReachedTargetArea : public BevNodePrecondition
{
public:
	virtual bool externalCondition(const BevNodeInputParam& input) const
	{
		const InputData&  inputData	= input.getRealData<InputData>();

		return true;
	}
};

Scene* BevTestScene::createScene()
{
	auto scene = Scene::create();
	auto layer = BevTestScene::create();
	scene->addChild(layer);
	return scene;
}

bool BevTestScene::init()
{
	if ( !Layer::init() )
	{
		return false;
	}


	BevNode &ret = BevNodeFactory::createPrioritySelectorNode(nullptr, "root");
	m_bevTreeRoot = &ret;
	BevNodeFactory::createTerminalNode<NOD_Turn>(m_bevTreeRoot, "action turn").setPrecondition(new CON_ReachedTargetArea());
	BevNodeFactory::createTerminalNode<NOD_MoveTo>(m_bevTreeRoot, "action move to").setPrecondition(new BevNodePreconditionTRUE());

	this->scheduleUpdate();

	return true;
}

void BevTestScene::update(float dt)
{
	BevNodeInputParam input(&m_inputData);
	BevNodeInputParam output(&m_outputData);
	if (m_bevTreeRoot && m_bevTreeRoot->doEvaluate(input))
	{
		m_bevTreeRoot->doTick(input, output);
	}
}

#include "BevTestScene.h"

#include "VisibleRect.h"
#include "BehaviorTree.h"

USING_NS_CC;

TestSprite* TestSprite::create(const std::string& filename)
{
	TestSprite *sprite = new (std::nothrow) TestSprite();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool TestSprite::initWithFile(const std::string& filename)
{
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	m_state = State::Ready;

	return true;
}

class NOD_MoveTo : public BTNodeAction
{
public:
	NOD_MoveTo(BTNode *parent)
		: BTNodeAction(parent)
	{

	}

protected:
	virtual BTRunningStatus onExecute(const BTInputParam& input, BTOutputParam& output)	
	{
		const InputData &inputData = input.getRealData<InputData>();
		OutputData &outputData = output.getRealData<OutputData>();

		auto sprite = inputData.sprite;
		TestSprite::State state = sprite->getState();

		if (state == TestSprite::State::Ready)
		{
			sprite->runAction(Sequence::create(MoveTo::create(2.0f, Point(VisibleRect::center().x+100, VisibleRect::center().y)), DelayTime::create(1.0f), CallFunc::create([=]() {
				sprite->setState(TestSprite::State::Ready);
			}), nullptr));
			sprite->setState(TestSprite::State::Running);
			return BTRunningStatus::Executing;
		}
		else if (state == TestSprite::State::Running)
		{
			return BTRunningStatus::Executing;
		}	
		else if (state == TestSprite::State::Finish)
		{
			sprite->setState(TestSprite::State::Ready);
			return BTRunningStatus::Finish;
		}

		return BTRunningStatus::Finish;
	}
};

class NOD_Turn : public BTNodeAction
{
public:
	NOD_Turn(BTNode *parent)
		: BTNodeAction(parent)
	{

	}

protected:
	virtual BTRunningStatus onExecute(const BTInputParam& input, BTOutputParam& output)	
	{
		const InputData &inputData = input.getRealData<InputData>();
		OutputData &outputData = output.getRealData<OutputData>();

		auto sprite = inputData.sprite;
		TestSprite::State state = sprite->getState();

		if (state == TestSprite::State::Ready)
		{
			sprite->runAction(Sequence::create(ScaleBy::create(1.0f, -1.0f, 1.0f), DelayTime::create(1.0f), CallFunc::create([=]() {
				sprite->setState(TestSprite::State::Ready);
			}), nullptr));
			sprite->setState(TestSprite::State::Running);
			return BTRunningStatus::Executing;
		}
		else if (state == TestSprite::State::Running)
		{
			return BTRunningStatus::Executing;
		}	
		else if (state == TestSprite::State::Finish)
		{
			sprite->setState(TestSprite::State::Ready);
			return BTRunningStatus::Finish;
		}

		return BTRunningStatus::Finish;
	}

};

class CON_ReachedTargetArea : public BTPrecondition
{
public:
	virtual bool onEvaluate(const BTInputParam& input) const
	{
		const InputData&  inputData	= input.getRealData<InputData>();

		auto sprite = inputData.sprite;

		if (sprite->getPositionX() > VisibleRect::center().x)
		{
			return true;
		}
		else
		{
			return false;
		}
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

	auto sprite = TestSprite::create("CloseNormal.png");
	sprite->setPosition(VisibleRect::left());
	this->addChild(sprite);

	m_inputData.sprite = sprite;
	m_outputData.sprite = sprite;

	BTNode &ret = BTNodeFactory::createPrioritySelectorNode(nullptr, "root");
	m_bevTreeRoot = &ret;
	BTNodeFactory::createActionNode<NOD_Turn>(m_bevTreeRoot, "action turn").setPrecondition(new CON_ReachedTargetArea());
	BTNodeFactory::createActionNode<NOD_MoveTo>(m_bevTreeRoot, "action move to").setPrecondition(new BTPreconditionTRUE());

	this->schedule(schedule_selector(BevTestScene::behaviorTreeUpdate), 0.2f); // 200ms做一次决策

	return true;
}

void BevTestScene::behaviorTreeUpdate(float dt)
{
	BTInputParam input(&m_inputData);
	BTInputParam output(&m_outputData);
	if (m_bevTreeRoot && m_bevTreeRoot->evaluate(input))
	{
		m_bevTreeRoot->update(input, output);
	}
}

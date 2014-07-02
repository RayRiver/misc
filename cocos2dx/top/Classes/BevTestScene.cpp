#include "BevTestScene.h"

#include "VisibleRect.h"
#include "Utils.h"
#include "BehaviorTree.h"
#include "BTDebugRenderer.h"

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
	m_state2 = State::Ready;
	m_bMoved = false;

	return true;
}

class NOD_MoveTo : public BTNodeAction
{
public:
	NOD_MoveTo(BTPrecondition *precondition = nullptr)
		: BTNodeAction(precondition)
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
			auto pos = sprite->getPosition();
			Point target = VisibleRect::center();
			if (pos.x < VisibleRect::center().x)
			{
				target.x = VisibleRect::center().x / 2 * 3;
			}
			else
			{
				target.x = VisibleRect::center().x / 2;
			}

			sprite->runAction(Sequence::create(MoveTo::create(2.0f, target), DelayTime::create(1.0f), CallFunc::create([=]() {
				sprite->setState(TestSprite::State::Finish);
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
			sprite->setMoved(true);
			return BTRunningStatus::Finish;
		}

		return BTRunningStatus::Finish;
	}
};

class NOD_Turn : public BTNodeAction
{
public:
	NOD_Turn(BTPrecondition *precondition = nullptr)
		: BTNodeAction(precondition)
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
				sprite->setState(TestSprite::State::Finish);
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

class NOD_Jump : public BTNodeAction
{
public:
	NOD_Jump(BTPrecondition *precondition = nullptr)
		: BTNodeAction(precondition)
	{

	}

protected:
	virtual BTRunningStatus onExecute(const BTInputParam& input, BTOutputParam& output)	
	{
		const InputData &inputData = input.getRealData<InputData>();
		OutputData &outputData = output.getRealData<OutputData>();

		auto sprite = inputData.sprite;
		TestSprite::State state = sprite->getState2();

		if (state == TestSprite::State::Ready)
		{
			sprite->runAction(Sequence::create(JumpBy::create(1.0f, Point::ZERO, 50.0f, 1), DelayTime::create(1.0f), CallFunc::create([=]() {
				sprite->setState2(TestSprite::State::Finish);
			}), nullptr));
			sprite->setState2(TestSprite::State::Running);
			return BTRunningStatus::Executing;
		}
		else if (state == TestSprite::State::Running)
		{
			return BTRunningStatus::Executing;
		}	
		else if (state == TestSprite::State::Finish)
		{
			sprite->setState2(TestSprite::State::Ready);
			return BTRunningStatus::Finish;
		}

		return BTRunningStatus::Finish;
	}

};

class NOD_SequenceEnd : public BTNodeAction
{
public:
	NOD_SequenceEnd(BTPrecondition *precondition = nullptr)
		: BTNodeAction(precondition)
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
			sprite->runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([=]() {
				sprite->setState(TestSprite::State::Finish);
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
			sprite->setMoved(false);
			return BTRunningStatus::Finish;
		}

		return BTRunningStatus::Finish;
	}

};

class CON_HasMoved : public BTPrecondition
{
public:
	virtual bool onEvaluate(const BTInputParam& input) const
	{
		const InputData&  inputData	= input.getRealData<InputData>();

		auto sprite = inputData.sprite;

		if (sprite->getMoved())
		{
			return true;
		}
		else
		{
			return false;
		}
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


	// another way
	if (0)
	{
		m_bevTreeRoot = new BTNodePrioritySelector(nullptr);

		m_bevTreeRoot
		->addChild("action move to", new NOD_MoveTo(new BTPreconditionNOT(new CON_HasMoved)) )
		->addChild(
			"control sequence 1", (new BTNodeSequence(new BTPreconditionNOT(new CON_ReachedTargetArea))) 
				->addChild("control loop 1", (new BTNodeLoop(2))
					->addChild("action turn 1", new NOD_Turn)
				)
				->addChild("action seq end 1", new NOD_SequenceEnd)
		)
		->addChild(
			"control sequence 2", (new BTNodeSequence(new CON_ReachedTargetArea))
				->addChild("action turn 2", new NOD_Turn)
				->addChild("control parallel", (new BTNodeParallel(BTNodeParallel::FinishCondition::AND))
					->addChild("action mixed jump", new NOD_Jump)
					->addChild("action mixed turn", new NOD_Turn)
				)
				->addChild("action seq end 2", new NOD_SequenceEnd)
		);

		/*
		m_bevTreeRoot
		->addChild(new NOD_MoveTo(new BTPreconditionNOT(new CON_HasMoved)) )
		->addChild(
			(new BTNodeSequence(new BTPreconditionNOT(new CON_ReachedTargetArea))) 
				->addChild((new BTNodeLoop(2))
					->addChild(new NOD_Turn)
				)
				->addChild(new NOD_SequenceEnd)
		)
		->addChild(
			(new BTNodeSequence(new CON_ReachedTargetArea))
				->addChild(new NOD_Turn)
				->addChild((new BTNodeParallel(BTNodeParallel::FinishCondition::AND))
					->addChild(new NOD_Jump)
					->addChild(new NOD_Turn)
				)
				->addChild(new NOD_SequenceEnd)
		);
		*/
	}
	else
	{
		BTNode &ret = BTNodeFactory::createPrioritySelectorNode(nullptr, Utils::gettext("btnode_control_priority_select"));
		m_bevTreeRoot = &ret;
		{
			auto &root = *m_bevTreeRoot;

			{
				BTNodeFactory::createActionNode<NOD_MoveTo>(&root, Utils::gettext("btnode_action_moveto")).setPrecondition(new BTPreconditionNOT(new CON_HasMoved), Utils::gettext("btprecondition_hadmoved"));
			}

			{
				BTNode &seq = BTNodeFactory::createSequenceNode(&root, Utils::gettext("btnode_control_sequence")).setPrecondition(new BTPreconditionNOT(new CON_ReachedTargetArea), Utils::gettext("btprecondition_not_reachedtargetarea"));
				{
					BTNode &loop = BTNodeFactory::createLoopNode(&seq, Utils::gettext("btnode_control_loop"), 2);
					{
						BTNodeFactory::createActionNode<NOD_Turn>(&loop, Utils::gettext("btnode_action_turn"));
					}
					BTNodeFactory::createActionNode<NOD_SequenceEnd>(&seq, Utils::gettext("btnode_action_seqend"));
				}
			}

			{
				BTNode &seq = BTNodeFactory::createSequenceNode(&root, Utils::gettext("btnode_control_sequence")).setPrecondition(new CON_ReachedTargetArea, Utils::gettext("btprecondition_reachedtargetarea"));
				{
					BTNodeFactory::createActionNode<NOD_Turn>(&seq, Utils::gettext("btnode_action_turn"));
					BTNode &parallel = BTNodeFactory::createParallelNode(&seq, Utils::gettext("btnode_control_parallel"));
					{
						BTNodeFactory::createActionNode<NOD_Turn>(&parallel, Utils::gettext("btnode_action_turn"));
						BTNodeFactory::createActionNode<NOD_Jump>(&parallel, Utils::gettext("btnode_action_jump"));
					}
					BTNodeFactory::createActionNode<NOD_SequenceEnd>(&seq, Utils::gettext("btnode_action_seqend"));
				}
			}
		}
	}	

	auto renderer = BTDebugRenderer::create(m_bevTreeRoot);
	this->addChild(renderer, 10001);

	//sprite->setPosition(VisibleRect::center());
	//sprite->runAction(Sequence::create(ScaleBy::create(1.0f, -1.0f, 1.0f), DelayTime::create(1.0f), CallFunc::create([=](){}), nullptr));
	//sprite->runAction(Sequence::create(JumpBy::create(1.0f, Point::ZERO, 50.0f, 1), DelayTime::create(1.0f), CallFunc::create([=](){}), nullptr));


	//this->schedule(schedule_selector(BevTestScene::behaviorTreeUpdate), 0.2f); // 200ms做一次决策
	this->getScheduler()->schedule([=](float dt) {
		BTInputParam input(&m_inputData);
		BTInputParam output(&m_outputData);
		if (m_bevTreeRoot && m_bevTreeRoot->evaluate(input))
		{
			m_bevTreeRoot->update(input, output);
			renderer->render();
		}
	}, this, 0.2f, !_running, "behaviorTreeUpdate");

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

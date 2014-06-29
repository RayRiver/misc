// 控制节点 BTNodeLoop
// 循环节点
// evaluate: 预设的循环次数到了就返回False，否则，只调用第一个子节点的Evaluate方法，用它所返回的值作为自身的值返回
// update: 只调用第一个节点的Tick方法，若返回运行结束，则看是否需要重复运行，若循环次数没到，则自身返回运行中，若循环次数已到，则返回运行结束

#include "BTNodeLoop.h"

BTNodeLoop::BTNodeLoop( BTNode *parent, BTPrecondition *precondition /*= nullptr*/, int nLoopCount /*= BTNodeLoop::InfiniteLoop*/ )
	: BTNode(parent, precondition)
	, m_nLoopCount(nLoopCount)
	, m_nCurrentLoopCount(0)
{

}

bool BTNodeLoop::onInternalEvaluate( const BTInputParam &input )
{
	if (m_nLoopCount == BTNodeLoop::InfiniteLoop || m_nCurrentLoopCount < m_nLoopCount)
	{
		if (_isIndexValid(0))
		{
			auto node = m_childrenList[0];
			if (node->evaluate(input))
			{
				return true;
			}
		}
	}
	return false;
}

void BTNodeLoop::onTransition( const BTInputParam &input )
{
	if (_isIndexValid(0))
	{
		auto node = m_childrenList[0];
		node->transition(input);
	}
	m_nCurrentLoopCount = 0;
}

BTRunningStatus BTNodeLoop::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	BTRunningStatus runningState = BTRunningStatus::Finish;

	if (_isIndexValid(0))
	{
		auto node = m_childrenList[0];
		runningState = node->update(input, output);
		if (runningState == BTRunningStatus::Finish)
		{
			if (m_nLoopCount != InfiniteLoop)
			{
				++m_nCurrentLoopCount;
				if (m_nCurrentLoopCount < m_nLoopCount)
				{
					runningState = BTRunningStatus::Executing;
				}
			}
			else
			{
				runningState = BTRunningStatus::Executing;
			}
		}
	}

	if (runningState != BTRunningStatus::Executing)
	{
		m_nCurrentLoopCount = 0;
	}

	return runningState;
}


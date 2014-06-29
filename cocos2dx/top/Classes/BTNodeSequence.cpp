// 控制节点 BTNodeSequence
// 序列节点
// evaluate: 若是从头开始的，则调用第一个子节点的Evaluate方法，将其返回值作为自身的返回值返回。否则，调用当前运行节点的Evaluate方法，将其返回值作为自身的返回值返回。
// update: 调用可以运行的子节点的update方法，若返回运行结束，则将下一个子节点作为当前运行节点，若当前已是最后一个子节点，表示该序列已经运行结束，则自身返回运行结束。若子节点返回运行中，则用它所返回的运行状态作为自身的运行状态返回

#include "BTNodeSequence.h"

BTNodeSequence::BTNodeSequence( BTNode *parent, BTPrecondition *precondition /*= nullptr*/ )
	: BTNode(parent, precondition)
	, m_nCurrentSelectIndex(BTInvalidChildNodeIndex)
{

}

bool BTNodeSequence::onInternalEvaluate( const BTInputParam &input )
{
	int n = 0;
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		n = m_nCurrentSelectIndex;
	}

	auto node = m_childrenList[n];
	return node->evaluate(input);
}

void BTNodeSequence::onTransition( const BTInputParam &input )
{
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->transition(input);
	}
	m_nCurrentSelectIndex = BTInvalidChildNodeIndex; 
}

BTRunningStatus BTNodeSequence::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	int n = 0;
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		n = m_nCurrentSelectIndex;
	}

	auto node = m_childrenList[n];
	BTRunningStatus runningState = node->update(input, output);
	if (runningState == BTRunningStatus::Finish)
	{
		++m_nCurrentSelectIndex;
		if (m_nCurrentSelectIndex == (int)m_childrenList.size())
		{
			m_nCurrentSelectIndex = BTInvalidChildNodeIndex;
		}
		else
		{
			runningState = BTRunningStatus::Executing;
		}
	}
	else if (runningState == BTRunningStatus::Terminal)
	{
		m_nCurrentSelectIndex = BTInvalidChildNodeIndex;
	}

	return runningState;
}


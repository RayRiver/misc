// 控制节点 BevNodeSequence
// 序列节点
// evaluate: 若是从头开始的，则调用第一个子节点的Evaluate方法，将其返回值作为自身的返回值返回。否则，调用当前运行节点的Evaluate方法，将其返回值作为自身的返回值返回。
// update: 调用可以运行的子节点的update方法，若返回运行结束，则将下一个子节点作为当前运行节点，若当前已是最后一个子节点，表示该序列已经运行结束，则自身返回运行结束。若子节点返回运行中，则用它所返回的运行状态作为自身的运行状态返回

#include "BevNodeSequence.h"

BevNodeSequence::BevNodeSequence( BevNode *parent, BevPrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
	, m_nCurrentSelectIndex(BevInvalidChildNodeIndex)
{

}

bool BevNodeSequence::onInternalEvaluate( const BevInputParam &input )
{
	int n = 0;
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		n = m_nCurrentSelectIndex;
	}

	auto node = m_childrenList[n];
	return node->evaluate(input);
}

void BevNodeSequence::onTransition( const BevInputParam &input )
{
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->transition(input);
	}
	m_nCurrentSelectIndex = BevInvalidChildNodeIndex; 
}

BevRunningStatus BevNodeSequence::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	int n = 0;
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		n = m_nCurrentSelectIndex;
	}

	auto node = m_childrenList[n];
	BevRunningStatus runningState = node->update(input, output);
	if (runningState == BevRunningStatus::Finish)
	{
		++m_nCurrentSelectIndex;
		if (m_nCurrentSelectIndex == (int)m_childrenList.size())
		{
			m_nCurrentSelectIndex = BevInvalidChildNodeIndex;
		}
		else
		{
			runningState = BevRunningStatus::Executing;
		}
	}
	else if (runningState == BevRunningStatus::Terminal)
	{
		m_nCurrentSelectIndex = BevInvalidChildNodeIndex;
	}

	return runningState;
}


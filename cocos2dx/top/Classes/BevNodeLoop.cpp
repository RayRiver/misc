// ���ƽڵ� BevNodeLoop
// ѭ���ڵ�
// evaluate: Ԥ���ѭ���������˾ͷ���False������ֻ���õ�һ���ӽڵ��Evaluate���������������ص�ֵ��Ϊ�����ֵ����
// update: ֻ���õ�һ���ڵ��Tick���������������н��������Ƿ���Ҫ�ظ����У���ѭ������û�����������������У���ѭ�������ѵ����򷵻����н���

#include "BevNodeLoop.h"

BevNodeLoop::BevNodeLoop( BevNode *parent, BevPrecondition *precondition /*= nullptr*/, int nLoopCount /*= BevNodeLoop::InfiniteLoop*/ )
	: BevNode(parent, precondition)
	, m_nLoopCount(nLoopCount)
	, m_nCurrentLoopCount(0)
{

}

bool BevNodeLoop::onInternalEvaluate( const BevInputParam &input )
{
	if (m_nLoopCount == BevNodeLoop::InfiniteLoop || m_nCurrentLoopCount < m_nLoopCount)
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

void BevNodeLoop::onTransition( const BevInputParam &input )
{
	if (_isIndexValid(0))
	{
		auto node = m_childrenList[0];
		node->transition(input);
	}
	m_nCurrentLoopCount = 0;
}

BevRunningStatus BevNodeLoop::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	BevRunningStatus runningState = BevRunningStatus::Finish;

	if (_isIndexValid(0))
	{
		auto node = m_childrenList[0];
		runningState = node->update(input, output);
		if (runningState == BevRunningStatus::Finish)
		{
			if (m_nLoopCount != InfiniteLoop)
			{
				++m_nCurrentLoopCount;
				if (m_nCurrentLoopCount < m_nLoopCount)
				{
					runningState = BevRunningStatus::Executing;
				}
			}
			else
			{
				runningState = BevRunningStatus::Executing;
			}
		}
	}

	if (runningState != BevRunningStatus::Executing)
	{
		m_nCurrentLoopCount = 0;
	}

	return runningState;
}


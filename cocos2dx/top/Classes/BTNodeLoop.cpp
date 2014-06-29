// ���ƽڵ� BTNodeLoop
// ѭ���ڵ�
// evaluate: Ԥ���ѭ���������˾ͷ���False������ֻ���õ�һ���ӽڵ��Evaluate���������������ص�ֵ��Ϊ�����ֵ����
// update: ֻ���õ�һ���ڵ��Tick���������������н��������Ƿ���Ҫ�ظ����У���ѭ������û�����������������У���ѭ�������ѵ����򷵻����н���

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


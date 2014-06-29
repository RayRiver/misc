// ���ƽڵ� BTNodeSequence
// ���нڵ�
// evaluate: ���Ǵ�ͷ��ʼ�ģ�����õ�һ���ӽڵ��Evaluate���������䷵��ֵ��Ϊ����ķ���ֵ���ء����򣬵��õ�ǰ���нڵ��Evaluate���������䷵��ֵ��Ϊ����ķ���ֵ���ء�
// update: ���ÿ������е��ӽڵ��update���������������н���������һ���ӽڵ���Ϊ��ǰ���нڵ㣬����ǰ�������һ���ӽڵ㣬��ʾ�������Ѿ����н����������������н��������ӽڵ㷵�������У������������ص�����״̬��Ϊ���������״̬����

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


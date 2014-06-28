// ���ƽڵ� BevNodeSequence
// ���нڵ�
// evaluate: ���Ǵ�ͷ��ʼ�ģ�����õ�һ���ӽڵ��Evaluate���������䷵��ֵ��Ϊ����ķ���ֵ���ء����򣬵��õ�ǰ���нڵ��Evaluate���������䷵��ֵ��Ϊ����ķ���ֵ���ء�
// update: ���ÿ������е��ӽڵ��update���������������н���������һ���ӽڵ���Ϊ��ǰ���нڵ㣬����ǰ�������һ���ӽڵ㣬��ʾ�������Ѿ����н����������������н��������ӽڵ㷵�������У������������ص�����״̬��Ϊ���������״̬����

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


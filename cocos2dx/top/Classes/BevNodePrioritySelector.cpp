// ���ƽڵ�
// �����ȼ���ѡ��ڵ㣬���ȼ������������ν���

#include "BevNodePrioritySelector.h"

BevNodePrioritySelector::BevNodePrioritySelector( BevNode *parent, BevNodePrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
	, m_nEvaluateSelectIndex(BevInvalidChildNodeIndex)
	, m_nCurrentSelectIndex(BevInvalidChildNodeIndex)
{

}

bool BevNodePrioritySelector::_doInternalEvaluate( const BevNodeInputParam &input )
{
	m_nEvaluateSelectIndex = BevInvalidChildNodeIndex;
	int count = (int)m_childrenList.size();
	for (int i=0; i<count; ++i)
	{
		BevNode *node = m_childrenList[i];
		if (node->doEvaluate(input))
		{
			m_nEvaluateSelectIndex = i;
			return true;
		}
	}
	return false;
}

void BevNodePrioritySelector::_doTransition( const BevNodeInputParam &input )
{
	// �����ڵ���Ч�Ļ������γ�ʼ���������е��ӽڵ�
	if (m_nEvaluateSelectIndex != BevInvalidChildNodeIndex)
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->doTransition(input);
		m_nCurrentSelectIndex = BevInvalidChildNodeIndex;
	}
}

BevRunningStatus BevNodePrioritySelector::_doTick( const BevNodeInputParam &input, BevNodeOutputParam &output )
{
	// �������вŻ��߽���
	assert(m_nEvaluateSelectIndex != BevInvalidChildNodeIndex);

	if (m_nEvaluateSelectIndex == m_nCurrentSelectIndex)
	{
		return BevRunningStatus::Finish;
	}
	else
	{
		// ����ѡ���Ľڵ���������еĽڵ㲻ͬ����Ҫtransition
		this->_doTransition(input);
		m_nCurrentSelectIndex = m_nEvaluateSelectIndex;

		// �ӽڵ�һ��dotick
		auto node = m_childrenList[m_nCurrentSelectIndex];
		BevRunningStatus state = node->doTick(input, output);
		if (state != BevRunningStatus::Executing)
		{
			// �ӽڵ�ִ����ϣ���ʼ��״̬
			m_nCurrentSelectIndex = BevInvalidChildNodeIndex;	
		}

		return state;
	}
}

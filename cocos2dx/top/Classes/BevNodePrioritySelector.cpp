// ���ƽڵ� BevNodePrioritySelector
// �����ȼ���ѡ��ڵ�
// evaluate: �ӵ�һ���ӽڵ㿪ʼ���α������е��ӽڵ㣬������evaluate�����������ִ��ڿ������е��ӽڵ�ʱ����¼�ӽڵ�������ֹͣ����������true 
// update: ���ÿ������е��ӽڵ��update���������������ص�����״̬��Ϊ���������״̬����

#include "BevNodePrioritySelector.h"

BevNodePrioritySelector::BevNodePrioritySelector( BevNode *parent, BevPrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
	, m_nEvaluateSelectIndex(BevInvalidChildNodeIndex)
	, m_nCurrentSelectIndex(BevInvalidChildNodeIndex)
{

}

bool BevNodePrioritySelector::onInternalEvaluate( const BevInputParam &input )
{
	m_nEvaluateSelectIndex = BevInvalidChildNodeIndex;
	int count = (int)m_childrenList.size();
	for (int i=0; i<count; ++i)
	{
		BevNode *node = m_childrenList[i];
		if (node->evaluate(input))
		{
			m_nEvaluateSelectIndex = i;
			return true;
		}
	}
	return false;
}

void BevNodePrioritySelector::onTransition( const BevInputParam &input )
{
	// �����ڵ���Ч�Ļ������γ�ʼ���������е��ӽڵ�
	if (m_nCurrentSelectIndex != BevInvalidChildNodeIndex)
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->transition(input);
		m_nCurrentSelectIndex = BevInvalidChildNodeIndex;
	}
}

BevRunningStatus BevNodePrioritySelector::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	// �������вŻ��߽���
	if (!_isIndexValid(m_nEvaluateSelectIndex))
	{
		assert(false);
		return BevRunningStatus::Finish;	
	}

	// ����ѡ���Ľڵ���������еĽڵ㲻ͬ����Ҫtransition
	if (m_nEvaluateSelectIndex != m_nCurrentSelectIndex)
	{
		this->transition(input);
		m_nCurrentSelectIndex = m_nEvaluateSelectIndex;
	}

	// �����еĽڵ�
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		BevRunningStatus state = node->update(input, output);
		if (state != BevRunningStatus::Executing)
		{
			// �ӽڵ�ִ����ϣ���ʼ��״̬
			m_nCurrentSelectIndex = BevInvalidChildNodeIndex;	
		}
		return state;
	}

	assert(false);
	return BevRunningStatus::Finish;
}

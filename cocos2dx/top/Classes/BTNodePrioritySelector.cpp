// ���ƽڵ� BTNodePrioritySelector
// �����ȼ���ѡ��ڵ�
// evaluate: �ӵ�һ���ӽڵ㿪ʼ���α������е��ӽڵ㣬������evaluate�����������ִ��ڿ������е��ӽڵ�ʱ����¼�ӽڵ�������ֹͣ����������true 
// update: ���ÿ������е��ӽڵ��update���������������ص�����״̬��Ϊ���������״̬����

#include "BTNodePrioritySelector.h"

BTNodePrioritySelector::BTNodePrioritySelector( BTPrecondition *precondition /*= nullptr*/ )
	: BTNode(precondition)
	, m_nEvaluateSelectIndex(BTInvalidChildNodeIndex)
	, m_nCurrentSelectIndex(BTInvalidChildNodeIndex)
{

}

bool BTNodePrioritySelector::onInternalEvaluate( const BTInputParam &input )
{
	m_nEvaluateSelectIndex = BTInvalidChildNodeIndex;
	int count = (int)m_childrenList.size();
	for (int i=0; i<count; ++i)
	{
		BTNode *node = m_childrenList[i];
		if (node->evaluate(input))
		{
			m_nEvaluateSelectIndex = i;
			return true;
		}
	}
	return false;
}

void BTNodePrioritySelector::onTransition( const BTInputParam &input )
{
	// �����ڵ���Ч�Ļ������γ�ʼ���������е��ӽڵ�
	if (m_nCurrentSelectIndex != BTInvalidChildNodeIndex)
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->transition(input);
		m_nCurrentSelectIndex = BTInvalidChildNodeIndex;
	}
}

BTRunningStatus BTNodePrioritySelector::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	// �������вŻ��߽���
	if (!_isIndexValid(m_nEvaluateSelectIndex))
	{
		assert(false);
		return BTRunningStatus::Finish;	
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
		BTRunningStatus state = node->update(input, output);
		if (state != BTRunningStatus::Executing)
		{
			// �ӽڵ�ִ����ϣ���ʼ��״̬
			m_nCurrentSelectIndex = BTInvalidChildNodeIndex;	
		}
		return state;
	}

	assert(false);
	return BTRunningStatus::Finish;
}

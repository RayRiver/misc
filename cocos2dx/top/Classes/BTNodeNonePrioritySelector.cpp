// ���ƽڵ� BTNodeNonePrioritySelector
// �������ȼ���ѡ��ڵ�
// evaluate: �ȵ�����һ�����е��ӽڵ㣨�����ڣ���evaluate����������������У�������˱���ýڵ������������true������������У�������ѡ��ͬ�����ȼ���ѡ��ڵ��ѡ��ʽ��
// update: ���ÿ������е��ӽڵ��update���������������ص�����״̬��Ϊ���������״̬����

#include "BTNodeNonePrioritySelector.h"

BTNodeNonePrioritySelector::BTNodeNonePrioritySelector( BTPrecondition *precondition /*= nullptr*/ )
	: BTNodePrioritySelector(precondition)
{

}

bool BTNodeNonePrioritySelector::onInternalEvaluate( const BTInputParam &input )
{
	if (_isIndexValid(m_nEvaluateSelectIndex))
	{
		auto node = m_childrenList[m_nEvaluateSelectIndex];
		if (node->evaluate(input))
		{
			return true;
		}
	}
	return BTNodePrioritySelector::onInternalEvaluate(input);
}

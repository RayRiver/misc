// ���ƽڵ� BevNodeNonePrioritySelector
// �������ȼ���ѡ��ڵ�
// evaluate: �ȵ�����һ�����е��ӽڵ㣨�����ڣ���evaluate����������������У�������˱���ýڵ������������true������������У�������ѡ��ͬ�����ȼ���ѡ��ڵ��ѡ��ʽ��
// update: ���ÿ������е��ӽڵ��update���������������ص�����״̬��Ϊ���������״̬����

#include "BevNodeNonePrioritySelector.h"

BevNodeNonePrioritySelector::BevNodeNonePrioritySelector( BevNode *parent, BevPrecondition *precondition /*= nullptr*/ )
	: BevNodePrioritySelector(parent, precondition)
{

}

bool BevNodeNonePrioritySelector::onInternalEvaluate( const BevInputParam &input )
{
	if (_isIndexValid(m_nEvaluateSelectIndex))
	{
		auto node = m_childrenList[m_nEvaluateSelectIndex];
		if (node->evaluate(input))
		{
			return true;
		}
	}
	return BevNodePrioritySelector::onInternalEvaluate(input);
}

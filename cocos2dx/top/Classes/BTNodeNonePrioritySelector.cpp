// 控制节点 BTNodeNonePrioritySelector
// 不带优先级的选择节点
// evaluate: 先调用上一个运行的子节点（若存在）的evaluate方法，如果可以运行，则继续运保存该节点的索引，返回true，如果不能运行，则重新选择（同带优先级的选择节点的选择方式）
// update: 调用可以运行的子节点的update方法，用它所返回的运行状态作为自身的运行状态返回

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

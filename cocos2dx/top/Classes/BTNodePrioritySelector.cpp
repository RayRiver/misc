// 控制节点 BTNodePrioritySelector
// 带优先级的选择节点
// evaluate: 从第一个子节点开始依次遍历所有的子节点，调用其evaluate方法，当发现存在可以运行的子节点时，记录子节点索引，停止遍历，返回true 
// update: 调用可以运行的子节点的update方法，用它所返回的运行状态作为自身的运行状态返回

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
	// 评估节点有效的话，依次初始化正在运行的子节点
	if (m_nCurrentSelectIndex != BTInvalidChildNodeIndex)
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->transition(input);
		m_nCurrentSelectIndex = BTInvalidChildNodeIndex;
	}
}

BTRunningStatus BTNodePrioritySelector::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	// 评估可行才会走进来
	if (!_isIndexValid(m_nEvaluateSelectIndex))
	{
		assert(false);
		return BTRunningStatus::Finish;	
	}

	// 评估选定的节点和正在运行的节点不同，需要transition
	if (m_nEvaluateSelectIndex != m_nCurrentSelectIndex)
	{
		this->transition(input);
		m_nCurrentSelectIndex = m_nEvaluateSelectIndex;
	}

	// 运行中的节点
	if (_isIndexValid(m_nCurrentSelectIndex))
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		BTRunningStatus state = node->update(input, output);
		if (state != BTRunningStatus::Executing)
		{
			// 子节点执行完毕，初始化状态
			m_nCurrentSelectIndex = BTInvalidChildNodeIndex;	
		}
		return state;
	}

	assert(false);
	return BTRunningStatus::Finish;
}

// 控制节点 BevNodePrioritySelector
// 带优先级的选择节点
// evaluate: 从第一个子节点开始依次遍历所有的子节点，调用其evaluate方法，当发现存在可以运行的子节点时，记录子节点索引，停止遍历，返回true 
// update: 调用可以运行的子节点的update方法，用它所返回的运行状态作为自身的运行状态返回

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
	// 评估节点有效的话，依次初始化正在运行的子节点
	if (m_nCurrentSelectIndex != BevInvalidChildNodeIndex)
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->transition(input);
		m_nCurrentSelectIndex = BevInvalidChildNodeIndex;
	}
}

BevRunningStatus BevNodePrioritySelector::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	// 评估可行才会走进来
	if (!_isIndexValid(m_nEvaluateSelectIndex))
	{
		assert(false);
		return BevRunningStatus::Finish;	
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
		BevRunningStatus state = node->update(input, output);
		if (state != BevRunningStatus::Executing)
		{
			// 子节点执行完毕，初始化状态
			m_nCurrentSelectIndex = BevInvalidChildNodeIndex;	
		}
		return state;
	}

	assert(false);
	return BevRunningStatus::Finish;
}

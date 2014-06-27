// 控制节点
// 有优先级的选择节点，优先级从左往右依次降低

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
	// 评估节点有效的话，依次初始化正在运行的子节点
	if (m_nEvaluateSelectIndex != BevInvalidChildNodeIndex)
	{
		auto node = m_childrenList[m_nCurrentSelectIndex];
		node->doTransition(input);
		m_nCurrentSelectIndex = BevInvalidChildNodeIndex;
	}
}

BevRunningStatus BevNodePrioritySelector::_doTick( const BevNodeInputParam &input, BevNodeOutputParam &output )
{
	// 评估可行才会走进来
	assert(m_nEvaluateSelectIndex != BevInvalidChildNodeIndex);

	if (m_nEvaluateSelectIndex == m_nCurrentSelectIndex)
	{
		return BevRunningStatus::Finish;
	}
	else
	{
		// 评估选定的节点和正在运行的节点不同，需要transition
		this->_doTransition(input);
		m_nCurrentSelectIndex = m_nEvaluateSelectIndex;

		// 子节点一次dotick
		auto node = m_childrenList[m_nCurrentSelectIndex];
		BevRunningStatus state = node->doTick(input, output);
		if (state != BevRunningStatus::Executing)
		{
			// 子节点执行完毕，初始化状态
			m_nCurrentSelectIndex = BevInvalidChildNodeIndex;	
		}

		return state;
	}
}

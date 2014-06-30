// ���ƽڵ� BTNodeParallel
// ���нڵ�
// evaluate: ���ε������е��ӽڵ��Evaluate�����������е��ӽڵ㶼����True��������Ҳ����True�����򣬷���False
// update: ���������ӽڵ��Tick�����������нڵ��ǡ����ߡ��Ĺ�ϵ����ֻҪ��һ���ӽڵ㷵�����н�����������ͷ������н����������нڵ��ǡ����ҡ��Ĺ�ϵ����ֻ�����е��ӽڵ㷵�ؽ���������ŷ������н���

#include "BTNodeParallel.h"

#include <assert.h>

BTNodeParallel::BTNodeParallel( FinishCondition finishCondition /*= FinishCondition::OR*/, BTPrecondition *precondition /*= nullptr*/ )
	: BTNode(precondition)
	, m_finishCondition(finishCondition)
{

}

bool BTNodeParallel::onInternalEvaluate( const BTInputParam &input )
{
	size_t count = m_runningStatus.size();
	size_t children_count = m_childrenList.size();
	if (count < children_count)
	{
		m_runningStatus.resize(m_childrenList.size());
		for (size_t i=count; i<children_count; ++i)
		{
			m_runningStatus[i] = BTRunningStatus::Executing;
		}
	}

	for (size_t i=0; i<children_count; ++i)
	{
		if (!m_childrenList[i]->evaluate(input))
		{
			return false;
		}
	}

	return true;
}

void BTNodeParallel::onTransition( const BTInputParam &input )
{
	initStatus();
	for (auto child : m_childrenList)
	{
		child->transition(input);
	}
}

BTRunningStatus BTNodeParallel::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	size_t children_count = m_childrenList.size();
	size_t finished_count = 0;
	for (size_t i=0; i<children_count; ++i)
	{
		BTNode *node = m_childrenList[i];
		BTRunningStatus runningState = m_runningStatus[i];
		if (m_finishCondition == FinishCondition::OR)
		{
			if (runningState == BTRunningStatus::Executing)
			{
				m_runningStatus[i] = node->update(input, output);
			}
			if (runningState != BTRunningStatus::Executing)
			{ 
				initStatus();
				return BTRunningStatus::Finish;
			}
		}
		else if (m_finishCondition == FinishCondition::AND)
		{
			if (runningState == BTRunningStatus::Executing)
			{
				m_runningStatus[i] = node->update(input, output);
			}
			if (runningState != BTRunningStatus::Executing)
			{
				++finished_count;
			}
		}
		else
		{
			assert(false);
		}

	}

	if (finished_count == children_count)
	{
		initStatus();
		return BTRunningStatus::Finish;
	}
	else
	{
		return BTRunningStatus::Executing;
	}
}

void BTNodeParallel::initStatus()
{
	for (auto &state : m_runningStatus)
	{
		state = BTRunningStatus::Executing;
	}
}


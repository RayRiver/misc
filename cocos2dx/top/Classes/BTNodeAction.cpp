#include "BTNodeAction.h"

#ifdef _BEHAVIOR_TREE_DEBUG
#include "cocos2d.h"
#include "BTDebugRenderer.h"
#endif // _BEHAVIOR_TREE_DEBUG

BTNodeAction::BTNodeAction( BTPrecondition *precondition /*= nullptr*/ )
	: BTNode(precondition)
	, m_isRunning(false)
{

}

void BTNodeAction::onEnter( const BTInputParam &input )
{
#ifdef _BEHAVIOR_TREE_DEBUG
	cocos2d::log("%s onEnter", this->m_name.c_str());
	if (BTDebugRenderer::getInstance())
	{
		BTDebugRenderer::getInstance()->renderNode(this, BTNodeEvent::enter);
	}
#endif // _BEHAVIOR_TREE_DEBUG
}

void BTNodeAction::onExit( const BTInputParam &input, BTRunningStatus state )
{
#ifdef _BEHAVIOR_TREE_DEBUG
	cocos2d::log("%s onExit", this->m_name.c_str());
	if (BTDebugRenderer::getInstance())
	{
		BTDebugRenderer::getInstance()->renderNode(this, BTNodeEvent::exit);
	}
#endif // _BEHAVIOR_TREE_DEBUG
}

BTRunningStatus BTNodeAction::onExecute( const BTInputParam &input, BTOutputParam &output )
{
	return BTRunningStatus::Finish;
}

void BTNodeAction::onTransition( const BTInputParam &input )
{
	if (m_isRunning)
	{
		onExit(input, BTRunningStatus::Terminal);
		m_isRunning = false;
	}
}

// �ߵ�doTick��ʾ���뿪ʼִ��
BTRunningStatus BTNodeAction::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	// ��ʼִ�У�����enter����
	if (!m_isRunning)
	{
		onEnter(input);
		m_isRunning = true;
	}

	BTRunningStatus running_state = onExecute(input, output);	
	if (running_state == BTRunningStatus::Executing)
	{
		// ִ��δ���
		return running_state;
	}
	else
	{
		// ִ����ɣ�����exit����
		m_isRunning = false;	
		onExit(input, running_state);
		return running_state;
	}

}


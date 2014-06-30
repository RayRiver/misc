#include "BTNodeAction.h"

#include "cocos2d.h"

BTNodeAction::BTNodeAction( BTPrecondition *precondition /*= nullptr*/ )
	: BTNode(precondition)
	, m_isRunning(false)
{

}

void BTNodeAction::onEnter( const BTInputParam &input )
{
	cocos2d::log("%s onEnter", this->m_name.c_str());
}

void BTNodeAction::onExit( const BTInputParam &input, BTRunningStatus state )
{
	cocos2d::log("%s onExit", this->m_name.c_str());
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

// 走到doTick表示必须开始执行
BTRunningStatus BTNodeAction::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	// 开始执行，调用enter方法
	if (!m_isRunning)
	{
		onEnter(input);
		m_isRunning = true;
	}

	BTRunningStatus running_state = onExecute(input, output);	
	if (running_state == BTRunningStatus::Executing)
	{
		// 执行未完成
		return running_state;
	}
	else
	{
		// 执行完成，调用exit方法
		m_isRunning = false;	
		onExit(input, running_state);
		return running_state;
	}

}


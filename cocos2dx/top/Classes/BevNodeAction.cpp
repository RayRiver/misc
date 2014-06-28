#include "BevNodeAction.h"

BevNodeAction::BevNodeAction( BevNode *parent, BevPrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
	, m_isRunning(false)
{

}

void BevNodeAction::onEnter( const BevInputParam &input )
{

}

void BevNodeAction::onExit( const BevInputParam &input, BevRunningStatus state )
{

}

BevRunningStatus BevNodeAction::onExecute( const BevInputParam &input, BevOutputParam &output )
{
	return BevRunningStatus::Finish;
}

void BevNodeAction::onTransition( const BevInputParam &input )
{
	if (m_isRunning)
	{
		onExit(input, BevRunningStatus::Terminal);
		m_isRunning = false;
	}
}

// 走到doTick表示必须开始执行
BevRunningStatus BevNodeAction::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	// 开始执行，调用enter方法
	if (!m_isRunning)
	{
		onEnter(input);
		m_isRunning = true;
	}

	BevRunningStatus running_state = onExecute(input, output);	
	if (running_state == BevRunningStatus::Executing)
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


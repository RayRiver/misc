#include "BevNodeAction.h"

BevNodeAction::BevNodeAction( BevNode *parent, BevPrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
	, m_isRunning(false)
{

}

void BevNodeAction::_doEnter( const BevInputParam &input )
{

}

void BevNodeAction::_doExit( const BevInputParam &input, BevRunningStatus state )
{

}

BevRunningStatus BevNodeAction::_doExecute( const BevInputParam &input, BevOutputParam &output )
{
	return BevRunningStatus::Finish;
}

void BevNodeAction::_doTransition( const BevInputParam &input )
{
	if (m_isRunning)
	{
		_doExit(input, BevRunningStatus::Terminal);
		m_isRunning = false;
	}
}

// 走到doTick表示必须开始执行
BevRunningStatus BevNodeAction::_doTick( const BevInputParam &input, BevOutputParam &output )
{
	// 开始执行，调用enter方法
	if (!m_isRunning)
	{
		_doEnter(input);
		m_isRunning = true;
	}

	// 每帧执行
	BevRunningStatus running_state = _doExecute(input, output);	
	if (running_state == BevRunningStatus::Executing)
	{
		// 执行未完成
		return running_state;
	}
	else
	{
		// 执行完成，调用exit方法
		m_isRunning = false;	
		_doExit(input, running_state);
		return running_state;
	}

}


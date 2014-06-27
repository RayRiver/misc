#include "BevNodeTerminal.h"

BevNodeTerminal::BevNodeTerminal( BevNode *parent, BevNodePrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
	, m_isRunning(false)
{

}

void BevNodeTerminal::_doEnter( const BevNodeInputParam &input )
{

}

void BevNodeTerminal::_doExit( const BevNodeInputParam &input, BevRunningStatus state )
{

}

BevRunningStatus BevNodeTerminal::_doExecute( const BevNodeInputParam &input, BevNodeOutputParam &output )
{
	return BevRunningStatus::Finish;
}

void BevNodeTerminal::_doTransition( const BevNodeInputParam &input )
{
	if (m_isRunning)
	{
		_doExit(input, BevRunningStatus::Terminal);
		m_isRunning = false;
	}
}

// 走到doTick表示必须开始执行
BevRunningStatus BevNodeTerminal::_doTick( const BevNodeInputParam &input, BevNodeOutputParam &output )
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


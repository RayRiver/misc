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

// �ߵ�doTick��ʾ���뿪ʼִ��
BevRunningStatus BevNodeTerminal::_doTick( const BevNodeInputParam &input, BevNodeOutputParam &output )
{
	// ��ʼִ�У�����enter����
	if (!m_isRunning)
	{
		_doEnter(input);
		m_isRunning = true;
	}

	// ÿִ֡��
	BevRunningStatus running_state = _doExecute(input, output);	
	if (running_state == BevRunningStatus::Executing)
	{
		// ִ��δ���
		return running_state;
	}
	else
	{
		// ִ����ɣ�����exit����
		m_isRunning = false;	
		_doExit(input, running_state);
		return running_state;
	}

}


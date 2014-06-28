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

// �ߵ�doTick��ʾ���뿪ʼִ��
BevRunningStatus BevNodeAction::_doTick( const BevInputParam &input, BevOutputParam &output )
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


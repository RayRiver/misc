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

// �ߵ�doTick��ʾ���뿪ʼִ��
BevRunningStatus BevNodeAction::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	// ��ʼִ�У�����enter����
	if (!m_isRunning)
	{
		onEnter(input);
		m_isRunning = true;
	}

	BevRunningStatus running_state = onExecute(input, output);	
	if (running_state == BevRunningStatus::Executing)
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


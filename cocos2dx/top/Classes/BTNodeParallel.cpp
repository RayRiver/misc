// ���ƽڵ� BTNodeParallel
// ���нڵ�
// evaluate: ���ε������е��ӽڵ��Evaluate�����������е��ӽڵ㶼����True��������Ҳ����True�����򣬷���False
// update: ���������ӽڵ��Tick�����������нڵ��ǡ����ߡ��Ĺ�ϵ����ֻҪ��һ���ӽڵ㷵�����н�����������ͷ������н����������нڵ��ǡ����ҡ��Ĺ�ϵ����ֻ�����е��ӽڵ㷵�ؽ���������ŷ������н���

#include "BTNodeParallel.h"

BTNodeParallel::BTNodeParallel( BTNode *parent, BTPrecondition *precondition /*= nullptr*/ )
	: BTNode(parent, precondition)
{

}

bool BTNodeParallel::onInternalEvaluate( const BTInputParam &input )
{
	return true;
}

void BTNodeParallel::onTransition( const BTInputParam &input )
{

}

BTRunningStatus BTNodeParallel::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	return BTRunningStatus::Finish;
}


// ���ƽڵ� BevNodeParallel
// ���нڵ�
// evaluate: ���ε������е��ӽڵ��Evaluate�����������е��ӽڵ㶼����True��������Ҳ����True�����򣬷���False
// update: ���������ӽڵ��Tick�����������нڵ��ǡ����ߡ��Ĺ�ϵ����ֻҪ��һ���ӽڵ㷵�����н�����������ͷ������н����������нڵ��ǡ����ҡ��Ĺ�ϵ����ֻ�����е��ӽڵ㷵�ؽ���������ŷ������н���

#include "BevNodeParallel.h"

BevNodeParallel::BevNodeParallel( BevNode *parent, BevPrecondition *precondition /*= nullptr*/ )
	: BevNode(parent, precondition)
{

}

bool BevNodeParallel::onInternalEvaluate( const BevInputParam &input )
{
	return true;
}

void BevNodeParallel::onTransition( const BevInputParam &input )
{

}

BevRunningStatus BevNodeParallel::onUpdate( const BevInputParam &input, BevOutputParam &output )
{
	return BevRunningStatus::Finish;
}


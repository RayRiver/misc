// 控制节点 BevNodeParallel
// 并行节点
// evaluate: 依次调用所有的子节点的Evaluate方法，若所有的子节点都返回True，则自身也返回True，否则，返回False
// update: 调用所有子节点的Tick方法，若并行节点是“或者”的关系，则只要有一个子节点返回运行结束，那自身就返回运行结束。若并行节点是“并且”的关系，则只有所有的子节点返回结束，自身才返回运行结束

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


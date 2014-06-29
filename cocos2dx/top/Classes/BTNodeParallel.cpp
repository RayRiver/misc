// 控制节点 BTNodeParallel
// 并行节点
// evaluate: 依次调用所有的子节点的Evaluate方法，若所有的子节点都返回True，则自身也返回True，否则，返回False
// update: 调用所有子节点的Tick方法，若并行节点是“或者”的关系，则只要有一个子节点返回运行结束，那自身就返回运行结束。若并行节点是“并且”的关系，则只有所有的子节点返回结束，自身才返回运行结束

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


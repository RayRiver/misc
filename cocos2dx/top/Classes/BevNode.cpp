#include "BevNode.h"

#include "BevDef.h"
#include "BevPrecondition.h"

using namespace std;

BevNode::BevNode(BevNode *parent, BevPrecondition *precondition/* = nullptr*/)
	: m_precondition(precondition)
{

}

BevNode::~BevNode()
{
	for (auto child : m_childrenList)
	{
		delete child;
	}
	m_childrenList.clear();

	if (m_precondition)
	{
		delete m_precondition;
		m_precondition = nullptr;
	}
}

BevNode & BevNode::addChild( BevNode *child )
{
	m_childrenList.push_back(child);
	return *this;
}

BevNode & BevNode::setPrecondition( BevPrecondition *precondition )
{
	if (m_precondition != precondition)
	{
		if (m_precondition)
		{
			delete m_precondition;
		}
		m_precondition = precondition;
	}
	return *this;
}

bool BevNode::_doInternalEvaluate( const BevInputParam &input )
{
	return true;
}

void BevNode::_doTransition( const BevInputParam &input )
{

}

BevRunningStatus BevNode::_doTick( const BevInputParam &input, BevOutputParam &output )
{
	return BevRunningStatus::Finish;
}



#include "BTNode.h"

#include "BTDef.h"
#include "BTPrecondition.h"

using namespace std;

BTNode::BTNode(BTNode *parent, BTPrecondition *precondition/* = nullptr*/)
	: m_precondition(precondition)
{

}

BTNode::~BTNode()
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

BTNode & BTNode::addChild( BTNode *child )
{
	m_childrenList.push_back(child);
	return *this;
}

BTNode & BTNode::setPrecondition( BTPrecondition *precondition )
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

bool BTNode::onInternalEvaluate( const BTInputParam &input )
{
	return true;
}

void BTNode::onTransition( const BTInputParam &input )
{

}

BTRunningStatus BTNode::onUpdate( const BTInputParam &input, BTOutputParam &output )
{
	return BTRunningStatus::Finish;
}



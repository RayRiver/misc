#include "BTNode.h"

#include "BTDef.h"
#include "BTPrecondition.h"

using namespace std;

BTNode::BTNode(BTPrecondition *precondition/* = nullptr*/)
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

BTNode * BTNode::addChild( const char *name, BTNode *child )
{
	m_childrenList.push_back(child);
	if (name)
	{
		child->setName(name);
	}
	return this;
}

BTNode * BTNode::addChild(BTNode *child)
{
	m_childrenList.push_back(child);
	return this;
}

BTNode & BTNode::setPrecondition( BTPrecondition *precondition, const char *desc /*= nullptr*/ )
{
	if (m_precondition != precondition)
	{
		if (m_precondition)
		{
			delete m_precondition;
		}
		m_precondition = precondition;
		if (desc)
		{
			m_preconditionDesc = desc;
		}
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



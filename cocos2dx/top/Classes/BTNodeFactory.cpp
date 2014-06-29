#include "BTNodeFactory.h"

#include "BTNode.h"
#include "BTNodeAction.h"
#include "BTNodePrioritySelector.h"
#include "BTNodeNonePrioritySelector.h"
#include "BTNodeSequence.h"
#include "BTNodeLoop.h"
#include "BTNodeParallel.h"

void BTNodeFactory::_createNode( BTNode *me, BTNode *parent, const char *name /*= nullptr*/ )
{
	if (parent)
	{
		parent->addChild(me);
	}
	if (name)
	{
		me->setName(name);
	}
}

BTNode & BTNodeFactory::createPrioritySelectorNode( BTNode *parent, const char *name /*= nullptr*/ )
{
	BTNode *node = new BTNodePrioritySelector(parent);
	BTNodeFactory::_createNode(node, parent, name);
	return *node;
}

BTNode & BTNodeFactory::createNonePrioritySelectorNode( BTNode *parent, const char *name /*= nullptr*/ )
{
	BTNode *node = new BTNodeNonePrioritySelector(parent);
	BTNodeFactory::_createNode(node, parent, name);
	return *node;
}

BTNode & BTNodeFactory::createSequenceNode( BTNode *parent, const char *name /*= nullptr*/ )
{
	BTNode *node = new BTNodeSequence(parent);
	BTNodeFactory::_createNode(node, parent, name);
	return *node;
}

BTNode & BTNodeFactory::createLoopNode( BTNode *parent, const char *name /*= nullptr*/ )
{
	BTNode *node = new BTNodeLoop(parent);
	BTNodeFactory::_createNode(node, parent, name);
	return *node;
}

BTNode & BTNodeFactory::createParallelNode( BTNode *parent, const char *name /*= nullptr*/ )
{
	BTNode *node = new BTNodeParallel(parent);
	BTNodeFactory::_createNode(node, parent, name);
	return *node;
}


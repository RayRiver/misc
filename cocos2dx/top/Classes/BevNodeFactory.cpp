#include "BevNodeFactory.h"

#include "BevNode.h"
#include "BevNodeAction.h"
#include "BevNodePrioritySelector.h"
#include "BevNodeNonePrioritySelector.h"
#include "BevNodeSequence.h"
#include "BevNodeLoop.h"
#include "BevNodeParallel.h"

void BevNodeFactory::_createNode( BevNode *me, BevNode *parent, const char *name /*= nullptr*/ )
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

BevNode & BevNodeFactory::createPrioritySelectorNode( BevNode *parent, const char *name /*= nullptr*/ )
{
	BevNode *node = new BevNodePrioritySelector(parent);
	BevNodeFactory::_createNode(node, parent, name);
	return *node;
}

BevNode & BevNodeFactory::createNonePrioritySelectorNode( BevNode *parent, const char *name /*= nullptr*/ )
{
	BevNode *node = new BevNodeNonePrioritySelector(parent);
	BevNodeFactory::_createNode(node, parent, name);
	return *node;
}

BevNode & BevNodeFactory::createSequenceNode( BevNode *parent, const char *name /*= nullptr*/ )
{
	BevNode *node = new BevNodeSequence(parent);
	BevNodeFactory::_createNode(node, parent, name);
	return *node;
}

BevNode & BevNodeFactory::createLoopNode( BevNode *parent, const char *name /*= nullptr*/ )
{
	BevNode *node = new BevNodeLoop(parent);
	BevNodeFactory::_createNode(node, parent, name);
	return *node;
}

BevNode & BevNodeFactory::createParallelNode( BevNode *parent, const char *name /*= nullptr*/ )
{
	BevNode *node = new BevNodeParallel(parent);
	BevNodeFactory::_createNode(node, parent, name);
	return *node;
}


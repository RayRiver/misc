#include "BevNodeFactory.h"

#include "BevNode.h"
#include "BevNodeAction.h"
#include "BevNodePrioritySelector.h"

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
	BevNodePrioritySelector *node = new BevNodePrioritySelector(parent);
	BevNodeFactory::_createNode(node, parent, name);
	return *node;
}

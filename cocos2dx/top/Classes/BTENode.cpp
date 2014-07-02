#include "BTENode.h"

USING_NS_CC;

BTENode * BTENode::create( const std::string& filename )
{
	BTENode *ret = new BTENode();
	if (ret && ret->initWithFile(filename))
	{
		ret->autorelease();
	}
	else
	{
		delete ret;
		ret = nullptr;
	}
	return ret;
}

bool BTENode::initWithFile( const std::string& filename )
{
	if (!BTEResponder::initWithFile(filename))
	{
		return false;
	}

	return true;
}

void BTENode::onActivate()
{

}

void BTENode::onInactivate()
{

}

void BTENode::onAction( const Vec2 &last, const Vec2 &current )
{
	this->setPosition(this->getPosition() + current - last);
}




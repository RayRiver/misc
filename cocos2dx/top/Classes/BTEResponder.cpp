#include "BTEResponder.h"

USING_NS_CC;

BTEResponder * BTEResponder::create( const std::string& filename )
{
	BTEResponder *ret = new BTEResponder();
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

bool BTEResponder::initWithFile( const std::string& filename )
{
	if (!Sprite::initWithFile(filename))
	{
		return false;
	}

	return true;
}

void BTEResponder::onActivate()
{

}

void BTEResponder::onInactivate()
{

}

void BTEResponder::onAction( const Vec2 &last, const Vec2 &current )
{

}


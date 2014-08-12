#include "MineObject.h"

#include "MineView.h"

MineObject *MineObject::create( MineView *view )
{
	auto obj = new MineObject;
	if (obj && obj->init(view))
	{

	}
	else
	{
		delete obj;
		obj = nullptr;
	}
	return obj;
}

MineObject::MineObject()
	: m_view(nullptr)
{

}

MineObject::~MineObject()
{

}

bool MineObject::init( MineView *view )
{
	m_view = view;

	return true;
}

void MineObject::setFixedPosition( const FixedVec2 &p )
{
	m_fixedPosition = p;

	if (m_view)
	{
		m_view->updatePosition(p);
	}
}



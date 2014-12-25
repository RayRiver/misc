#include "Com.h"

NS_GX_BEGIN

Com * GX::Com::create(const std::string &type)
{
	auto com = new Com(type);
	return com;
}

Com::Com(const std::string &type)
	: m_type(type)
{

}

Com::~Com()
{

}

Com * Com::cloneEmpty() const
{

}

NS_GX_END

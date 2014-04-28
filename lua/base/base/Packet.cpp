#include "Packet.h"

#include "NetImp.h"

Packet::Packet()
{

}

Packet::~Packet()
{

}

void Packet::addId( LUA_NUMBER val )
{
	m_args.add((int32_t)val);
}

void Packet::addInt8( LUA_NUMBER val )
{
	m_args.add((int8_t)Var::BYTE);
	m_args.add((int8_t)val);
}

void Packet::addInt16( LUA_NUMBER val )
{
	m_args.add((int8_t)Var::SHORT);
	m_args.add((int16_t)val);
}

void Packet::addInt32( LUA_NUMBER val )
{
	m_args.add((int8_t)Var::INT);
	m_args.add((int32_t)val);
}

void Packet::addInt64( LUA_NUMBER val )
{
	m_args.add((int8_t)Var::INT64);
	m_args.add((int64_t)val);
}

void Packet::addFloat( LUA_NUMBER val )
{
	m_args.add((int8_t)Var::FLOAT);
	m_args.add((float)val);
}

void Packet::addDouble( LUA_NUMBER val )
{
	m_args.add((int8_t)Var::NUMBER);
	m_args.add((double)val);
}

void Packet::addString( const char *val )
{
	m_args.add((int8_t)Var::STRING);
	m_args.add((int32_t)strlen(val));
	m_args.add((const char *)val);
}

void Packet::send()
{
	GetNetImp()->writePack(m_args);
}

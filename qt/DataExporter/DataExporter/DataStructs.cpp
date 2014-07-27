#include "DataStructs.h"

DataTable::DataTable( const QString & name )
	: m_name(name)
{

}

DataTable::~DataTable()
{

}

const QString & DataTable::getName()
{
	return m_name;
}

void DataTable::setHeader( const QStringList &names )
{
	m_header = names;
}

void DataTable::addRecord( const QVariantList &record )
{
	m_records.append(record);
}

void DataTable::setKeys( const QList<int> &keys )
{
	m_keys = keys;
}


DataSheet::DataSheet( const QString & name )
	: m_name(name)
{

}

DataSheet::~DataSheet()
{
	for (auto it=m_tables.begin(); it!=m_tables.end(); ++it)
	{
		auto table = *it;
		delete table;
	}
	m_tables.clear();
}

const QString & DataSheet::getName()
{
	return m_name;
}

void DataSheet::addTable( DataTable *table )
{
	m_tables.push_back(table);
}

const QList<DataTable *> DataSheet::getTables()
{
	return m_tables;
}


DataFile::DataFile( const QString & name )
	: m_name(name)
{

}

DataFile::~DataFile()
{
	for (auto it=m_sheets.begin(); it!=m_sheets.end(); ++it)
	{
		auto sheet = *it;
		delete sheet;
	}
	m_sheets.clear();
}

const QString & DataFile::getName()
{
	return m_name;
}

void DataFile::addSheet( DataSheet *sheet )
{
	m_sheets.push_back(sheet);
}

const QList<DataSheet *> DataFile::getSheets()
{
	return m_sheets;
}


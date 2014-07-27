#ifndef DataStructs_h__
#define DataStructs_h__

#include <QString>
#include <QVariant>

class DataTable
{
public:
	DataTable(const QString &name);
	~DataTable(); 

	const QString &getName();

	void setHeader(const QStringList &names);
	void setKeys(const QList<int> &keys);
	void addRecord(const QVariantList &record);

	const QStringList &getHeader() { return m_header; }
	const QList<int> &getKeys() { return m_keys; }
	const QList<QVariantList> &getRecords() { return m_records; }

private:
	QString m_name;
	QStringList m_header;
	QList<int> m_keys;
	QList<QVariantList> m_records;
};

class DataSheet
{
public:
	DataSheet(const QString &name);
	~DataSheet();

	const QString &getName();

	void addTable(DataTable *table);
	const QList<DataTable *> getTables();

private:
	QString m_name;
	QList<DataTable *> m_tables;
};

class DataFile
{
public:
	DataFile(const QString &name);
	~DataFile();

	const QString &getName();

	void addSheet(DataSheet *sheet);
	const QList<DataSheet *> getSheets();

private:
	QString m_name;
	QList<DataSheet *> m_sheets;
};

#endif // DataStructs_h__

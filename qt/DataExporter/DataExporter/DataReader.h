#ifndef DATAREADER_H
#define DATAREADER_H

#include <QObject>
#include <QStringList>

class DataFile;
class DataTable;
namespace QXlsx {
class Worksheet;
}

class DataReader
{
public:
	static DataReader *instance();
	~DataReader();

	DataFile *loadData(const QString &filename);

	bool exportData(DataTable *dataTable, const QString &path);

private:
	DataReader();
	static DataReader *s_instance;

	DataTable *parseTable(QXlsx::Worksheet *sheet, int row, int col);
	DataTable *parseLocale(QXlsx::Worksheet *sheet, int row, int col);
	
	bool exportLua(DataTable *dataTable, const QString &path);
	bool exportXml(DataTable *dataTable, const QString &path);
	bool exportLocale(DataTable *dataTable, const QString &path);
};

#endif // DATAREADER_H

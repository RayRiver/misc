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

	bool exportLua(DataTable *dataTable, const QString &path);
	bool exportXml(DataTable *dataTable, const QString &path);

private:
	DataReader();
	static DataReader *s_instance;

	DataTable *parseTable(QXlsx::Worksheet *sheet, int row, int col);
	
};

#endif // DATAREADER_H

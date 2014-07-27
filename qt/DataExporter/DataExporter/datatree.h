#ifndef DATATREE_H
#define DATATREE_H

#include <QTreeWidget>
#include "ui_datatree.h"

class DataFile;
class DataTable;

class DataTree : public QTreeWidget
{
	Q_OBJECT

public:
	DataTree(QWidget *parent = 0);
	~DataTree();

	void clearData();
	bool loadData(const QString &filename);
	bool exportData();

	QTreeWidgetItem *addFile(const QString &filename);
	QTreeWidgetItem *addSheet(QTreeWidgetItem *fileItem, const QString &sheetname);
	QTreeWidgetItem *addTable(QTreeWidgetItem *sheetItem, const QString &tablename);

private:
	Ui::DataTree ui;
	DataFile *m_dataFile;

	struct DataTableInfo
	{
		DataFile *dataFile;
		DataTable *dataTable;
	};
	QMap<QTreeWidgetItem *, DataTableInfo> m_dataTableMap;
};

#endif // DATATREE_H

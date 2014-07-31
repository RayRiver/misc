#include "datatree.h"

#include <QFileInfo>

#include "DataStructs.h"
#include "DataReader.h"

DataTree::DataTree(QWidget *parent)
	: QTreeWidget(parent)
	, m_dataFile(nullptr)
{
	ui.setupUi(this);
}

DataTree::~DataTree()
{
	clearData();
}

QTreeWidgetItem * DataTree::addFile( const QString &filename )
{
	QStringList content;
	content << filename;
	auto item = new QTreeWidgetItem(this, content);
	//item->setCheckState(0, Qt::CheckState::Unchecked);
	item->setExpanded(true);
	item->setBackgroundColor(0, QColor(230, 230, 230));
	return item;
}

QTreeWidgetItem * DataTree::addSheet( QTreeWidgetItem *fileItem, const QString &sheetname )
{
	QStringList content;
	content << sheetname;
	auto item = new QTreeWidgetItem(fileItem, content);
	//item->setCheckState(0, Qt::CheckState::Unchecked);
	item->setExpanded(true);
	return item;
}

QTreeWidgetItem * DataTree::addTable( QTreeWidgetItem *sheetItem, const QString &tablename )
{
	QStringList content;
	content << tablename;
	auto item = new QTreeWidgetItem(sheetItem, content);
	item->setCheckState(0, Qt::CheckState::Unchecked);
	return item;
}

void DataTree::clearData()
{
	if (m_dataFile)
	{
		delete m_dataFile;
		m_dataFile = nullptr;
	}
	this->clear();
	this->m_dataTableMap.clear();
}

bool DataTree::loadData( const QString &filename )
{
	m_dataFile = DataReader::instance()->loadData(filename);
	if (!m_dataFile)
	{
		return false;
	}

	auto dataFile = m_dataFile;

	// 根据数据文件显示;
	if (dataFile)
	{
		auto fileItem = this->addFile(dataFile->getName());

		auto sheets = dataFile->getSheets();
		for (auto it=sheets.begin(); it!=sheets.end(); ++it)
		{
			auto dataSheet = *it;
			auto sheetItem = this->addSheet(fileItem, dataSheet->getName());

			auto tables = dataSheet->getTables();
			for (auto itTables=tables.begin(); itTables!=tables.end(); ++itTables)
			{
				auto dataTable = *itTables;
				auto tableItem = this->addTable(sheetItem, dataTable->getName());

				// 记录关联;
				DataTableInfo info;
				info.dataFile = dataFile;
				info.dataTable = dataTable;
				m_dataTableMap.insert(tableItem, info);
			}
		}
	}

	return true;
}

bool DataTree::exportData(const QString &exportPath)
{
	for (auto it=m_dataTableMap.begin(); it!=m_dataTableMap.end(); ++it)
	{
		auto item = it.key();
		if (item->checkState(0) == Qt::CheckState::Checked)
		{
			auto &dataTableInfo = it.value();
			auto dataFile = dataTableInfo.dataFile;
			auto dataTable = dataTableInfo.dataTable;

			// 获取导出文件路径;			
			//auto filepath = dataFile->getName();
			//QFileInfo &fileInfo = QFileInfo(filepath);
			//filepath = fileInfo.absolutePath();
			auto &filepath = exportPath;

			DataReader::instance()->exportData(dataTable, filepath);

		}
	}

	return true;
}

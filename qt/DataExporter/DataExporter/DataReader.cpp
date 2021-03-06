#include "datareader.h"

#include <QDebug>
#include <QObject>
#include <QFile>
#include <QTextCodec>
#include <QDir>

#include "xlsxdocument.h"
QTXLSX_USE_NAMESPACE;

#include "DataStructs.h"

DataReader * DataReader::s_instance = nullptr;

DataReader * DataReader::instance()
{
	if (!s_instance)
	{
		s_instance = new DataReader;
	}
	return s_instance;
}

DataReader::DataReader()
{

}

DataReader::~DataReader()
{

}

DataFile * DataReader::loadData( const QString &filename )
{
	Document doc(filename);

	DataFile *dataFile = nullptr;

	// 遍历所有sheet;
	auto names = doc.sheetNames();
	for (auto it=names.begin(); it!=names.end(); ++it)
	{
		// 获取sheet;
		const auto &sheetName = *it;
		doc.selectSheet(sheetName);
		Worksheet *sheet = doc.currentWorksheet();

		// 行列范围;
		auto range = sheet->dimension();

		DataSheet *dataSheet = nullptr;

		// 遍历所有cell;
		for (int row=range.firstRow(); row<=range.lastRow(); ++row)
		{
			for (int col=range.firstColumn(); col<=range.lastColumn(); ++col)
			{
				auto cell = sheet->cellAt(row, col);
				if (!cell) continue;

				// 检查表头;
				auto &val = cell->value();
				if (val.type() == QVariant::String)
				{
					const auto &s = val.toString();
					if (sheetName.compare("LOCALE", Qt::CaseSensitivity::CaseInsensitive) == 0 &&
						s.compare("LOCALE", Qt::CaseSensitivity::CaseInsensitive) == 0)
					{
						auto table = this->parseLocale(sheet, row, col);
						if (table)
						{
							if (!dataSheet)
							{
								dataSheet = new DataSheet(sheetName);
							}

							dataSheet->addTable(table);
						}	
					}
					else if (s.length() >=2 && s[0] == QChar('#') && s[1] == QChar('^'))
					{
						// 普通数据表;
						qDebug() << QObject::tr("find table at ") << row << QObject::tr(", ") << col;
						auto table = this->parseTable(sheet, row, col);
						if (table)
						{
							if (!dataSheet)
							{
								dataSheet = new DataSheet(sheetName);
							}

							dataSheet->addTable(table);
						}
					}
				}
			}
		}

		// 如果该sheet中有表的话;
		if (dataSheet)
		{
			if (!dataFile)
			{
				dataFile = new DataFile(filename);
			}

			dataFile->addSheet(dataSheet);
		}
	}

	return dataFile;
}

DataTable *DataReader::parseTable( Worksheet *sheet, int tableRow, int tableCol )
{
	// 解析表名;
	auto tableCell = sheet->cellAt(tableRow, tableCol);
	if (!tableCell) 
	{
		return nullptr;
	}
	auto tableName = tableCell->value().toString();
	tableName = tableName.mid(2);

	auto dataTable = new DataTable(tableName);

	// 有效列;
	QList<int> cols;

	// 键列;
	QList<int> keys;

	// 有效列名;
	QStringList names;

	// 行列范围;
	auto range = sheet->dimension();

	// 解析表头;
	for (int col=tableCol+1; col<=range.lastColumn(); ++col)
	{
		auto cell = sheet->cellAt(tableRow, col);
		if (!cell) continue;

		auto &val = cell->value();
		if (val.type() == QVariant::String)
		{
			const auto &s = val.toString();

			// 检测是否结束;
			if (s.length() >=2 && s[0] == QChar('#') && s[1] == QChar('$'))
			{
				break;
			}
			// 检测是否为有效列;
			else if (s.length() >= 1 && s[0] == QChar('#'))
			{
				auto colIndex = cols.size();
				cols.append(col);

				// 解析列名;
				if (s.length() >= 2 && s[1] == QChar('*'))
				{
					auto &colName = s.mid(2);
					names.push_back(colName);
					keys.push_back(colIndex);
				}
				else
				{
					names.push_back(s.mid(1));
				}

			}
		}
	}

	// 设置表头;
	dataTable->setHeader(names);
	dataTable->setKeys(keys);

	// 解析表记录;
	for (int row=tableRow+1; row<=range.lastRow(); ++row)
	{
		auto cell = sheet->cellAt(row, tableCol);
		if (!cell) continue;

		auto &val = cell->value();
		if (val.type() == QVariant::String)
		{
			const auto &s = val.toString();

			// 检测是否结束;
			if (s.length() >=2 && s[0] == QChar('#') && s[1] == QChar('$'))
			{
				break;
			}
			// 检测是否为有效行;
			else if (s.length() >= 1 && s[0] == QChar('#'))
			{
				// 根据有效列解析数据;
				QVariantList vars;
				for (auto it=cols.begin(); it!=cols.end(); ++it)
				{
					auto col = *it;

					auto dataCell = sheet->cellAt(row, col);
					if (!dataCell) 
					{
						// 数据为空，填入默认值;
						vars.push_back(QVariant());
					}
					else
					{
						vars.push_back(dataCell->value());
					}
				}

				// 加入数据表格;
				dataTable->addRecord(vars);
			}
		}
	}

	return dataTable;
}

DataTable *DataReader::parseLocale( QXlsx::Worksheet *sheet, int tableRow, int tableCol )
{
	auto dataTable = new DataTable("LOCALE");

	// 有效列;
	QList<int> cols;

	// 有效列名;
	QStringList names;

	// 行列范围;
	auto range = sheet->dimension();

	// 解析表头;
	for (int col=tableCol; col<=range.lastColumn(); ++col)
	{
		auto cell = sheet->cellAt(tableRow, col);
		if (!cell) continue;

		auto &val = cell->value();
		if (val.type() == QVariant::String)
		{
			const auto &s = val.toString();

			// 有效列;
			if (!s.isEmpty())
			{
				// 解析列名;
				auto &colName = s;
				names.push_back(colName);
				cols.push_back(col);
			}
		}
	}

	// 设置表头;
	dataTable->setHeader(names);

	// 解析表记录;
	for (int row=tableRow+1; row<=range.lastRow(); ++row)
	{
		auto cell = sheet->cellAt(row, tableCol);
		if (!cell) continue;

		auto &val = cell->value();
		if (val.type() == QVariant::String)
		{
			const auto &s = val.toString();

			// 有效行;
			if (!s.isEmpty())
			{
				// 根据有效列解析数据;
				QVariantList vars;
				for (auto it=cols.begin(); it!=cols.end(); ++it)
				{
					auto col = *it;

					auto dataCell = sheet->cellAt(row, col);
					if (!dataCell) 
					{
						// 数据为空，填入默认值;
						vars.push_back(QString());
					}
					else
					{
						vars.push_back(dataCell->value().toString());
					}
				}

				// 加入数据表格;
				dataTable->addRecord(vars);
			}
		}
	}

	return dataTable;
}

bool DataReader::exportLua( DataTable *dataTable, const QString &path )
{
	const QString &name = dataTable->getName();
	const QStringList &header = dataTable->getHeader();
	const QList<int> &keys = dataTable->getKeys();
	const QList<QVariantList> &records = dataTable->getRecords();

	// 创建目录;
	QString dir_path = path + QObject::tr("/lua");
	QDir dir;
	bool exist = dir.exists(dir_path);
	if (!exist)
	{
		bool ok = dir.mkdir(dir_path);
		if (!ok)
		{
			return false;
		}
	}

	auto filename = dir_path + QObject::tr("/") + name.toLower() + QObject::tr(".lua");

	QString content;

	// lua头;
	content.append("-- WARNNING:\n");
	content.append("-- This lua file is generated by DataExporter.\n");
	content.append("-- Please don't modify manually.\n\n");
	content.append("return\n{\n");

	// 键列表;
	content.append("    _keys =\n    {\n");
	for (auto it=keys.begin(); it!=keys.end(); ++it)
	{
		auto keyIndex = *it;
		const auto &keyName = header[keyIndex];

		content.append("        \"");
		content.append(keyName);
		content.append("\",\n");
	}
	content.append("    },\n\n");

	// 映射表;
	content.append("    _map =\n    {\n");
	if (keys.size() == 0)
	{

	}
	else if (keys.size() == 1)
	{
		auto keyIndex = keys[0];

		// 解析到map中;
		QMap<QString, int> map;
		int dataIndex = 1;
		for (auto it=records.begin(); it!=records.end(); ++it, ++dataIndex)
		{
			const auto &record = *it;
			auto key = record[keyIndex].toString();
			map[key] = dataIndex;
		}

		// 输出内容;
		for (auto it=map.begin(); it!=map.end(); ++it)
		{
			const auto &key = it.key();
			auto dataIndex = it.value();
			content.append("        [\"");
			content.append(key);
			content.append("\"] = ");
			content.append(QString::number(dataIndex));
			content.append(",\n");
		}
	}
	else if (keys.size() == 2)
	{
		auto keyIndex1 = keys[0];
		auto keyIndex2 = keys[1];

		// 解析到map中;
		QMap<QString, QMap<QString, int> > map;
		int dataIndex = 1;
		for (auto it=records.begin(); it!=records.end(); ++it, ++dataIndex)
		{
			const auto &record = *it;
			auto key1 = record[keyIndex1].toString();
			auto key2 = record[keyIndex2].toString();

			auto itFind = map.find(key1);
			if (itFind == map.end())
			{
				map[key1] = QMap<QString, int>();
			}

			map[key1][key2] = dataIndex;
		}

		// 输出内容;
		for (auto it=map.begin(); it!=map.end(); ++it)
		{
			const auto &key1 = it.key();
			const auto &map1 = it.value();

			content.append("        [\"");
			content.append(key1);
			content.append("\"] = {\n");
			for (auto it2=map1.begin(); it2!=map1.end(); ++it2)
			{
				const auto &key2 = it2.key();
				auto dataIndex = it2.value();
				content.append("            [\"");
				content.append(key2);
				content.append("\"] = ");
				content.append(QString::number(dataIndex));
				content.append(",\n");
			}
			content.append("        },\n");
		}
	}
	else if (keys.size() == 3)
	{
		auto keyIndex1 = keys[0];
		auto keyIndex2 = keys[1];
		auto keyIndex3 = keys[2];

		// 解析到map中;
		QMap<QString, QMap<QString, QMap<QString, int> > > map;
		int dataIndex = 1;
		for (auto it=records.begin(); it!=records.end(); ++it, ++dataIndex)
		{
			const auto &record = *it;
			auto key1 = record[keyIndex1].toString();
			auto key2 = record[keyIndex2].toString();
			auto key3 = record[keyIndex3].toString();

			auto itFind = map.find(key1);
			if (itFind == map.end())
			{
				map[key1] = QMap<QString, QMap<QString, int> >();
			}

			auto itFind2 = map[key1].find(key2);
			if (itFind2 == map[key1].end())
			{
				map[key1][key2] = QMap<QString, int>();
			}

			map[key1][key2][key3] = dataIndex;
		}

		// 输出内容;
		for (auto it=map.begin(); it!=map.end(); ++it)
		{
			const auto &key1 = it.key();
			const auto &map1 = it.value();

			content.append("        [\"");
			content.append(key1);
			content.append("\"] = {\n");
			for (auto it2=map1.begin(); it2!=map1.end(); ++it2)
			{
				const auto &key2 = it2.key();
				const auto &map2 = it2.value();
				content.append("            [\"");
				content.append(key2);
				content.append("\"] = {\n");
				for (auto it3=map2.begin(); it3!=map2.end(); ++it3)
				{
					const auto &key3 = it3.key();
					auto dataIndex = it3.value();
					content.append("                [\"");
					content.append(key3);
					content.append("\"] = ");
					content.append(QString::number(dataIndex));
					content.append(",\n");
				}
				content.append("            },\n");
			}
			content.append("        },\n");
		}
	}
	else
	{
		// 目前只支持最多3个key;
		Q_ASSERT(false);
	}
	content.append("    },\n\n");


	// 数据;
	content.append("    _data = \n    {\n");
	for (auto it=records.begin(); it!=records.end(); ++it)
	{
		content.append("        {\n");
		const auto &record = *it;
		auto itHeader = header.begin();
		auto itRecord = record.begin();
		for ( ; itHeader!=header.end(); ++itHeader, ++itRecord)
		{
			const auto &colName = *itHeader;
			const auto &colData = *itRecord;

			bool isstring = false;
			if (colData.type() == QVariant::String)
			{
				isstring = true;
			}

			content.append("            [\"");
			content.append(colName);
			content.append("\"] = ");
			if (isstring) content.append("\"");
			content.append(colData.toString());
			if (isstring) content.append("\"");
			content.append(",\n");
		}
		content.append("        },\n");
	}
	content.append("    }\n");

	// lua文件尾;
	content.append("}\n");

	// 输出文件;
	QFile f(filename);
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream output(&f);
		output.setCodec("utf-8");
		output << content << endl;
		f.close();
	}

	return true;
}

bool DataReader::exportXml( DataTable *dataTable, const QString &path )
{
	const QString &name = dataTable->getName();
	const QStringList &header = dataTable->getHeader();
	const QList<QVariantList> &records = dataTable->getRecords();

	// 创建目录;
	QString dir_path = path + QObject::tr("/xml");
	QDir dir;
	bool exist = dir.exists(dir_path);
	if (!exist)
	{
		bool ok = dir.mkdir(dir_path);
		if (!ok)
		{
			return false;
		}
	}

	auto filename = dir_path + QObject::tr("/") + name.toLower() + QObject::tr(".xml");

	QString content;

	// xml头;
	content.append("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n");

	content.append("<");
	content.append(name);
	content.append(" No=\"\" Name=\"\">\n");

	// 数据;
	for (auto it=records.begin(); it!=records.end(); ++it)
	{
		content.append("  <Property ");
		const auto &record = *it;
		auto itHeader = header.begin();
		auto itRecord = record.begin();
		for ( ; itHeader!=header.end(); ++itHeader, ++itRecord)
		{
			const auto &colName = *itHeader;
			const auto &colData = *itRecord;

			content.append(colName);
			content.append("=\"");
			content.append(colData.toString());
			content.append("\" ");
		}
		content.append("/>\n");
	}

	content.append("</");
	content.append(name);
	content.append(">\n");

	// 输出文件;
	QFile f(filename);
	if (f.open(QIODevice::WriteOnly | QIODevice::Text))
	{
		QTextStream output(&f);
		output.setCodec("utf-8");
		output << content << endl;
		f.close();
	}

	return true;
}

bool DataReader::exportLocale( DataTable *dataTable, const QString &path )
{
	const QString &name = dataTable->getName();
	const QStringList &header = dataTable->getHeader();
	const QList<QVariantList> &records = dataTable->getRecords();

	auto locale_path = path + QObject::tr("/locale");

	// 创建locale目录;
	QDir locale_dir;
	bool exist = locale_dir.exists(locale_path);
	if (!exist)
	{
		bool ok = locale_dir.mkdir(locale_path);
		if (!ok)
		{
			return false;
		}
	}

	QStringList origins;

	// 解析不同语言;
	int col = 0;
	for (auto it=header.begin(); it!=header.end(); ++it, ++col) 
	{
		const auto &lang = *it;
		if (lang.isEmpty()) continue;

		// 解析原字符串;
		if (lang.compare("LOCALE", Qt::CaseSensitivity::CaseInsensitive) == 0) 
		{
			for (auto it=records.begin(); it!=records.end(); ++it)
			{
				const auto &val = *it;
				const auto &s = val[col].toString();
				origins.push_back(s);
			}
			continue;
		}

		auto lang_path = locale_path + QObject::tr("/") + lang;

		// 创建语言目录;
		QDir lang_dir;
		bool exist = lang_dir.exists(lang_path);
		if (!exist)
		{
			bool ok = lang_dir.mkdir(lang_path);
			if (!ok)
			{
				return false;
			}
		}

		QString content;

		// json头;
		content.append("{\n");

		// 解析所有字符串;
		int row = 0;
		for (auto it=records.begin(); it!=records.end(); ++it, ++row)
		{
			const auto &record = *it;
			const auto &s = record[col].toString();

			content.append("    \"");
			content.append(origins[row]);
			content.append("\" : \"");
			content.append(s);
			content.append("\",\n");
		}

		// json尾;
		content.append("    \"\" : \"\"\n}\n");

		// 输出文件;
		auto filename = lang_path + QObject::tr("/text.json");
		QFile f(filename);
		if (f.open(QIODevice::WriteOnly | QIODevice::Text))
		{
			QTextStream output(&f);
			output.setCodec("utf-8");
			output << content << endl;
			f.close();
		}
		else
		{
			return false;
		}

	}

	return true;
}

bool DataReader::exportData( DataTable *dataTable, const QString &path )
{
	if (dataTable->getName().compare("LOCALE", Qt::CaseSensitivity::CaseInsensitive) == 0)
	{
		this->exportLocale(dataTable, path);
	}
	else
	{
		this->exportLua(dataTable, path);
		this->exportXml(dataTable, path);
	}

	return true;
}


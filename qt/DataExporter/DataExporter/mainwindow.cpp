#include "mainwindow.h"

#include <QTreeWidget>
#include <QStringList>
#include <QFileInfo>
#include <QPushButton>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTextCodec>
#include <QFileDialog>
#include <QComboBox>
#include <QDebug>
#include <QSettings>

#include "DataReader.h"
#include "helpdialog.h"

#define MIMETYPE "application/x-qt-windows-mime;value=\"FileNameW\""

MainWindow::MainWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	DataTree *tree = this->findChild<DataTree *>(tr("treeWidget"));

	QStringList headers;
	headers << tr("title"); 
	tree->setHeaderLabels(headers);

	tree->setHeaderHidden(true);


	auto exportButton = this->findChild<QPushButton *>(tr("pushButton_exportData"));
	if (exportButton)
	{
		this->connect(exportButton, SIGNAL(clicked()), this, SLOT(onExportData()));
	}

	auto setExportPathButton = this->findChild<QPushButton *>(tr("pushButton_setExportPath"));
	if (setExportPathButton)
	{
		this->connect(setExportPathButton, SIGNAL(clicked()), this, SLOT(onSetExportPath()));
	}

	auto helpButton = this->findChild<QPushButton *>(tr("pushButton_help"));
	if (helpButton)
	{
		this->connect(helpButton, SIGNAL(clicked()), this, SLOT(onHelp()));
	}

	this->setAcceptDrops(true);

	loadOpenedFileList();

	//QString filename = QObject::tr("D:\\dev\\project\\misc\\qt\\DataExporter\\data\\test.xlsx");
	//tree->loadData(filename);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onSetExportPath()
{
	QString startPath;

	// 从当前选中路径开始;
	auto comboBox_exportPaths = this->findChild<QComboBox *>(tr("comboBox_exportPaths"));
	if (comboBox_exportPaths)
	{
		startPath = comboBox_exportPaths->currentText();
		qDebug() << tr("start path: ") << startPath;	
	}
	if (startPath.isEmpty())
	{
		startPath = QDir::currentPath();
	}

	// 打开选择目录对话框;
	QString directory = QFileDialog::getExistingDirectory(this, tr("Find Files"), startPath);

	if (!directory.isEmpty()) 
	{
		// 在combobox中设置选中的文件夹;
		if (comboBox_exportPaths)
		{
			if (comboBox_exportPaths->findText(directory) == -1)
			{
				comboBox_exportPaths->addItem(directory);
			}
			comboBox_exportPaths->setCurrentIndex(comboBox_exportPaths->findText(directory));
		}

		saveOpenedFileList();
	}

}

void MainWindow::onExportData()
{
	// 判断有无导出路径;
	auto comboBox_exportPaths = this->findChild<QComboBox *>(tr("comboBox_exportPaths"));
	const auto &exportPath = comboBox_exportPaths->currentText();
	if (exportPath.isEmpty())
	{
		QMessageBox::information(NULL, "information", "Please set export path first!", QMessageBox::Yes, QMessageBox::Yes);
		return;
	}

	DataTree *tree = this->findChild<DataTree *>(tr("treeWidget"));
	tree->exportData(exportPath);

	QMessageBox::information(NULL, "information", "export done", QMessageBox::Yes, QMessageBox::Yes);
}

void MainWindow::dragEnterEvent( QDragEnterEvent *event )
{
	if (event->mimeData()->hasFormat(MIMETYPE)) 
	{
		event->acceptProposedAction();
	}
}

void MainWindow::dragMoveEvent( QDragMoveEvent *event )
{

}

void MainWindow::dropEvent( QDropEvent *event )
{
	if (!event->mimeData()->hasFormat(MIMETYPE)) 
	{
		return;
	}

	auto &filenameBytes = event->mimeData()->data(MIMETYPE);
	auto &filename = QTextCodec::codecForName("utf-16")->toUnicode(filenameBytes);

	DataTree *tree = this->findChild<DataTree *>(tr("treeWidget"));
	tree->clearData();
	tree->loadData(filename);
}

void MainWindow::loadOpenedFileList()
{
	// 读配置文件;
	QString settingsFileName = QDir::currentPath() + tr("/settings.ini");
	auto &settings = QSettings(settingsFileName, QSettings::IniFormat);

	settings.beginGroup("config");
	const auto &vallist = settings.value(tr("opened_file_list"), QVariantList()).toList();
	const auto &latest_file = settings.value(tr("latest_file"), QString()).toString();
	settings.endGroup();

	// 解析到字符串列表中;
	QStringList filelist;
	for (auto it=vallist.begin(); it!=vallist.end(); ++it)
	{
		const auto &val = *it;
		filelist.push_back(val.toString());
	}

	// 填入comboBox;
	auto comboBox_exportPaths = this->findChild<QComboBox *>(tr("comboBox_exportPaths"));
	if (comboBox_exportPaths)
	{
		comboBox_exportPaths->addItems(filelist);
		comboBox_exportPaths->setCurrentText(latest_file);
	}
}

void MainWindow::saveOpenedFileList()
{
	// 填入comboBox;
	auto comboBox_exportPaths = this->findChild<QComboBox *>(tr("comboBox_exportPaths"));
	if (!comboBox_exportPaths)
	{
		Q_ASSERT(false);
		return;
	}

	QVariantList vallist;
	int count = comboBox_exportPaths->maxVisibleItems();
	for (int i=0; i<count; ++i)
	{
		const auto &s = comboBox_exportPaths->itemText(i);
		const auto &val = QVariant(s);
		vallist.push_back(val);
	}

	QString latest_file = comboBox_exportPaths->currentText();

	// 写配置文件;
	QString settingsFileName = QDir::currentPath() + tr("/settings.ini");
	auto &settings = QSettings(settingsFileName, QSettings::IniFormat);

	settings.beginGroup("config");
	settings.setValue(tr("opened_file_list"), vallist);
	settings.setValue(tr("latest_file"), latest_file);
	settings.endGroup();
}

void MainWindow::onHelp()
{
	auto dialog = new HelpDialog(this);
	dialog->show();
}

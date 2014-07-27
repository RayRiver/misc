#include "mainwindow.h"

#include <QTreeWidget>
#include <QStringList>
#include <QFileInfo>
#include <QPushButton>
#include <QMessageBox>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QTextCodec>

#include "DataReader.h"

#define MIMETYPE "application/x-qt-windows-mime;value=\"FileNameW\""

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
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

	this->setAcceptDrops(true);


	//QString filename = QObject::tr("D:\\dev\\project\\misc\\qt\\DataExporter\\data\\test.xlsx");
	//tree->loadData(filename);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onExportData()
{
	DataTree *tree = this->findChild<DataTree *>(tr("treeWidget"));

	tree->exportData();

	QMessageBox::information(NULL, "Title", "Content", QMessageBox::Yes, QMessageBox::Yes);
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

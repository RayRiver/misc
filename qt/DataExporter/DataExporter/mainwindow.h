#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class QDropEvent;
class QDropEnterEvent;
class QDropMoveEvent;

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onSetExportPath();
	void onExportData();

protected:
	void dragEnterEvent(QDragEnterEvent *event);    
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

	// ���غͱ����Ѵ��ļ��б�;
	void loadOpenedFileList();
	void saveOpenedFileList();

private:
	Ui::Dialog ui;
};

#endif // MAINWINDOW_H

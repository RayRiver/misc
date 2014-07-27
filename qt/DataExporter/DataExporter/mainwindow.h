#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtWidgets/QMainWindow>
#include "ui_mainwindow.h"

class QDropEvent;
class QDropEnterEvent;
class QDropMoveEvent;

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0);
	~MainWindow();

private slots:
	void onExportData();

protected:
	void dragEnterEvent(QDragEnterEvent *event);    
	void dragMoveEvent(QDragMoveEvent *event);
	void dropEvent(QDropEvent *event);

private:
	Ui::MainWindowClass ui;
};

#endif // MAINWINDOW_H

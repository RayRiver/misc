#ifndef HELPDIALOG_H
#define HELPDIALOG_H

#include <QDialog>
#include "ui_helpdialog.h"

class HelpDialog : public QDialog
{
	Q_OBJECT

public:
	HelpDialog(QWidget *parent = 0);
	~HelpDialog();

private:
	Ui::HelpDialog ui;
};

#endif // HELPDIALOG_H

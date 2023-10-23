#pragma once

#include <QDialog>
#include "ui_AboutDlg.h"

class AboutDlg : public QDialog
{
	Q_OBJECT

public:
	AboutDlg(QWidget *parent = nullptr);
	~AboutDlg();

private:
	Ui::AboutDlgClass ui;
};

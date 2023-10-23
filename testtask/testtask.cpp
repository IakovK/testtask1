#include <QMessageBox>

#include "testtask.h"
#include "AboutDlg.h"

testtask::testtask(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    connectActions();
}

testtask::~testtask()
{}

void testtask::connectActions()
{
    connect(ui.actionWave_viewer, &QAction::triggered, this, &testtask::showWaveViewer);
    connect(ui.actionAbout, &QAction::triggered, this, &testtask::showAboutDlg);
}

void testtask::showWaveViewer()
{
    wv.show();
}

void testtask::showAboutDlg()
{
    AboutDlg dlg;
    dlg.exec();
}


#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_testtask.h"
#include "WaveViewer.h"

class testtask : public QMainWindow
{
    Q_OBJECT

public:
    testtask(QWidget *parent = nullptr);
    ~testtask();

private:
    Ui::testtaskClass ui;

    void connectActions();
    void showWaveViewer();
    void showAboutDlg();
    WaveViewer wv;
};

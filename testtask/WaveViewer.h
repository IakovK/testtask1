#pragma once

#include <QWidget>
#include "ui_WaveViewer.h"
#include <QUdpSocket>
#include <QNetworkDatagram>

class WaveViewer : public QWidget
{
	Q_OBJECT

public:
	WaveViewer(QWidget *parent = nullptr);
	~WaveViewer();

private:
	Ui::WaveViewerClass ui;

	bool captureActive{};
	QUdpSocket* socket{};

	void setupControls();
	void connectSignals();
	void startCapture();
	void stopCapture();
	void setupSocket();
	void setupPlot();
	void stopSocket();
	void readyRead();
	void processTheDatagram(QNetworkDatagram datagram);
};

#include "WaveViewer.h"
#include <algorithm>

WaveViewer::WaveViewer(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	setupControls();
	connectSignals();
	setupPlot();
}

WaveViewer::~WaveViewer()
{}

void WaveViewer::setupControls()
{
	if (captureActive)
	{
		ui.stopButton->show();
		ui.startButton->hide();
	}
	else
	{
		ui.stopButton->hide();
		ui.startButton->show();
	}
}

void WaveViewer::connectSignals()
{
	connect(ui.startButton, &QAbstractButton::clicked, this, &WaveViewer::startCapture);
	connect(ui.stopButton, &QAbstractButton::clicked, this, &WaveViewer::stopCapture);
}

void WaveViewer::startCapture()
{
	captureActive = true;
	setupControls();
	setupSocket();
	ui.logLine->setText(QString("capture started"));
}

void WaveViewer::stopCapture()
{
	captureActive = false;
	setupControls();
	stopSocket();
	ui.logLine->setText(QString("capture stopped"));
}

void WaveViewer::setupSocket()
{
	socket = new QUdpSocket(this);
	socket->bind(QHostAddress::LocalHost, 10002);

	connect(socket, &QUdpSocket::readyRead, this, &WaveViewer::readyRead);
}

void WaveViewer::stopSocket()
{
	delete socket;
	socket = nullptr;
}

void WaveViewer::readyRead()
{
	while (socket->hasPendingDatagrams())
	{
		QNetworkDatagram datagram = socket->receiveDatagram();
		processTheDatagram(datagram);
	}
}

template<typename T1, typename T2> void FillArray(QVector<T2>& y, QNetworkDatagram datagram)
{
	auto d = datagram.data();
	auto size = d.size() / sizeof(T1);
	auto dPtr = reinterpret_cast<T1*>(d.data());
	for (int j = 0; j < size; j++)
	{
		y.push_back(qFromBigEndian(dPtr[j]));
	}
}

template<typename T> T findMedian(std::vector<T> &&a)
{
	auto n = a.size();
	if (n % 2 == 0)
	{
		// Applying nth_element 
		// on n/2th index 
		nth_element(a.begin(),
			a.begin() + n / 2,
			a.end());

		// Applying nth_element 
		// on (n-1)/2 th index 
		nth_element(a.begin(),
			a.begin() + (n - 1) / 2,
			a.end());

		// Find the average of value at 
		// index N/2 and (N-1)/2 
		return (T)(a[(n - 1) / 2]
			+ a[n / 2])
			/ 2.0;
	}

	// If size of the arr[] is odd 
	else
	{

		// Applying nth_element 
		// on n/2 
		nth_element(a.begin(),
			a.begin() + n / 2,
			a.end());

		// Value at index (N/2)th 
		// is the median 
		return (T)a[n / 2];
	}
}

void WaveViewer::processTheDatagram(QNetworkDatagram datagram)
{
	QVector<double> x, y, y1;
	FillArray<int16_t>(y, datagram);
	FillArray<int16_t>(y1, datagram);
	for (int i = 0; i < y.size(); ++i)
	{
		x.push_back(i);
	}
	double maxElt = *std::max_element(y.begin(), y.end());
	double minElt = *std::min_element(y.begin(), y.end());
	double median = findMedian<double>(y.toStdVector());

	ui.customPlot->xAxis->setRange(0, x.size());
	ui.customPlot->yAxis->setRange(minElt * 1.1, maxElt * 1.1);
	ui.customPlot->graph(0)->setData(x, y);
	ui.customPlot->replot();

	ui.logLine->setText(QString("max = %1, median = %2").arg(maxElt).arg(median));
}

void WaveViewer::setupPlot()
{
	ui.customPlot->addGraph();
	ui.customPlot->xAxis->setRange(0, 4095);
	ui.customPlot->yAxis->setRange(0, 4095);
	ui.customPlot->replot();
}


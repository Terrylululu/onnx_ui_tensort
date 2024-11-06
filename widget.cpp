#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

	connect(ui->pushButton_onnx2trt, &QPushButton::clicked, this, &Widget::onnx2trt);

	connect(ui->pushButton, &QPushButton::clicked, this, [=]() {


	    onnx_path = QFileDialog::getOpenFileName(this, "open onnx file");
		qDebug() << onnx_path;

		// ʹ�� QFileInfo ��ȡ��Ϣ
		QFileInfo fileInfo(onnx_path);

		// ��ȡ�ļ���׺��
		QString fileExtension = fileInfo.suffix(); // ��ȡ��׺��
		if (fileExtension != QString("onnx"))
		{
			QMessageBox::information(this, "info", "Recheck onnx file path");
			isonnx = false;
		}
		else {
			// ��ȡtrt�ļ�·��
			trt_path = get_trt_file_path(onnx_path);
			qDebug() << trt_path;
			
			isonnx = true;
		}
		
	});



}

Widget::~Widget()
{
    delete ui;
}

void Widget::onnx2trt()
{
	qDebug() << "begin onnx to  trt";
	
	std::string onnxpath = onnx_path.toStdString();

	std::string trtpath = trt_path.toStdString();
	if (isonnx)
	{
		item.onnxToTRTModel(onnxpath, trtpath, 1);
	}
	else
	{
		QMessageBox::information(this, "info", "please to choose onnx file ");

	}
	
}

QString Widget::get_trt_file_path(QString str)
{
	QFileInfo fileInfo(str);

	// ��ȡ�ļ���׺��
	QString fileExtension = fileInfo.suffix(); // ��ȡ��׺��

	// ��ȡ��ǰ�ļ���·��
	QString directoryPath = fileInfo.absolutePath(); // ��ȡ�ļ���·��

	// ��ȡ�ļ���
	QString fileName = fileInfo.fileName().split('.')[0]; // ��ȡ�ļ���

	QString trt_path = directoryPath + "/" + fileName + ".trt";
	return trt_path;
}

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

		// 使用 QFileInfo 提取信息
		QFileInfo fileInfo(onnx_path);

		// 获取文件后缀名
		QString fileExtension = fileInfo.suffix(); // 获取后缀名
		if (fileExtension != QString("onnx"))
		{
			QMessageBox::information(this, "info", "Recheck onnx file path");
			isonnx = false;
		}
		else {
			// 获取trt文件路径
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

	// 获取文件后缀名
	QString fileExtension = fileInfo.suffix(); // 获取后缀名

	// 提取当前文件夹路径
	QString directoryPath = fileInfo.absolutePath(); // 获取文件夹路径

	// 获取文件名
	QString fileName = fileInfo.fileName().split('.')[0]; // 获取文件名

	QString trt_path = directoryPath + "/" + fileName + ".trt";
	return trt_path;
}

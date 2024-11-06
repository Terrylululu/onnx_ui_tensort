#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>
#include"Onnx2Trt.h"
#include <QFileDialog>
#include<QString>
#include<QMessageBox>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
	Onnx2Trt item;
	QString onnx_path;
	QString trt_path;
	QString get_trt_file_path(QString str);
	bool isonnx=false;

private:
    Ui::Widget *ui;
public slots:
    void onnx2trt();

};

#endif // WIDGET_H

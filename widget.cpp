#include "widget.h"
#include "./ui_widget.h"
#include <QFontDatabase>
#include <QDebug>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    QFontDatabase::addApplicationFont(":/new/prefix1/DigitalDisplayRegular-ODEO.ttf");
    QFont digital_font = QFont("Digital Display", 30);
    ui->operationLabel->setFont(digital_font);

}

Widget::~Widget()
{
    delete ui;
}

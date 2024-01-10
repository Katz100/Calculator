#include "widget.h"
#include "./ui_widget.h"
#include <QFontDatabase>
#include <QDebug>
#include "DyArray.h"
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    //Setup digital font
    QFontDatabase::addApplicationFont(":/new/prefix1/PocketCalculator-qjd.ttf");
    QFont digital_font = QFont("Pocket Calculator", 30);
    ui->operationLabel->setFont(digital_font);

    setUpButtons();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::setUpButtons()
{
    connect(ui->zeroButton, &QPushButton::clicked, this, &Widget::zeroButtonClicked);
    connect(ui->oneButton, &QPushButton::clicked, this, &Widget::oneButtonClicked);
    connect(ui->twoButton, &QPushButton::clicked, this, &Widget::twoButtonClicked);
    connect(ui->threeButton, &QPushButton::clicked, this, &Widget::threeButtonClicked);
    connect(ui->fourButton, &QPushButton::clicked, this, &Widget::fourButtonClicked);
    connect(ui->fiveButton, &QPushButton::clicked, this, &Widget::fiveButtonClicked);
    connect(ui->sixButton, &QPushButton::clicked, this, &Widget::sixButtonClicked);
    connect(ui->sevenButton, &QPushButton::clicked, this, &Widget::sevenButtonClicked);
    connect(ui->eightButton, &QPushButton::clicked, this, &Widget::eightButtonClicked);
    connect(ui->nineButton, &QPushButton::clicked, this, &Widget::nineButtonClicked);
    connect(ui->openingparaButton, &QPushButton::clicked, this, &Widget::openingParaClicked);
    connect(ui->closingparaButton, &QPushButton::clicked, this, &Widget::closingParaClicked);
    connect(ui->addButton, &QPushButton::clicked, this, &Widget::addButtonClicked);
    connect(ui->minusButton, &QPushButton::clicked, this, &Widget::minusButtonClicked);
    connect(ui->multButton, &QPushButton::clicked, this, &Widget::multButtonClicked);
    connect(ui->divisionButton, &QPushButton::clicked, this, &Widget::divisionButtonClicked);
    connect(ui->CButton, &QPushButton::clicked, this, &Widget::clearOneButtonClicked);
    connect(ui->CEButton, &QPushButton::clicked, this, &Widget::clearAllButtonClicked);
    connect(ui->dotButton, &QPushButton::clicked, this, &Widget::dotButtonClicked);
    connect(ui->equalButton, &QPushButton::clicked, this, &Widget::equalButtonClicked);


}

//button definitions
void Widget::zeroButtonClicked()
{
    operation += "0";
    ui->operationLabel->setText(operation);
}

void Widget::dotButtonClicked()
{
    if (dotClicked == false)
    {
        operation += ".";
        ui->operationLabel->setText(operation);
        dotClicked = true;
    }
}

void Widget::oneButtonClicked()
{
    operation += "1";
    ui->operationLabel->setText(operation);
}

void Widget::twoButtonClicked()
{
    operation += "2";
    ui->operationLabel->setText(operation);
}

void Widget::threeButtonClicked()
{
    operation += "3";
    ui->operationLabel->setText(operation);
}

void Widget::fourButtonClicked()
{
    operation += "4";
    ui->operationLabel->setText(operation);
}

void Widget::fiveButtonClicked()
{
    operation += "5";
    ui->operationLabel->setText(operation);
}

void Widget::sixButtonClicked()
{
    operation += "6";
    ui->operationLabel->setText(operation);
}

void Widget::sevenButtonClicked()
{
    operation += "7";
    ui->operationLabel->setText(operation);
}

void Widget::eightButtonClicked()
{
    operation += "8";
    ui->operationLabel->setText(operation);
}

void Widget::nineButtonClicked()
{
    operation += "9";
    ui->operationLabel->setText(operation);
}

void Widget::openingParaClicked()
{
    operation += "(";
    ui->operationLabel->setText(operation);
}

void Widget::closingParaClicked()
{
    operation += ")";
    ui->operationLabel->setText(operation);
}

void Widget::addButtonClicked()
{
    operation += "+";
    ui->operationLabel->setText(operation);
    dotClicked = false;
}

void Widget::minusButtonClicked()
{
    operation += "-";
    ui->operationLabel->setText(operation);
    dotClicked = false;

}

void Widget::multButtonClicked()
{
    operation += "*";
    ui->operationLabel->setText(operation);
    dotClicked = false;

}

void Widget::divisionButtonClicked()
{
    operation += "/";
    ui->operationLabel->setText(operation);
    dotClicked = false;

}

void Widget::clearOneButtonClicked()
{
    operation.removeLast();
    ui->operationLabel->setText(operation);
}

void Widget::clearAllButtonClicked()
{
    operation.clear();
    ui->operationLabel->setText(operation);
    dotClicked = false;
}

void Widget::equalButtonClicked()
{


    try {
    double answer = calculate(operation.toStdString());
    operation.clear();
    ui->operationLabel->setText(QString::number(answer));

    } catch (const std::invalid_argument& e) {
        operation.clear();
        ui->operationLabel->setText("Error");
        qDebug() << e.what();
    }

}



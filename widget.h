#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    Ui::Widget *ui;
    QString operation;
    //prevent multiple instances of '.' appearing
    bool dotClicked = false;

    void setUpButtons();

    //button declarations
    void zeroButtonClicked();
    void dotButtonClicked();
    void oneButtonClicked();
    void twoButtonClicked();
    void threeButtonClicked();
    void fourButtonClicked();
    void fiveButtonClicked();
    void sixButtonClicked();
    void sevenButtonClicked();
    void eightButtonClicked();
    void nineButtonClicked();
    void openingParaClicked();
    void closingParaClicked();
    void addButtonClicked();
    void minusButtonClicked();
    void multButtonClicked();
    void divisionButtonClicked();
    void clearOneButtonClicked();
    void clearAllButtonClicked();
    void equalButtonClicked();
    //end button declarations

};
#endif // WIDGET_H

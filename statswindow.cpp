#include "statswindow.h"

SecondWindow::SecondWindow(QWidget *parent) : QWidget(parent)
//  , ui2(new Ui::SecondWindow)
{
//    ui2->setupUi(this);
    setWindowTitle("Second Window");
    resize(400, 300); // Set the size of the second window
}

SecondWindow::~SecondWindow()
{
//    delete ui;
}

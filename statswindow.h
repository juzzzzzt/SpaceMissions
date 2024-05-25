/*#include "statswindow.h"

StatsWindow::StatsWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::StatsWindow)
{
    ui->setupUi(this);

    // Создаем кнопку "Назад"
    QPushButton *backButton = new QPushButton("Назад", this);

    // Устанавливаем кнопку "Назад" в макет
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(backButton);
    setLayout(layout);

    // Подключаем сигнал кнопки "Назад"
    connect(backButton, &QPushButton::clicked, this, &StatsWindow::backButtonClicked);
}

StatsWindow::~StatsWindow()
{
    delete ui;
}*/

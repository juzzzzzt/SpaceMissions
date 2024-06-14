#include "globalstatswindow.h"

GlobalStatsWindow::GlobalStatsWindow(QWidget *parent) : QDialog(parent)
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    statsLabel = new QLabel(this);
    QPixmap pixmap("C:/Users/Аскар/Downloads/oatu.png");
    statsLabel->setPixmap(pixmap);
    statsLabel->setAlignment(Qt::AlignCenter);

    backButton = new QPushButton("Back", this);
    connect(backButton, &QPushButton::clicked, this, &GlobalStatsWindow::on_backButton_clicked);

    layout->addWidget(statsLabel);
    layout->addWidget(backButton);
    setLayout(layout);

    setWindowTitle("Global Stats");
    resize(pixmap.size());

    this->setStyleSheet(
            "QDialog {"
            "    background-color: black;"
            "    color: white;"
            "}"
            "QLabel {"
            "    background-color: black;"
            "    color: white;"
            "}"
            "QPushButton {"
            "    background-color: #333333;"
            "    color: white;"
            "    border: 1px solid gray;"
            "    padding: 5px;"
            "}"
            "QPushButton:hover {"
            "    background-color: #444444;"
            "}"
            "QPushButton:pressed {"
            "    background-color: #555555;"
            "}"
        );
}

GlobalStatsWindow::~GlobalStatsWindow()
{
}

void GlobalStatsWindow::on_backButton_clicked()
{
    this->close();
}

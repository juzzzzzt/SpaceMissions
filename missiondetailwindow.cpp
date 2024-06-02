#include "missiondetailwindow.h"

MissionDetailWindow::MissionDetailWindow(QWidget *parent) :
    QDialog(parent),
    detailsTextEdit(new QTextEdit(this)),
    closeButton(new QPushButton("Close", this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(detailsTextEdit);
    layout->addWidget(closeButton);

    setLayout(layout);
    setWindowTitle("Mission Details");
    resize(600, 450);

    connect(closeButton, &QPushButton::clicked, this, &MissionDetailWindow::close);

    this->setStyleSheet(
        "QDialog {"
        "    background-color: black;"
        "    color: cyan;"
        "    qproperty-alignment: AlignCenter;"
        "}"
        "QTextEdit {"
        "    background-color: black;"
        "    color: cyan;"
        "    border: none;"
        "    padding: 5px;"
        "}"
        "QTextEdit QScrollBar::add-line:vertical {"
        "    background: #444444;"
        "    height: 16px;"
        "    subcontrol-position: bottom;"
        "    subcontrol-origin: margin;"
        "    border: 1px solid gray;"
        "}"
        "QTextEdit QScrollBar::sub-line:vertical {"
        "    background: #444444;"
        "    height: 16px;"
        "    subcontrol-position: top;"
        "    subcontrol-origin: margin;"
        "    border: 1px solid gray;"
        "}"
        "QTextEdit QScrollBar::up-arrow:vertical, QScrollBar::down-arrow:vertical {"
        "    border: 2px solid grey;"
        "    width: 3px;"
        "    height: 3px;"
        "    background: white;"
        "}"
        "QTextEdit QScrollBar::add-page:vertical, QScrollBar::sub-page:vertical {"
        "    background: none;"
        "}"
        "QPushButton {"
        "    background-color: #333333;"
        "    color: white;"
        "    border: none;"
        "    padding: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #444444;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #555555;"
        "}"
    );

    detailsTextEdit->setReadOnly(true);
}

MissionDetailWindow::~MissionDetailWindow()
{
}

void MissionDetailWindow::setMissionDetails(const QString &details)
{
    detailsTextEdit->setPlainText(details);
}

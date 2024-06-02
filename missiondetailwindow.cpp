#include "missiondetailwindow.h"

MissionDetailWindow::MissionDetailWindow(QWidget *parent) :
    QDialog(parent),
    detailsTextEdit(new QTextEdit(this))
{
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(detailsTextEdit);

    setLayout(layout);
    setWindowTitle("Mission Details");
    resize(400, 300);
}

void MissionDetailWindow::setMissionDetails(const QString &details)
{
    detailsTextEdit->setPlainText(details);
}

#include "missiondetailwindow.h"

MissionDetailWindow::MissionDetailWindow(QWidget *parent)
    : QWidget(parent),
      detailsLabel(new QLabel(this)),
      layout(new QVBoxLayout(this))
{
    layout->addWidget(detailsLabel);
    setLayout(layout);
}

MissionDetailWindow::~MissionDetailWindow()
{

}

void MissionDetailWindow::setMissionDetails(const QString &details)
{
    detailsLabel->setText(details);
}

#ifndef MISSIONDETAILWINDOW_H
#define MISSIONDETAILWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>

class MissionDetailWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MissionDetailWindow(QWidget *parent = nullptr);
    ~MissionDetailWindow();
    void setMissionDetails(const QString &details);

private:
    QLabel *detailsLabel;
    QVBoxLayout *layout;
};

#endif // MISSIONDETAILWINDOW_H

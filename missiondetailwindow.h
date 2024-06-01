#ifndef MISSIONDETAILWINDOW_H
#define MISSIONDETAILWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QVBoxLayout>

class MissionDetailWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MissionDetailWindow(QWidget *parent = nullptr);

    void setMissionDetails(const QString &details);

private:
    QTextEdit *detailsTextEdit;
};

#endif // MISSIONDETAILWINDOW_H

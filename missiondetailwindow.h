#ifndef MISSIONDETAILWINDOW_H
#define MISSIONDETAILWINDOW_H

#include <QDialog>
#include <QTextEdit>
#include <QPushButton>
#include <QVBoxLayout>

class MissionDetailWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MissionDetailWindow(QWidget *parent = nullptr);
    ~MissionDetailWindow();
    void setMissionDetails(const QString &details);

private:
    QTextEdit *detailsTextEdit;
    QPushButton *closeButton;
};

#endif // MISSIONDETAILWINDOW_H

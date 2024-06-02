#ifndef GLOBALSTATSWINDOW_H
#define GLOBALSTATSWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>

class GlobalStatsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit GlobalStatsWindow(QWidget *parent = nullptr);
    ~GlobalStatsWindow();

private slots:
    void on_backButton_clicked();

private:
    QLabel *statsLabel;
    QPushButton *backButton;
};

#endif // GLOBALSTATSWINDOW_H

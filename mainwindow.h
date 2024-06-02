#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLineEdit>
#include <QTableWidget>
#include <QVector>
#include <QComboBox>
#include <vector>

#include "missiondetailwindow.h"
#include "globalstatswindow.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();
    void on_filterChanged();
    void on_tableWidget_cellClicked(int row, int column);
    void on_globalStatsButton_clicked();

private:
    void loadCSV(const QString &filename);
    void setupTable();
    void updateTable(const std::vector<std::vector<QString>> &data);

    Ui::MainWindow *ui;
    QLineEdit *searchLineEdit;
    QTableWidget *tableWidget;
    QVector<QLineEdit*> filterLineEdits;
    std::vector<std::vector<QString>> csvData;
    MissionDetailWindow *missionDetailWindow;
    GlobalStatsWindow *globalStatsWindow;
    QPushButton *globalStatsButton;
};

#endif // MAINWINDOW_H

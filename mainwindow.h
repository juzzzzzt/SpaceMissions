#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVector>
#include <QStringList>
#include <QList>

#include "missiondetailwindow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_searchButton_clicked();
    void on_filterChanged();
    void on_tableWidget_cellClicked(int row, int column);

private:
    Ui::MainWindow *ui;
    QLineEdit *searchLineEdit;
    QTableWidget *tableWidget;
    QVector<QLineEdit*> filterLineEdits;
    std::vector<std::vector<QString>> csvData;
    MissionDetailWindow *missionDetailWindow;

    void loadCSV(const QString &filename);
    void setupTable();
    void updateTable(const std::vector<std::vector<QString>> &data);
};

#endif // MAINWINDOW_H

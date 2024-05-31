#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPushButton>
#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <vector>
#include "statwindow.h"

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
    void on_filterChanged();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();

private:

    Ui::MainWindow *ui;
    QLineEdit *searchLineEdit;
    QTableWidget *tableWidget;
    QVector<QLineEdit *> filterLineEdits;
    std::vector<std::vector<QString>> csvData;

    void loadCSV(const QString &filename);
    void setupTable();
    void updateTable(const std::vector<std::vector<QString>> &data);

    QPushButton *openWindowButton;
    StatWindow *secondWindow;
    QComboBox *filterComboBox;

};

#endif

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QString>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>

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
    void loadCSV(const QString &filename);
    void updateTable(const std::vector<std::vector<QString>> &data);

private:
    Ui::MainWindow *ui;
    std::vector<std::vector<QString>> csvData;
    QLineEdit *searchLineEdit;
    QComboBox *filterComboBox;
    QLineEdit *filterLineEdit;
    QTableWidget *tableWidget;
};

#endif // MAINWINDOW_H

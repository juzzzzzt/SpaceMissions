#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QComboBox>
#include <QTableWidget>
#include <vector>

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

private:
    void loadCSV(const QString &filename);
    void setupTable();
    void updateTable(const std::vector<std::vector<QString>> &data);

    Ui::MainWindow *ui;
    QLineEdit *searchLineEdit;
    QComboBox *filterComboBox;
    QTableWidget *tableWidget;
    std::vector<std::vector<QString>> csvData;
    QVector<QLineEdit*> filterLineEdits;  // Добавить объявление переменной здесь
};

#endif // MAINWINDOW_H

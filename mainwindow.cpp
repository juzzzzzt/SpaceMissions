#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvparser.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QHeaderView>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create and set up UI components
    searchLineEdit = new QLineEdit(this);
    filterComboBox = new QComboBox(this);
    filterLineEdit = new QLineEdit(this);
    tableWidget = new QTableWidget(this);

    QPushButton *searchButton = new QPushButton("Search", this);

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    // Setup filter combo box with criteria
    filterComboBox->addItems({"CompanyName", "Location", "Datum", "Detail", "Status Rocket", "Rocket", "Status Mission"});

    QHBoxLayout *filterLayout = new QHBoxLayout;
    filterLayout->addWidget(filterComboBox);
    filterLayout->addWidget(filterLineEdit);

    mainLayout->addLayout(filterLayout);
    mainLayout->addWidget(tableWidget);

    setCentralWidget(centralWidget);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_filterChanged);
    connect(filterLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_filterChanged);

    loadCSV("C:/Users/79032/Documents/space_missions.csv"); // Adjust the path to your CSV file
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCSV(const QString &filename)
{
    csvData = parseCSV(filename);
    updateTable(csvData);
}

void MainWindow::updateTable(const std::vector<std::vector<QString>> &data)
{
    if (data.empty()) return;

    tableWidget->setRowCount(data.size());
    tableWidget->setColumnCount(data[0].size());

    for (size_t i = 0; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            tableWidget->setItem(i, j, new QTableWidgetItem(data[i][j]));
        }
    }
}

void MainWindow::on_searchButton_clicked()
{
    QString searchText = searchLineEdit->text().trimmed();
    std::vector<std::vector<QString>> filteredData;
    for (const auto &row : csvData) {
        for (const auto &field : row) {
            if (field.contains(searchText, Qt::CaseInsensitive)) {
                filteredData.push_back(row);
                break;
            }
        }
    }
    updateTable(filteredData);
}

void MainWindow::on_filterChanged()
{
    int filterIndex = filterComboBox->currentIndex();
    QString filterText = filterLineEdit->text().trimmed();

    std::vector<std::vector<QString>> filteredData;

    for (const auto &row : csvData) {
        if (row[filterIndex].contains(filterText, Qt::CaseInsensitive)) {
            filteredData.push_back(row);
        }
    }

    updateTable(filteredData);
}

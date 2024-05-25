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
    //filterComboBox = new QComboBox(this);
    tableWidget = new QTableWidget(this);

    QPushButton *searchButton = new QPushButton("Search", this);

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);

    // Setup filter combo box with criteria
    //filterComboBox->addItems({"CompanyName", "Location", "Datum", "RocketName", "Status Rocket", "Status Mission"});

    //mainLayout->addWidget(filterComboBox);
    mainLayout->addWidget(tableWidget);

    setCentralWidget(centralWidget);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    //connect(filterComboBox, QOverload<int>::of(&QComboBox::currentIndexChanged), this, &MainWindow::on_filterChanged);

    loadCSV("C:/Users/79032/Documents/space_missions.csv"); // Adjust the path to your CSV file
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadCSV(const QString &filename)
{
    csvData = parseCSV(filename);
    setupTable();
    updateTable(csvData);
}

void MainWindow::setupTable()
{
    if (csvData.empty()) return;

    tableWidget->setColumnCount(csvData[0].size());
    tableWidget->setRowCount(0); // Initially no rows, as we will add them dynamically

    // Set the table headers
    QStringList headers;
    headers << "CompanyName" << "Location" << "Datum" << "RocketName" << "Status Rocket" << "Status Mission";
    tableWidget->setHorizontalHeaderLabels(headers);

    // Add QLineEdit for each column for filtering
    filterLineEdits.clear();
    QHBoxLayout *filterLayout = new QHBoxLayout;
    for (int i = 0; i < csvData[0].size(); ++i) {
        QLineEdit *filterLineEdit = new QLineEdit(this);
        filterLineEdits.append(filterLineEdit);
        filterLayout->addWidget(filterLineEdit);

        connect(filterLineEdit, &QLineEdit::textChanged, this, &MainWindow::on_filterChanged);
    }

    QVBoxLayout *mainLayout = static_cast<QVBoxLayout *>(centralWidget()->layout());
    mainLayout->insertLayout(2, filterLayout);

    // Set the columns to resize to fit the content
    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    // Set the same width for the filter QLineEdits as the columns
    for (int i = 0; i < csvData[0].size(); ++i) {
        filterLineEdits[i]->setMinimumWidth(tableWidget->columnWidth(i));
    }
}

void MainWindow::updateTable(const std::vector<std::vector<QString>> &data)
{
    tableWidget->setRowCount(data.size());
    for (size_t i = 1; i < data.size(); ++i) {
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
    std::vector<std::vector<QString>> filteredData = csvData;
    for (int i = 0; i < filterLineEdits.size(); ++i) {
        QString filterText = filterLineEdits[i]->text().trimmed();
        if (!filterText.isEmpty()) {
            std::vector<std::vector<QString>> tempFilteredData;
            for (const auto &row : filteredData) {
                if (row[i].contains(filterText, Qt::CaseInsensitive)) {
                    tempFilteredData.push_back(row);
                }
            }
            filteredData = std::move(tempFilteredData);
        }
    }
    updateTable(filteredData);
}



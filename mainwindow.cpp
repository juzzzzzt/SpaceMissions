// mainwindow.cpp
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
#include <QDebug>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include <QRegularExpression>
#include <QUrl>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , missionDetailWindow(new MissionDetailWindow(this))
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    // Create and set up UI components
    searchLineEdit = new QLineEdit(this);
    tableWidget = new QTableWidget(this);

    QPushButton *searchButton = new QPushButton("Search", this);

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableWidget);

    setCentralWidget(centralWidget);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_cellClicked);
    QPushButton *statsButton = new QPushButton("Stats Window", this);
    connect(statsButton, &QPushButton::clicked, this, &MainWindow::on_statsButton_clicked);
    loadCSV("C:/Users/79032/Documents/space_missions.csv");
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


    tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    for (int i = 0; i < csvData[0].size(); ++i) {
        filterLineEdits[i]->setMinimumWidth(tableWidget->columnWidth(i));
    }
}

void MainWindow::updateTable(const std::vector<std::vector<QString>> &data)
{
    tableWidget->setRowCount(data.size());
    for (size_t i = 1; i < data.size(); ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            QTableWidgetItem *item = new QTableWidgetItem(data[i][j]);
            if (j == 0) {
                item->setData(Qt::UserRole, i);
                item->setForeground(Qt::blue);
                item->setFont(QFont("Arial", 10, QFont::Bold));
                item->setTextAlignment(Qt::AlignCenter);
            }
            tableWidget->setItem(i, j, item);
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


void MainWindow::on_tableWidget_cellClicked(int row, int column)
{
    if (column == 0) {
        QString missionName = csvData[row][column];


        QString wikipediaUrl = "https://en.wikipedia.org/wiki/" + missionName.replace("\"", "");


        QUrl url = commandLineUrlArgument(wikipediaUrl);

            Browser browser;
            BrowserWindow *window = browser.createHiddenWindow();
            window->tabWidget()->setUrl(url);
            window->show();

]

//        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//        connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
//            if (reply->error() != QNetworkReply::NoError) {
//                QMessageBox::warning(this, "Error", "Failed to fetch Wikipedia page for the mission.");
//                return;
//            }


//            QByteArray htmlData = reply->readAll();


//            QString missionDetails = QString::fromUtf8(htmlData);
//            QMessageBox::information(this, "Mission Details", missionDetails);

//            reply->deleteLater();
//        });

//        manager->get(QNetworkRequest(QUrl(wikipediaUrl)));
    }
}

void MainWindow::on_statsButton_clicked() {

}

//void MainWindow::on_tableWidget_cellClicked(int row, int column)
//{
//    if (column == 3) { // Assuming the mission name is in the 4th column (index 3)
//        QString missionName = csvData[row][column];

//        // Формируем URL страницы https://nextspaceflight.com/ для данной миссии
//        QString nextSpaceFlightUrl = "https://nextspaceflight.com/launches/";

//        // Создаем объект QNetworkAccessManager для выполнения HTTP-запросов
//        QNetworkAccessManager *manager = new QNetworkAccessManager(this);
//        connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply){
//            if (reply->error() != QNetworkReply::NoError) {
//                QMessageBox::warning(this, "Error", "Failed to fetch data from nextspaceflight.com");
//                return;
//            }

//            // Получаем HTML-код страницы
//            QByteArray htmlData = reply->readAll();

//            // Парсим HTML-код, чтобы извлечь информацию о миссии
//            QString missionDetails = parseNextSpaceFlightHtml(htmlData, missionName);
//            if (missionDetails.isEmpty()) {
//                QMessageBox::warning(this, "Error", "Failed to extract mission details from nextspaceflight.com");
//                return;
//            }

//            // Отображаем информацию о миссии
//            QMessageBox::information(this, "Mission Details", missionDetails);

//            reply->deleteLater();
//        });

//        // Выполняем запрос на страницу nextspaceflight.com
//        manager->get(QNetworkRequest(QUrl(nextSpaceFlightUrl)));
//    }
//}

//QString MainWindow::parseNextSpaceFlightHtml(const QByteArray &htmlData, const QString &missionName)
//{
//    QString missionDetails;

//    // Создаем регулярное выражение для поиска информации о миссии в HTML-коде
//    QRegularExpression regex("<tr>\\s*<td>(.*?)</td>\\s*<td>" + missionName + "</td>(.*?)</tr>");
//    QRegularExpressionMatch match = regex.match(QString::fromUtf8(htmlData));

//    // Если найдено соответствие, извлекаем информацию о миссии
//    if (match.hasMatch()) {
//        QString missionInfo = match.captured(1) + match.captured(2);

//        // Удаление HTML-тегов из информации о миссии
//        missionInfo.remove(QRegularExpression("<[^>]*>"));

//        missionDetails = "Mission Details:\n\n" + missionInfo;
//    } else {
//        missionDetails = "Mission details not found.";
//    }

//    return missionDetails;
//}

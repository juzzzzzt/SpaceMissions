#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "csvparser.h"
#include "disambiguationdialog.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QLineEdit>
#include <QComboBox>
#include <QHeaderView>
#include <QDebug>
#include <QProcess>
#include <QMessageBox>
#include <QRegularExpression>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , missionDetailWindow(new MissionDetailWindow(this))
{
    ui->setupUi(this);

    QWidget *centralWidget = new QWidget(this);
    QVBoxLayout *mainLayout = new QVBoxLayout(centralWidget);

    searchLineEdit = new QLineEdit(this);
    tableWidget = new QTableWidget(this);

    QString imagePath = "C:/Users/Аскар/Downloads/back.png";
    centralWidget->setStyleSheet(
        QString(
        "QWidget {"
        "    background-color: black;"
        "    color: white;"
        "    border: 1px solid gray;"
        "}"
        "QTableWidget {"
        "    background-color: black;"
        "    color: white;"
        "    background-image: url(%100);"
        "    background-repeat: repeat;"
        "    background-position: center;"
        "    background-size: auto;"
        "    gridline-color: black;"
        "    border: none;"
        "}"
        "QTableWidget::item {"
        "    border: none;"
        "}"
        "QHeaderView::section {"
        "    background-color: black;"
        "    color: white;"
        "    border: 1px solid gray;"
        "}"
        "QLineEdit {"
        "    background-color: #333333;"
        "    color: white;"
        "    border: 1px solid gray;"
        "    padding: 5px;"
        "}"
        "QPushButton {"
        "    background-color: #333333;"
        "    color: white;"
        "    border: 1px solid gray;"
        "    padding: 5px;"
        "}"
        "QPushButton:hover {"
        "    background-color: #444444;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #555555;"
        "}"
        ).arg(imagePath));

    QPushButton *searchButton = new QPushButton("Search", this);

    QHBoxLayout *searchLayout = new QHBoxLayout;
    searchLayout->addWidget(searchLineEdit);
    searchLayout->addWidget(searchButton);

    mainLayout->addLayout(searchLayout);
    mainLayout->addWidget(tableWidget);

    setCentralWidget(centralWidget);

    connect(searchButton, &QPushButton::clicked, this, &MainWindow::on_searchButton_clicked);
    connect(tableWidget, &QTableWidget::cellClicked, this, &MainWindow::on_tableWidget_cellClicked);
    loadCSV("C:/Users/Аскар/OneDrive/Рабочий стол/space_missions.csv");

    tableWidget->verticalHeader()->setVisible(false);
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
    tableWidget->setRowCount(0);

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
            if (j == 0 or j == 3) {
                item->setData(Qt::UserRole, i);
                item->setForeground(Qt::cyan);
                item->setFont(QFont("Arial", 10, QFont::Bold));
                item->setTextAlignment(Qt::AlignCenter);
            }
            else {
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
        QString companyName = tableWidget->item(row, column)->text();
        QString wikipediaUrl;

        if (companyName == "\"US Navy") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/SpaceX";
        } else if (companyName == "\"CASC") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/China_Aerospace_Science_and_Technology_Corporation";
        } else if (companyName == "\"ULA") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/United_Launch_Alliance";
        } else if (companyName == "\"JAXA") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/JAXA";
        } else if (companyName == "\"Northrop") {
            wikipediaUrl = "https://www.northropgrumman.com";
        } else if (companyName == "\"VKS RF") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Russian_Aerospace_Forces";
        } else if (companyName == "\"RVSN USSR") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Strategic_Rocket_Forces";
        } else if (companyName == "\"SpaceX") {
            wikipediaUrl = "https://www.spacex.com";
        } else if (companyName == "\"Lockheed") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Lockheed_Martin_Space";
        } else if (companyName == "\"NASA") {
            wikipediaUrl = "https://www.nasa.gov";
        } else if (companyName == "\"ILS") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/International_Launch_Services";
        } else if (companyName == "\"Boeing") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Boeing_Defense,_Space_%26_Security";
        } else if (companyName == "\"MHI") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Mitsubishi_Heavy_Industries";
        } else if (companyName == "\"ISAS") {
            wikipediaUrl = "https://en.m.wikipedia.org/wiki/Institute_of_Space_and_Astronautical_Science";
        } else if (companyName == "\"Rocket Lab") {
            wikipediaUrl = "https://www.rocketlabusa.com";
        } else if (companyName == "\"ESA") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/European_Space_Agency";
        } else if (companyName == "\"ASI") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Italian_Space_Agency";
        } else if (companyName == "\"MITT") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Moscow_Institute_of_Thermal_Technology";
        } else if (companyName == "\"IRGC") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Islamic_Revolutionary_Guard_Corps_Aerospace_Force";
        } else if (companyName == "\"IAI") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Israel_Aerospace_Industries";
        } else if (companyName == "\"ISA") {
            wikipediaUrl = "https://en.wikipedia.org/wiki/Iranian_Space_Agency";
        }

        else {
            wikipediaUrl = "https://en.wikipedia.org/wiki/" + companyName.replace("\"", "");
        }

        QStringList arguments;
        QString scriptPath = "C:/Users/Аскар/Desktop/pythonProject/parse_wikipedia.py";
        arguments << scriptPath << wikipediaUrl;

        QProcess *process = new QProcess(this);
        QString pythonPath = "C:/Program Files/Python312/python.exe";
        connect(process, &QProcess::readyReadStandardOutput, this, [this, process, scriptPath, pythonPath]() { // захватите scriptPath и pythonPath
            QString output = process->readAllStandardOutput();

            if (output.startsWith("Disambiguation error:")) {
                QStringList options = output.remove("Disambiguation error: [").remove("]").split(", ");
                DisambiguationDialog dialog(options, this);
                if (dialog.exec() == QDialog::Accepted) {
                    QString selectedOption = dialog.getSelectedOption();
                    QStringList newArguments;
                    QString newWikipediaUrl = "https://en.wikipedia.org/wiki/" + selectedOption.replace("\"", "");
                    newArguments << scriptPath << newWikipediaUrl;

                    QProcess *newProcess = new QProcess(this);
                    newProcess->start(pythonPath, newArguments);
                    connect(newProcess, &QProcess::readyReadStandardOutput, this, [this, newProcess]() {
                        QString newOutput = newProcess->readAllStandardOutput();
                        missionDetailWindow->setMissionDetails(newOutput);
                        missionDetailWindow->exec();
                    });
                    connect(newProcess, &QProcess::readyReadStandardError, this, [this, newProcess]() {
                        QString error = newProcess->readAllStandardError();
                        QMessageBox::critical(this, "Error", error);
                    });
                }
            } else {
                missionDetailWindow->setMissionDetails(output);
                missionDetailWindow->exec();
            }

            process->deleteLater();
        });
        connect(process, &QProcess::readyReadStandardError, this, [this, process]() {
            QString error = process->readAllStandardError();
            QMessageBox::critical(this, "Error", error);
        });

        process->start(pythonPath, arguments);
    } else if (column == 3) { // Нажатие на название ракеты
        QString rocketName = tableWidget->item(row, column)->text();
        QStringList arguments;
        QString scriptPath = "C:/Users/Аскар/Desktop/pythonProject/fetch_rocket_details.py";
        arguments << scriptPath << rocketName;

        QProcess *process = new QProcess(this);
        QString pythonPath = "C:/Program Files/Python312/python.exe";
        connect(process, &QProcess::readyReadStandardOutput, this, [this, process]() {
            QString output = process->readAllStandardOutput();
            missionDetailWindow->setMissionDetails(output);
            missionDetailWindow->exec();
            process->deleteLater();
        });
        connect(process, &QProcess::readyReadStandardError, this, [this, process]() {
            QString error = process->readAllStandardError();
            QMessageBox::critical(this, "Error", error);
        });

        process->start(pythonPath, arguments);
    }
}

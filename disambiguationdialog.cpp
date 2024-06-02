#include "disambiguationdialog.h"

DisambiguationDialog::DisambiguationDialog(const QStringList &options, QWidget *parent)
    : QDialog(parent), selectedOption("")
{
    QVBoxLayout *layout = new QVBoxLayout(this);

    listWidget = new QListWidget(this);
    listWidget->addItems(options);
    layout->addWidget(listWidget);

    connect(listWidget, &QListWidget::itemDoubleClicked, this, &DisambiguationDialog::onItemDoubleClicked);

    QPushButton *okButton = new QPushButton("OK", this);
    layout->addWidget(okButton);

    connect(okButton, &QPushButton::clicked, this, &QDialog::accept);

    setLayout(layout);
    setWindowTitle("Disambiguation");
    resize(400, 300);
}

QString DisambiguationDialog::getSelectedOption() const
{
    return selectedOption;
}

void DisambiguationDialog::onItemDoubleClicked(QListWidgetItem *item)
{
    selectedOption = item->text();
    accept();
}

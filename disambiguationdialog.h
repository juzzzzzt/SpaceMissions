#ifndef DISAMBIGUATIONDIALOG_H
#define DISAMBIGUATIONDIALOG_H

#include <QDialog>
#include <QListWidget>
#include <QVBoxLayout>
#include <QPushButton>

class DisambiguationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DisambiguationDialog(const QStringList &options, QWidget *parent = nullptr);

    QString getSelectedOption() const;

private slots:
    void onItemDoubleClicked(QListWidgetItem *item);

private:
    QListWidget *listWidget;
    QString selectedOption;
};

#endif // DISAMBIGUATIONDIALOG_H

#ifndef STATWINDOW_H
#define STATWINDOW_H

#include <QWidget>
#include <QLabel>

namespace Ui {
class StatWindow;
}

class StatWindow : public QWidget
{
    Q_OBJECT

public:
    explicit StatWindow(QWidget *parent = nullptr);
    ~StatWindow();

private slots:
    void on_label_linkActivated(const QString &link);

private:
    Ui::StatWindow *ui;
    QLabel *imageLabel;
};

#endif // STATWINDOW_H

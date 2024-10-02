#ifndef SECOND_WINDOW_H
#define SECOND_WINDOW_H

#include <QDialog>
namespace Ui {
class Second_Window;
}

class Second_Window : public QDialog
{
    Q_OBJECT

public:
    explicit Second_Window(QWidget *parent = nullptr);
    ~Second_Window();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Second_Window *ui;
};

#endif // SECOND_WINDOW_H

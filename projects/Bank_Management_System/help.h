#ifndef HELP_H
#define HELP_H

#include <QDialog>

namespace Ui {
class Help;
}
/**
 * @brief The Help class provides a dialog for displaying help information.
 *
 * This class inherits from QDialog and allows users to access help content
 * based on their selection from a combo box. It includes methods to change
 * the content dynamically and close the dialog.
 */
class Help : public QDialog
{
    Q_OBJECT

public:
    explicit Help(QWidget *parent = nullptr);
    ~Help();

private slots:

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

private:
    Ui::Help *ui;
};

#endif // HELP_H

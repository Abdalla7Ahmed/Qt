#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_actionNew_triggered();

    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionCopy_triggered();

    void on_actionCut_triggered();

    void on_actionPast_triggered();

    void on_actionundo_triggered();

    void on_actionredo_triggered();

    void on_actionSave_as_triggered();

    void on_actionAbout_triggered();



    void on_actionFont_triggered();

    void on_actionColor_triggered();

    void on_actionBackground_text_triggered();

    void on_actionBackgrount_Edit_Text_triggered();

    void on_actionPrint_triggered();

private:
    Ui::MainWindow *ui;
    QString file_path;
};
#endif // MAINWINDOW_H

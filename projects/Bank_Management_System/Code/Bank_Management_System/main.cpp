#include "mainwindow.h"

#include <QApplication>

/**
 * @brief The main entry point of the application.
 *
 * This function initializes the QApplication, creates an instance of
 * the MainWindow, and shows it in a maximized state. The application
 * enters its main event loop, waiting for user interaction.
 *
 * @param argc The number of command-line arguments.
 * @param argv The command-line arguments.
 * @return int The exit status of the application.
 */
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow w;
    // w.showFullScreen();
    // w.show();
    w.showMaximized();
    return app.exec();
}

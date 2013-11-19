#ifndef MAINWINDOW_H
#define MAINWINDOW_H

typedef struct MainWindowTag
{
    GtkWindow *window;

    GtkButton *lkButton;
    GtkButton *sdButton;

} MainWindow;

MainWindow *clksd_mainwindow_new();
#endif // MAINWINDOW_H

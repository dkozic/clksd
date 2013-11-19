#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include "mainwindow.h"

#define GETTEXT_PACKAGE "clksd"
#define PROGRAMNAME_LOCALEDIR "./locale"

int main(int argc, char *argv[])
{
    switch (argc)
    {
    case 1:
        g_setenv("LC_MESSAGES", "en", TRUE);
        break;
    default:
        g_setenv("LC_MESSAGES", argv[1], TRUE);
        break;
    }

    bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
    bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
    textdomain(GETTEXT_PACKAGE);

    /*Gtk staff*/
    MainWindow *mainWindow;

    g_debug("Starting cLKSD...");
    gtk_init(&argc, &argv);

    mainWindow = clksd_mainwindow_new();

    g_debug("Starting cLKSD done!");

    gtk_main();


    return 0;
}

#include <stdlib.h>
#include <gtk/gtk.h>
#include <glib/gi18n.h>
#include <windows.h>
#include <sqlite3.h>
#include "lk.h"
#include "sd.h"
#include "lkwindow.h"
#include "sdwindow.h"

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
    //LkWindow *lkWindow;

    g_debug("Starting cLKSD...");
    gtk_init(&argc, &argv);

    //lkWindow = clksd_lkwindow_new();
    clksd_lkwindow_new();

    g_debug("Starting cLKSD done!");

    gtk_main();


    return 0;
}

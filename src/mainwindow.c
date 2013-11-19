#include <stdio.h>
#include <gtk/gtk.h>
#include <winscard.h>
#include <CelikApi.h>
#include <sqlite3.h>
#include <glib/gi18n.h>
#include "lk.h"
#include "lkwindow.h"
#include "sd.h"
#include "sdwindow.h"
#include "mainwindow.h"

G_MODULE_EXPORT void clksd_mainwindow_on_destroy(GtkObject *object, MainWindow *mainWindow)
{
    g_debug("Destroying cLKSD...");
    g_free(mainWindow);
    gtk_main_quit();
    g_debug("Destroying cLKSD done!");
}

G_MODULE_EXPORT gboolean clksd_mainwindow_on_delete(GtkObject *object, GdkEvent *event, MainWindow *mainWindow)
{
    GtkWidget *dialog;
    gint response;
    dialog = gtk_message_dialog_new(mainWindow->window,
                                    GTK_DIALOG_MODAL,
                                    GTK_MESSAGE_QUESTION,
                                    GTK_BUTTONS_YES_NO,
                                    _("Are you sure to quit?"));
    gtk_window_set_title(GTK_WINDOW(dialog), _("Question"));
    response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
    if (response == GTK_RESPONSE_YES)
    {
        return FALSE;
    }
    return TRUE;

}

G_MODULE_EXPORT void clksd_mainwindow_on_lkbutton_clicked(GtkObject *object, MainWindow *mainWindow)
{
    LkWindow *lkWindow;

    lkWindow = clksd_lkwindow_new();
}

G_MODULE_EXPORT void clksd_mainwindow_on_sdbutton_clicked(GtkObject *object, MainWindow *mainWindow)
{
    SdWindow *sdWindow;

    sdWindow = clksd_sdwindow_new();
}

MainWindow *clksd_mainwindow_new()
{
    /*Gtk staff*/
    GtkBuilder *builder;
    GError *error = NULL;

    MainWindow *mainWindow;

    mainWindow = (MainWindow *) g_malloc(sizeof (MainWindow));

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "glade/mainwindow.glade", &error))
    {
        g_error("%s", error->message);
    }

    mainWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "mainwindow"));

    mainWindow->lkButton = GTK_BUTTON(gtk_builder_get_object(builder, "lkButton"));
    mainWindow->sdButton = GTK_BUTTON(gtk_builder_get_object(builder, "sdButton"));

    g_signal_connect(G_OBJECT(mainWindow->window), "destroy", G_CALLBACK(clksd_mainwindow_on_destroy), (gpointer) mainWindow);
    g_signal_connect(G_OBJECT(mainWindow->window), "delete_event", G_CALLBACK(clksd_mainwindow_on_delete), (gpointer) mainWindow);
    g_signal_connect(G_OBJECT(mainWindow->lkButton), "clicked", G_CALLBACK(clksd_mainwindow_on_lkbutton_clicked), (gpointer) mainWindow);
    g_signal_connect(G_OBJECT(mainWindow->sdButton), "clicked", G_CALLBACK(clksd_mainwindow_on_sdbutton_clicked), (gpointer) mainWindow);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show((GtkWidget *) mainWindow->window);

    return mainWindow;
}



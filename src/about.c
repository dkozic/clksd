#include <stdio.h>
#include <gtk/gtk.h>
#include <string.h>

GtkAboutDialog *clksd_aboutdialog_new()
{
    /*Gtk staff*/
    GtkBuilder *builder;
    GError *error = NULL;
    GtkAboutDialog *aboutDialog = NULL;
    gchar *gladeFile = "glade/about.glade";

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, gladeFile, &error))
    {
        g_error("Error loading glade file(%s): %s", gladeFile, error->message);
        g_clear_error(&error);
        return aboutDialog;
    }

    aboutDialog = GTK_ABOUT_DIALOG(gtk_builder_get_object(builder, "aboutdialog"));

    g_object_unref(G_OBJECT(builder));

    gtk_dialog_run((GtkDialog *) aboutDialog);
    gtk_widget_destroy ((GtkWidget *) aboutDialog);

    return aboutDialog;
}

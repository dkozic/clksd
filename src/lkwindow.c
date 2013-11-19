#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <winscard.h>
#include <CelikApi.h>
#include <gtk/gtk.h>
#include <string.h>
#include <hpdf.h>
#include <sqlite3.h>
#include <glib/gi18n.h>
#include "lk.h"
#include "lkwindow.h"
#include "about.h"
#include "lkprint.h"
#include "lksc.h"
#include "lkdb.h"

#define STATUSBAR_TIMEOUT 3000

typedef struct statusbar_message
{
    GtkStatusbar *statusbar;
    guint context;
    guint message;
} StatusbarMessage;

static void on_window_destroy(GtkObject *object, LkWindow *lkWindow)
{
    g_debug("Destroying lkwindow...");
    clksd_lk_free(lkWindow->lk);
    g_free(lkWindow);
    g_debug("Destroying lkwindow done!");
}

static void lk_clear(LkWindow *lkWindow)
{
    clksd_lk_free(lkWindow->lk);
    lkWindow->lk = NULL;

    gtk_label_set_label(lkWindow->docRegNoTxt, NULL);
    gtk_label_set_label(lkWindow->issuingDateTxt, NULL);
    gtk_label_set_label(lkWindow->expiryDateTxt, NULL);
    gtk_label_set_label(lkWindow->issuingAuthorityTxt, NULL);

    gtk_label_set_label(lkWindow->personalNumberTxt, NULL);
    gtk_label_set_label(lkWindow->surnameTxt, NULL);
    gtk_label_set_label(lkWindow->givenNameTxt, NULL);
    gtk_label_set_label(lkWindow->parentGivenNameTxt, NULL);
    gtk_label_set_label(lkWindow->sexTxt, NULL);
    gtk_label_set_label(lkWindow->placeOfBirthTxt, NULL);
    gtk_label_set_label(lkWindow->stateOfBirthTxt, NULL);
    gtk_label_set_label(lkWindow->dateOfBirthTxt, NULL);
    gtk_label_set_label(lkWindow->communityOfBirthTxt, NULL);

    gtk_label_set_label(lkWindow->stateTxt, NULL);
    gtk_label_set_label(lkWindow->communityTxt, NULL);
    gtk_label_set_label(lkWindow->placeTxt, NULL);
    gtk_label_set_label(lkWindow->streetTxt, NULL);
    gtk_label_set_label(lkWindow->houseNumberTxt, NULL);
    gtk_label_set_label(lkWindow->houseLetterTxt, NULL);
    gtk_label_set_label(lkWindow->entranceTxt, NULL);
    gtk_label_set_label(lkWindow->apartmentNumberTxt, NULL);

    gtk_image_set_from_stock(lkWindow->image, GTK_STOCK_MISSING_IMAGE, GTK_ICON_SIZE_BUTTON);
    gtk_widget_set_sensitive(GTK_WIDGET(lkWindow->printToolButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(lkWindow->menuitem_print), FALSE);
}

static gboolean statusbar_clear (StatusbarMessage *statusbarMessage)
{
    gtk_statusbar_remove(statusbarMessage->statusbar, statusbarMessage->context, statusbarMessage->message);
    return FALSE;
}

static void handle_message(LkWindow *lkWindow, char *message)
{
    guint contextid;
    guint messageid;
    StatusbarMessage *statusbarMessage;

    contextid = gtk_statusbar_get_context_id(lkWindow->statusbar, "read");
    messageid = gtk_statusbar_push(lkWindow->statusbar, contextid, message);

    statusbarMessage = g_new0(StatusbarMessage, 1);
    statusbarMessage->statusbar = lkWindow->statusbar;
    statusbarMessage->context = contextid;
    statusbarMessage->message = messageid;

    g_timeout_add(STATUSBAR_TIMEOUT, (GSourceFunc) statusbar_clear, (gpointer)statusbarMessage);
}

static void handle_error(LkWindow *lkWindow, GError *error)
{
    guint contextid;
    guint messageid;
    StatusbarMessage *statusbarMessage;
    if (error != NULL)
    {
        g_debug("%s\n", error->message);

        contextid = gtk_statusbar_get_context_id(lkWindow->statusbar, "read");
        messageid = gtk_statusbar_push(lkWindow->statusbar, contextid, error->message);

        statusbarMessage = g_new0(StatusbarMessage, 1);
        statusbarMessage->statusbar = lkWindow->statusbar;
        statusbarMessage->context = contextid;
        statusbarMessage->message = messageid;

        g_timeout_add(STATUSBAR_TIMEOUT, (GSourceFunc) statusbar_clear, (gpointer)statusbarMessage);

        g_clear_error(&error);
    }
}

static void pixbuf_size_prepared(GdkPixbufLoader *loader, gint width, gint height, LkWindow *lkWindow)
{
    gdk_pixbuf_loader_set_size (loader,180, 240);
}

static void pixbuf_area_prepared(GdkPixbufLoader *loader, LkWindow *lkWindow)
{
    GdkPixbuf *pixbuf;

    pixbuf = gdk_pixbuf_loader_get_pixbuf(loader);
    g_object_ref(pixbuf);
    gtk_image_set_from_pixbuf(lkWindow->image, pixbuf);
}

static void lk_show (LkWindow *lkWindow, Lk *lk)
{
    GdkPixbufLoader *loader;
    GError *error = NULL;

    lkWindow->lk = lk;

    gtk_label_set_label(lkWindow->docRegNoTxt, clksd_lk_get_docRegNo(lk));
    gtk_label_set_label(lkWindow->issuingDateTxt, clksd_lk_get_issuingDate(lk));
    gtk_label_set_label(lkWindow->expiryDateTxt, clksd_lk_get_expiryDate(lk));
    gtk_label_set_label(lkWindow->issuingAuthorityTxt, clksd_lk_get_issuingAuthority(lk));

    gtk_label_set_label(lkWindow->personalNumberTxt, clksd_lk_get_personalNumber(lk));
    gtk_label_set_label(lkWindow->surnameTxt, clksd_lk_get_surname(lk));
    gtk_label_set_label(lkWindow->givenNameTxt, clksd_lk_get_givenName(lk));
    gtk_label_set_label(lkWindow->parentGivenNameTxt, clksd_lk_get_parentGivenName(lk));
    gtk_label_set_label(lkWindow->sexTxt, clksd_lk_get_sex(lk));
    gtk_label_set_label(lkWindow->placeOfBirthTxt, clksd_lk_get_placeOfBirth(lk));
    gtk_label_set_label(lkWindow->stateOfBirthTxt, clksd_lk_get_stateOfBirth(lk));
    gtk_label_set_label(lkWindow->dateOfBirthTxt, clksd_lk_get_dateOfBirth(lk));
    gtk_label_set_label(lkWindow->communityOfBirthTxt, clksd_lk_get_communityOfBirth(lk));

    gtk_label_set_label(lkWindow->stateTxt, clksd_lk_get_state(lk));
    gtk_label_set_label(lkWindow->communityTxt, clksd_lk_get_community(lk));
    gtk_label_set_label(lkWindow->placeTxt, clksd_lk_get_place(lk));
    gtk_label_set_label(lkWindow->streetTxt, clksd_lk_get_street(lk));
    gtk_label_set_label(lkWindow->houseNumberTxt, clksd_lk_get_houseNumber(lk));
    gtk_label_set_label(lkWindow->houseLetterTxt, clksd_lk_get_houseLetter(lk));
    gtk_label_set_label(lkWindow->entranceTxt, clksd_lk_get_entrance(lk));
    gtk_label_set_label(lkWindow->apartmentNumberTxt, clksd_lk_get_apartmentNumber(lk));

    loader = gdk_pixbuf_loader_new();
    g_signal_connect(G_OBJECT(loader), "area_prepared", G_CALLBACK(pixbuf_area_prepared), lkWindow);
    g_signal_connect(G_OBJECT(loader), "size_prepared", G_CALLBACK(pixbuf_size_prepared), lkWindow);
    gdk_pixbuf_loader_write(loader, clksd_lk_get_portrait(lk), clksd_lk_get_portraitSize(lk), &error);
    if (error != NULL)
    {
        g_printerr("Error %s", error->message);
        g_error_free(error);
        return;
    }


    gdk_pixbuf_loader_close(loader, &error);
    if (error != NULL)
    {
        g_printerr("Error %s", error->message);
        g_error_free(error);
        return;
    }

    gtk_widget_set_sensitive(GTK_WIDGET(lkWindow->printToolButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(lkWindow->menuitem_print), TRUE);

}

static void read (LkWindow *lkWindow)
{
    gboolean result;
    Lk *lk;
    GError *error = NULL;
    GtkListStore *liststore = lkWindow->liststore;
    GtkTreeIter iter;


    lk_clear(lkWindow);

    lk = clksd_lksc_read_eid(&error);
    if (lk == NULL)
    {
        handle_error(lkWindow, error);
        return;
    }

    lk_show(lkWindow, lk);

    result = clksd_lkdb_insert(lk, &error);
    if (!result)
    {
        handle_error(lkWindow, error);
        return;
    }

    //add row to treeview
    gtk_list_store_append (liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, lk->id, 1, lk->surname, 2, lk->givenName, -1);

    //activate print button
    gtk_widget_set_sensitive(GTK_WIDGET(lkWindow->printToolButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(lkWindow->menuitem_print), TRUE);

    //print OK message to status bar
    handle_message(lkWindow, _("Read OK"));
}
static void on_readtoolbutton_clicked(GtkObject *object, LkWindow *lkWindow)
{
    read (lkWindow);
}

static void print (LkWindow *lkWindow)
{
    GError *error = NULL;
    gchar *fname;
    gchar *fname1;
    gboolean result;
    g_debug("Start printing...");

    fname1 = g_strconcat(lkWindow->lk->personalNumber, ".pdf", NULL);
    fname = g_build_filename(g_get_tmp_dir(), fname1, NULL);
    result = clksd_lkprint_print(lkWindow->lk, fname, &error);
    if (!result)
    {
        handle_error(lkWindow, error);
        return;
    }
    g_debug("Printing done!");

    ShellExecute(NULL, "open", fname, NULL, NULL, SW_SHOWNORMAL);
    g_free(fname);
    g_free(fname1);

    handle_message(lkWindow, _("Print OK"));
}

static void on_printtoolbutton_clicked(GtkObject *object, LkWindow *lkWindow)
{
    print(lkWindow);
}

static void on_menuitem_delete_clicked(GtkMenuItem *menuitem, LkWindow *lkWindow)
{
    GtkTreeSelection *treeSelection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean selected;
    sqlite_int64 id;
    GError *error = NULL;
    gboolean result;

    treeSelection = gtk_tree_view_get_selection(lkWindow->treeview);
    selected = gtk_tree_selection_get_selected(treeSelection, &model, &iter);
    if (selected)
    {
        gtk_tree_model_get (model, &iter, 0, &id, -1);
        result = clksd_lkdb_delete(id, &error);
        if (!result)
        {
            handle_error(lkWindow, error);
            return;
        }
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
    };

    handle_message(lkWindow, _("Delete OK"));
}

static void on_menuitem_delete_all_clicked(GtkMenuItem *menuitem, LkWindow *lkWindow)
{
    gboolean result;
    GError *error = NULL;

    result = clksd_lkdb_delete_all(&error);
    if (!result)
    {
        handle_error(lkWindow, error);
        return;
    }
    gtk_list_store_clear(lkWindow->liststore);

    handle_message(lkWindow, _("Delete all OK"));
}

static void on_menuitem_show_clicked(GtkMenuItem *menuitem, LkWindow *lkWindow)
{
    GtkTreeSelection *treeSelection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean selected;
    sqlite_int64 id;
    Lk *lk;
    GError *error = NULL;

    lk_clear(lkWindow);

    treeSelection = gtk_tree_view_get_selection(lkWindow->treeview);
    selected = gtk_tree_selection_get_selected(treeSelection, &model, &iter);
    if (selected)
    {
        gtk_tree_model_get (model, &iter, 0, &id, -1);
        lk = clksd_lkdb_find(id, &error);
        if (lk == NULL)
        {
            handle_error(lkWindow, error);
            return;
        }
        lk_show(lkWindow, lk);
    }
}

static gboolean on_treeview_button_press(GtkObject *treeview, GdkEventButton *event,  GtkMenu *menu)
{
    if ((event->button == 3) && (event->type == GDK_BUTTON_PRESS))
    {
        gtk_menu_popup(menu, NULL, NULL, NULL, NULL, event->button, event->time);
        return TRUE;
    }
    return FALSE;
}

static void on_treeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, LkWindow *lkWindow)
{
    GtkTreeSelection *treeSelection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean selected;
    sqlite_int64 id;
    Lk *lk;
    GError *error = NULL;

    lk_clear(lkWindow);

    treeSelection = gtk_tree_view_get_selection(lkWindow->treeview);
    selected = gtk_tree_selection_get_selected(treeSelection, &model, &iter);
    if (selected)
    {
        gtk_tree_model_get (model, &iter, 0, &id, -1);
        lk = clksd_lkdb_find(id, &error);
        if (lk == NULL)
        {
            handle_error(lkWindow, error);
            return;
        }
        lk_show(lkWindow, lk);
    }
}

static void on_menuitem_about_clicked(GtkMenuItem *menuitem, LkWindow *lkWindow)
{
    clksd_aboutdialog_new();
}

static void on_menuitem_print_clicked(GtkMenuItem *menuitem, LkWindow *lkWindow)
{
    print(lkWindow);
}

static void on_menuitem_read_clicked(GtkMenuItem *menuitem, LkWindow *lkWindow)
{
    read(lkWindow);
}

void lkArrayIterator (gpointer data, gpointer user_data)
{
    Lk *lk = (Lk *)data;
    LkWindow *lkWindow = (LkWindow *)user_data;
    GtkListStore *liststore = lkWindow->liststore;
    GtkTreeIter iter;
    gtk_list_store_append (liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, lk->id, 1, lk->surname, 2, lk->givenName, -1);
}

LkWindow *clksd_lkwindow_new()
{
    /*Gtk staff*/
    GtkBuilder *builder;
    GError *error = NULL;
    GPtrArray *lkArray;

    LkWindow *lkWindow;

    lkWindow = (LkWindow *) g_malloc(sizeof (LkWindow));

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "glade/lkwindow.glade", &error))
    {
        g_error("%s", error->message);
    }

    lkWindow->lk = NULL;
    lkWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "lkwindow"));

    lkWindow->docRegNoTxt = GTK_LABEL(gtk_builder_get_object(builder, "DocRegNoTxt"));
    lkWindow->issuingDateTxt = GTK_LABEL(gtk_builder_get_object(builder, "IssuingDateTxt"));
    lkWindow->expiryDateTxt = GTK_LABEL(gtk_builder_get_object(builder, "ExpiryDateTxt"));
    lkWindow->issuingAuthorityTxt = GTK_LABEL(gtk_builder_get_object(builder, "IssuingAuthorityTxt"));

    lkWindow->personalNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "PersonalNumberTxt"));
    lkWindow->surnameTxt = GTK_LABEL(gtk_builder_get_object(builder, "SurnameTxt"));
    lkWindow->givenNameTxt = GTK_LABEL(gtk_builder_get_object(builder, "GivenNameTxt"));
    lkWindow->parentGivenNameTxt = GTK_LABEL(gtk_builder_get_object(builder, "ParentGivenNameTxt"));
    lkWindow->sexTxt = GTK_LABEL(gtk_builder_get_object(builder, "SexTxt"));
    lkWindow->placeOfBirthTxt = GTK_LABEL(gtk_builder_get_object(builder, "PlaceOfBirthTxt"));
    lkWindow->stateOfBirthTxt = GTK_LABEL(gtk_builder_get_object(builder, "StateOfBirthTxt"));
    lkWindow->dateOfBirthTxt = GTK_LABEL(gtk_builder_get_object(builder, "DateOfBirthTxt"));
    lkWindow->communityOfBirthTxt = GTK_LABEL(gtk_builder_get_object(builder, "CommunityOfBirthTxt"));

    lkWindow->stateTxt = GTK_LABEL(gtk_builder_get_object(builder, "StateTxt"));
    lkWindow->communityTxt = GTK_LABEL(gtk_builder_get_object(builder, "CommunityTxt"));
    lkWindow->placeTxt = GTK_LABEL(gtk_builder_get_object(builder, "PlaceTxt"));
    lkWindow->streetTxt = GTK_LABEL(gtk_builder_get_object(builder, "StreetTxt"));
    lkWindow->houseNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "HouseNumberTxt"));
    lkWindow->houseLetterTxt = GTK_LABEL(gtk_builder_get_object(builder, "HouseLetterTxt"));
    lkWindow->entranceTxt = GTK_LABEL(gtk_builder_get_object(builder, "EntranceTxt"));
    lkWindow->floorTxt = GTK_LABEL(gtk_builder_get_object(builder, "FloorTxt"));
    lkWindow->apartmentNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "ApartmentNumberTxt"));

    lkWindow->readToolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "readToolButton"));
    lkWindow->printToolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "printToolButton"));

    lkWindow->image = GTK_IMAGE(gtk_builder_get_object(builder, "image"));

    lkWindow->statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder, "statusbar"));

    lkWindow->treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview"));
    lkWindow->treeviewcolumn1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "treeviewcolumn1"));
    lkWindow->treeviewcolumn2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "treeviewcolumn2"));
    lkWindow->liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore"));

    lkWindow->popupmenu = GTK_MENU(gtk_builder_get_object(builder, "popupmenu"));
    lkWindow->menuitem_delete = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_delete"));
    lkWindow->menuitem_delete_all = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_delete_all"));
    lkWindow->menuitem_show = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_show"));

    lkWindow->menuitem_about = GTK_IMAGE_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_about"));
    lkWindow->menuitem_read = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_read"));
    lkWindow->menuitem_print = GTK_IMAGE_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_print"));
    lkWindow->menuitem_quit = GTK_IMAGE_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_quit"));

    g_signal_connect(G_OBJECT(lkWindow->window), "destroy", G_CALLBACK(on_window_destroy), (gpointer) lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->readToolButton), "clicked", G_CALLBACK(on_readtoolbutton_clicked), (gpointer) lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->printToolButton), "clicked", G_CALLBACK(on_printtoolbutton_clicked), (gpointer) lkWindow);

    g_signal_connect(G_OBJECT(lkWindow->treeview), "row_activated", G_CALLBACK(on_treeview_row_activated), lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->treeview), "button_press_event", G_CALLBACK(on_treeview_button_press), lkWindow->popupmenu);
    g_signal_connect(G_OBJECT(lkWindow->menuitem_delete), "activate", G_CALLBACK(on_menuitem_delete_clicked), lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->menuitem_delete_all), "activate", G_CALLBACK(on_menuitem_delete_all_clicked), lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->menuitem_show), "activate", G_CALLBACK(on_menuitem_show_clicked), lkWindow);

    gtk_menu_attach_to_widget(lkWindow->popupmenu, GTK_WIDGET(lkWindow->treeview), NULL);

    g_signal_connect(G_OBJECT(lkWindow->menuitem_about), "activate", G_CALLBACK(on_menuitem_about_clicked), lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->menuitem_read), "activate", G_CALLBACK(on_menuitem_read_clicked), lkWindow);
    g_signal_connect(G_OBJECT(lkWindow->menuitem_print), "activate", G_CALLBACK(on_menuitem_print_clicked), lkWindow);
    g_signal_connect_swapped(G_OBJECT(lkWindow->menuitem_quit), "activate", G_CALLBACK(gtk_widget_destroy), lkWindow->window);

    g_object_unref(G_OBJECT(builder));

    lkArray = clksd_lkdb_find_all(&error);
    if (lkArray == NULL)
    {
        handle_error(lkWindow, error);
        return NULL;
    }

    g_ptr_array_foreach (lkArray, lkArrayIterator, lkWindow);

    gtk_widget_show((GtkWidget *) lkWindow->window);

    return lkWindow;
}

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <winscard.h>
#include <eVehicleRegistrationAPI.h>
#include <gtk/gtk.h>
#include <string.h>
#include <setjmp.h>
#include <hpdf.h>
#include <sqlite3.h>
#include <glib/gi18n.h>
#include "sd.h"
#include "sdsc.h"
#include "sddb.h"
#include "sdprint.h"
#include "sdwindow.h"
#include "about.h"

#define STATUSBAR_TIMEOUT 3000

typedef struct statusbar_message
{
    GtkStatusbar *statusbar;
    guint context;
    guint message;
} StatusbarMessage;

static void on_window_destroy(GtkObject *object, SdWindow *sdWindow)
{
    g_debug("Destroying sdwindow...");
    clksd_sd_free(sdWindow->sd);
    g_free(sdWindow);
    g_debug("Destroying sdwindow done!");
}

void sd_clear(SdWindow *sdWindow)
{
    gtk_label_set_label(sdWindow->stateIssuingTxt, NULL);
    gtk_label_set_label(sdWindow->competentAuthorityTxt, NULL);
    gtk_label_set_label(sdWindow->authorityIssuingTxt, NULL);
    gtk_label_set_label(sdWindow->unambiguousNumberTxt, NULL);
    gtk_label_set_label(sdWindow->issuingDateTxt, NULL);
    gtk_label_set_label(sdWindow->expiryDateTxt, NULL);
    gtk_label_set_label(sdWindow->serialNumberTxt, NULL);

    gtk_label_set_label(sdWindow->dateOfFirstRegistrationTxt, NULL);
    gtk_label_set_label(sdWindow->yearOfProductionTxt, NULL);
    gtk_label_set_label(sdWindow->vehicleMakeTxt, NULL);
    gtk_label_set_label(sdWindow->vehicleTypeTxt, NULL);
    gtk_label_set_label(sdWindow->commercialDescriptionTxt, NULL);
    gtk_label_set_label(sdWindow->vehicleIDNumberTxt, NULL);
    gtk_label_set_label(sdWindow->registrationNumberOfVehicleTxt, NULL);
    gtk_label_set_label(sdWindow->maximumNetPowerTxt, NULL);
    gtk_label_set_label(sdWindow->engineCapacityTxt, NULL);
    gtk_label_set_label(sdWindow->typeOfFuelTxt, NULL);
    gtk_label_set_label(sdWindow->powerWeightRatioTxt, NULL);
    gtk_label_set_label(sdWindow->vehicleMassTxt, NULL);
    gtk_label_set_label(sdWindow->maximumPermissibleLadenMassTxt, NULL);
    gtk_label_set_label(sdWindow->typeApprovalNumberTxt, NULL);
    gtk_label_set_label(sdWindow->numberOfSeatsTxt, NULL);
    gtk_label_set_label(sdWindow->numberOfStandingPlacesTxt, NULL);
    gtk_label_set_label(sdWindow->engineIDNumberTxt, NULL);
    gtk_label_set_label(sdWindow->numberOfAxlesTxt, NULL);
    gtk_label_set_label(sdWindow->vehicleCategoryTxt, NULL);
    gtk_label_set_label(sdWindow->colourOfVehicleTxt, NULL);
    gtk_label_set_label(sdWindow->restrictionToChangeOwnerTxt, NULL);
    gtk_label_set_label(sdWindow->vehicleLoadTxt, NULL);

    gtk_label_set_label(sdWindow->ownersPersonalNoTxt, NULL);
    gtk_label_set_label(sdWindow->ownersSurnameOrBusinessNameTxt, NULL);
    gtk_label_set_label(sdWindow->ownerNameTxt, NULL);
    gtk_label_set_label(sdWindow->ownerAddressTxt, NULL);
    gtk_label_set_label(sdWindow->usersPersonalNoTxt, NULL);
    gtk_label_set_label(sdWindow->usersSurnameOrBusinessNameTxt, NULL);
    gtk_label_set_label(sdWindow->usersNameTxt, NULL);
    gtk_label_set_label(sdWindow->usersAddressTxt, NULL);

    gtk_widget_set_sensitive(GTK_WIDGET(sdWindow->printToolButton), FALSE);
    gtk_widget_set_sensitive(GTK_WIDGET(sdWindow->menuitem_print), FALSE);

}

static gboolean statusbar_clear (StatusbarMessage *statusbarMessage)
{
    gtk_statusbar_remove(statusbarMessage->statusbar, statusbarMessage->context, statusbarMessage->message);
    return FALSE;
}

static void handle_message(SdWindow *sdWindow, char *message)
{
    guint contextid;
    guint messageid;
    StatusbarMessage *statusbarMessage;

    contextid = gtk_statusbar_get_context_id(sdWindow->statusbar, "read");
    messageid = gtk_statusbar_push(sdWindow->statusbar, contextid, message);

    statusbarMessage = g_new0(StatusbarMessage, 1);
    statusbarMessage->statusbar = sdWindow->statusbar;
    statusbarMessage->context = contextid;
    statusbarMessage->message = messageid;

    g_timeout_add(STATUSBAR_TIMEOUT, (GSourceFunc) statusbar_clear, (gpointer)statusbarMessage);
}

static void handle_error(SdWindow *sdWindow, GError *error)
{
    guint contextid;
    guint messageid;
    StatusbarMessage *statusbarMessage;
    if (error != NULL)
    {
        g_debug("%s\n", error->message);

        contextid = gtk_statusbar_get_context_id(sdWindow->statusbar, "read");
        messageid = gtk_statusbar_push(sdWindow->statusbar, contextid, error->message);

        statusbarMessage = g_new0(StatusbarMessage, 1);
        statusbarMessage->statusbar = sdWindow->statusbar;
        statusbarMessage->context = contextid;
        statusbarMessage->message = messageid;

        g_timeout_add(STATUSBAR_TIMEOUT, (GSourceFunc) statusbar_clear, (gpointer)statusbarMessage);

        g_clear_error(&error);
    }
}

char *clksd_sdwindow_get_str(char *str, char *data, int size)
{
    strncpy(str, data, size);
    str[size] = '\0';
    return str;
}

static void sd_show (SdWindow *sdWindow, Sd *sd)
{

    sdWindow->sd = sd;

    gtk_label_set_label(sdWindow->stateIssuingTxt, sd->stateIssuing);
    gtk_label_set_label(sdWindow->competentAuthorityTxt, sd->competentAuthority);
    gtk_label_set_label(sdWindow->authorityIssuingTxt, sd->authorityIssuing);
    gtk_label_set_label(sdWindow->unambiguousNumberTxt, sd->unambiguousNumber);
    gtk_label_set_label(sdWindow->issuingDateTxt, sd->issuingDate);
    gtk_label_set_label(sdWindow->expiryDateTxt, sd->expiryDate);
    gtk_label_set_label(sdWindow->serialNumberTxt, sd->serialNumber);

    gtk_label_set_label(sdWindow->dateOfFirstRegistrationTxt, sd->dateOfFirstRegistration);
    gtk_label_set_label(sdWindow->yearOfProductionTxt, sd->yearOfProduction);
    gtk_label_set_label(sdWindow->vehicleMakeTxt, sd->vehicleMake);
    gtk_label_set_label(sdWindow->vehicleTypeTxt, sd->vehicleType);
    gtk_label_set_label(sdWindow->commercialDescriptionTxt, sd->commercialDescription);
    gtk_label_set_label(sdWindow->vehicleIDNumberTxt, sd->vehicleIDNumber);
    gtk_label_set_label(sdWindow->registrationNumberOfVehicleTxt, sd->registrationNumberOfVehicle);
    gtk_label_set_label(sdWindow->maximumNetPowerTxt, sd->maximumNetPower);
    gtk_label_set_label(sdWindow->engineCapacityTxt, sd->engineCapacity);
    gtk_label_set_label(sdWindow->typeOfFuelTxt, sd->typeOfFuel);
    gtk_label_set_label(sdWindow->powerWeightRatioTxt, sd->powerWeightRatio);
    gtk_label_set_label(sdWindow->vehicleMassTxt, sd->vehicleMass);
    gtk_label_set_label(sdWindow->maximumPermissibleLadenMassTxt, sd->maximumPermissibleLadenMass);
    gtk_label_set_label(sdWindow->typeApprovalNumberTxt, sd->typeApprovalNumber);
    gtk_label_set_label(sdWindow->numberOfSeatsTxt, sd->numberOfSeats);
    gtk_label_set_label(sdWindow->numberOfStandingPlacesTxt, sd->numberOfStandingPlaces);
    gtk_label_set_label(sdWindow->engineIDNumberTxt, sd->engineIDNumber);
    gtk_label_set_label(sdWindow->numberOfAxlesTxt, sd->numberOfAxles);
    gtk_label_set_label(sdWindow->vehicleCategoryTxt, sd->vehicleCategory);
    gtk_label_set_label(sdWindow->colourOfVehicleTxt, sd->colourOfVehicle);
    gtk_label_set_label(sdWindow->restrictionToChangeOwnerTxt, sd->restrictionToChangeOwner);
    gtk_label_set_label(sdWindow->vehicleLoadTxt, sd->vehicleLoad);

    gtk_label_set_label(sdWindow->ownersPersonalNoTxt, sd->ownersPersonalNo);
    gtk_label_set_label(sdWindow->ownersSurnameOrBusinessNameTxt, sd->ownersSurnameOrBusinessName);
    gtk_label_set_label(sdWindow->ownerNameTxt, sd->ownerName);
    gtk_label_set_label(sdWindow->ownerAddressTxt, sd->ownerAddress);
    gtk_label_set_label(sdWindow->usersPersonalNoTxt, sd->usersPersonalNo);
    gtk_label_set_label(sdWindow->usersSurnameOrBusinessNameTxt, sd->usersSurnameOrBusinessName);
    gtk_label_set_label(sdWindow->usersNameTxt, sd->usersName);
    gtk_label_set_label(sdWindow->usersAddressTxt, sd->usersAddress);

    gtk_widget_set_sensitive(GTK_WIDGET(sdWindow->printToolButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(sdWindow->menuitem_print), TRUE);

}

static void read (SdWindow *sdWindow)
{
    gboolean result;
    GError *error = NULL;
    Sd *sd;
    GtkListStore *liststore = sdWindow->liststore;
    GtkTreeIter iter;

    sd_clear(sdWindow);

    sd = clksd_sdsc_read(&error);
    if (sd == NULL)
    {
        handle_error(sdWindow, error);
        return;
    }

    sd_show(sdWindow, sd);

    result = clksd_sddb_insert(sd, &error);
    if (!result)
    {
        handle_error(sdWindow, error);
        return;
    }

    //add row to treeview
    gtk_list_store_append (liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, sd->id, 1, sd->registrationNumberOfVehicle, 2, sd->commercialDescription, -1);

    //activate print button
    gtk_widget_set_sensitive(GTK_WIDGET(sdWindow->printToolButton), TRUE);
    gtk_widget_set_sensitive(GTK_WIDGET(sdWindow->menuitem_print), TRUE);


    handle_message(sdWindow, _("Read OK"));

}

static void on_readtoolbutton_clicked(GtkObject *object, SdWindow *sdWindow)
{
    read (sdWindow);
}

static void print (SdWindow *sdWindow)
{
    GError *error = NULL;
    gchar *fname;
    gchar *fname1;
    gboolean result;
    g_debug("Start printing...");

    fname1 = g_strconcat(sdWindow->sd->registrationNumberOfVehicle, ".pdf", NULL);
    fname = g_build_filename(g_get_tmp_dir(), fname1, NULL);
    result = clksd_sdprint_print(sdWindow->sd, fname, &error);
    if (!result)
    {
        handle_error(sdWindow, error);
        return;
    }
    g_debug("Printing done!");

    ShellExecute(NULL, "open", fname, NULL, NULL, SW_SHOWNORMAL);
    g_free(fname);
    g_free(fname1);

    handle_message(sdWindow, _("Print OK"));
}

static void on_printtoolbutton_clicked(GtkObject *object, SdWindow *sdWindow)
{
    print(sdWindow);
}

static void on_menuitem_delete_clicked(GtkMenuItem *menuitem, SdWindow *sdWindow)
{
    GtkTreeSelection *treeSelection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean selected;
    sqlite_int64 id;
    GError *error = NULL;
    gboolean result;

    treeSelection = gtk_tree_view_get_selection(sdWindow->treeview);
    selected = gtk_tree_selection_get_selected(treeSelection, &model, &iter);
    if (selected)
    {
        gtk_tree_model_get (model, &iter, 0, &id, -1);
        result = clksd_sddb_delete(id, &error);
        if (!result)
        {
            handle_error(sdWindow, error);
            return;
        }
        gtk_list_store_remove(GTK_LIST_STORE(model), &iter);
    };

    handle_message(sdWindow, _("Delete OK"));
}

static void on_menuitem_delete_all_clicked(GtkMenuItem *menuitem, SdWindow *sdWindow)
{
    gboolean result;
    GError *error = NULL;

    result = clksd_sddb_delete_all(&error);
    if (!result)
    {
        handle_error(sdWindow, error);
        return;
    }
    gtk_list_store_clear(sdWindow->liststore);

    handle_message(sdWindow, _("Delete all OK"));
}

static void on_menuitem_show_clicked(GtkMenuItem *menuitem, SdWindow *sdWindow)
{
    GtkTreeSelection *treeSelection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean selected;
    sqlite_int64 id;
    Sd *sd;
    GError *error = NULL;

    sd_clear(sdWindow);

    treeSelection = gtk_tree_view_get_selection(sdWindow->treeview);
    selected = gtk_tree_selection_get_selected(treeSelection, &model, &iter);
    if (selected)
    {
        gtk_tree_model_get (model, &iter, 0, &id, -1);
        sd = clksd_sddb_find(id, &error);
        if (sd == NULL)
        {
            handle_error(sdWindow, error);
            return;
        }
        sd_show(sdWindow, sd);
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

static void on_treeview_row_activated(GtkTreeView *treeview, GtkTreePath *path, GtkTreeViewColumn *column, SdWindow *sdWindow)
{
    GtkTreeSelection *treeSelection;
    GtkTreeIter iter;
    GtkTreeModel *model;
    gboolean selected;
    sqlite_int64 id;
    Sd *sd;
    GError *error = NULL;

    sd_clear(sdWindow);

    treeSelection = gtk_tree_view_get_selection(sdWindow->treeview);
    selected = gtk_tree_selection_get_selected(treeSelection, &model, &iter);
    if (selected)
    {
        gtk_tree_model_get (model, &iter, 0, &id, -1);
        sd = clksd_sddb_find(id, &error);
        if (sd == NULL)
        {
            handle_error(sdWindow, error);
            return;
        }
        sd_show(sdWindow, sd);
    }
}

static void on_menuitem_about_clicked(GtkMenuItem *menuitem, SdWindow *sdWindow)
{
    clksd_aboutdialog_new();
}

static void on_menuitem_print_clicked(GtkMenuItem *menuitem, SdWindow *sdWindow)
{
    print(sdWindow);
}

static void on_menuitem_read_clicked(GtkMenuItem *menuitem, SdWindow *sdWindow)
{
    read(sdWindow);
}

void sdArrayIterator (gpointer data, gpointer user_data)
{
    Sd *sd = (Sd *)data;
    SdWindow *sdWindow = (SdWindow *)user_data;
    GtkListStore *liststore = sdWindow->liststore;
    GtkTreeIter iter;
    gtk_list_store_append (liststore, &iter);
    gtk_list_store_set(liststore, &iter, 0, sd->id, 1, sd->registrationNumberOfVehicle, 2, sd->commercialDescription, -1);
}

SdWindow *clksd_sdwindow_new()
{
    /*Gtk staff*/
    GtkBuilder *builder;
    GError *error = NULL;
    GPtrArray *sdArray;

    SdWindow *sdWindow;

    sdWindow = (SdWindow *) g_malloc(sizeof (SdWindow));

    builder = gtk_builder_new();
    if (!gtk_builder_add_from_file(builder, "glade/sdwindow.glade", &error))
    {
        g_error("%s", error->message);
    }

    sdWindow->sd = NULL;
    sdWindow->window = GTK_WINDOW(gtk_builder_get_object(builder, "sdwindow"));

    sdWindow->stateIssuingTxt = GTK_LABEL(gtk_builder_get_object(builder, "stateIssuingTxt"));
    sdWindow->competentAuthorityTxt = GTK_LABEL(gtk_builder_get_object(builder, "competentAuthorityTxt"));
    sdWindow->authorityIssuingTxt = GTK_LABEL(gtk_builder_get_object(builder, "authorityIssuingTxt"));
    sdWindow->unambiguousNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "unambiguousNumberTxt"));
    sdWindow->issuingDateTxt = GTK_LABEL(gtk_builder_get_object(builder, "issuingDateTxt"));
    sdWindow->expiryDateTxt = GTK_LABEL(gtk_builder_get_object(builder, "expiryDateTxt"));
    sdWindow->serialNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "serialNumberTxt"));

    sdWindow->dateOfFirstRegistrationTxt = GTK_LABEL(gtk_builder_get_object(builder, "dateOfFirstRegistrationTxt"));
    sdWindow->yearOfProductionTxt = GTK_LABEL(gtk_builder_get_object(builder, "yearOfProductionTxt"));
    sdWindow->vehicleMakeTxt = GTK_LABEL(gtk_builder_get_object(builder, "vehicleMakeTxt"));
    sdWindow->vehicleTypeTxt = GTK_LABEL(gtk_builder_get_object(builder, "vehicleTypeTxt"));
    sdWindow->commercialDescriptionTxt = GTK_LABEL(gtk_builder_get_object(builder, "commercialDescriptionTxt"));
    sdWindow->vehicleIDNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "vehicleIDNumberTxt"));
    sdWindow->registrationNumberOfVehicleTxt = GTK_LABEL(gtk_builder_get_object(builder, "registrationNumberOfVehicleTxt"));
    sdWindow->maximumNetPowerTxt = GTK_LABEL(gtk_builder_get_object(builder, "maximumNetPowerTxt"));
    sdWindow->engineCapacityTxt = GTK_LABEL(gtk_builder_get_object(builder, "engineCapacityTxt"));
    sdWindow->typeOfFuelTxt = GTK_LABEL(gtk_builder_get_object(builder, "typeOfFuelTxt"));
    sdWindow->powerWeightRatioTxt = GTK_LABEL(gtk_builder_get_object(builder, "powerWeightRatioTxt"));
    sdWindow->vehicleMassTxt = GTK_LABEL(gtk_builder_get_object(builder, "vehicleMassTxt"));
    sdWindow->maximumPermissibleLadenMassTxt = GTK_LABEL(gtk_builder_get_object(builder, "maximumPermissibleLadenMassTxt"));
    sdWindow->typeApprovalNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "typeApprovalNumberTxt"));
    sdWindow->numberOfSeatsTxt = GTK_LABEL(gtk_builder_get_object(builder, "numberOfSeatsTxt"));
    sdWindow->numberOfStandingPlacesTxt = GTK_LABEL(gtk_builder_get_object(builder, "numberOfStandingPlacesTxt"));
    sdWindow->engineIDNumberTxt = GTK_LABEL(gtk_builder_get_object(builder, "engineIDNumberTxt"));
    sdWindow->numberOfAxlesTxt = GTK_LABEL(gtk_builder_get_object(builder, "numberOfAxlesTxt"));
    sdWindow->vehicleCategoryTxt = GTK_LABEL(gtk_builder_get_object(builder, "vehicleCategoryTxt"));
    sdWindow->colourOfVehicleTxt = GTK_LABEL(gtk_builder_get_object(builder, "colourOfVehicleTxt"));
    sdWindow->restrictionToChangeOwnerTxt = GTK_LABEL(gtk_builder_get_object(builder, "restrictionToChangeOwnerTxt"));
    sdWindow->vehicleLoadTxt = GTK_LABEL(gtk_builder_get_object(builder, "vehicleLoadTxt"));

    sdWindow->ownersPersonalNoTxt = GTK_LABEL(gtk_builder_get_object(builder, "ownersPersonalNoTxt"));
    sdWindow->ownersSurnameOrBusinessNameTxt = GTK_LABEL(gtk_builder_get_object(builder, "ownersSurnameOrBusinessNameTxt"));
    sdWindow->ownerNameTxt = GTK_LABEL(gtk_builder_get_object(builder, "ownerNameTxt"));
    sdWindow->ownerAddressTxt = GTK_LABEL(gtk_builder_get_object(builder, "ownerAddressTxt"));
    sdWindow->usersPersonalNoTxt = GTK_LABEL(gtk_builder_get_object(builder, "usersPersonalNoTxt"));
    sdWindow->usersSurnameOrBusinessNameTxt = GTK_LABEL(gtk_builder_get_object(builder, "usersSurnameOrBusinessNameTxt"));
    sdWindow->usersNameTxt = GTK_LABEL(gtk_builder_get_object(builder, "usersNameTxt"));
    sdWindow->usersAddressTxt = GTK_LABEL(gtk_builder_get_object(builder, "usersAddressTxt"));

    sdWindow->readToolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "readToolButton"));
    sdWindow->printToolButton = GTK_TOOL_BUTTON(gtk_builder_get_object(builder, "printToolButton"));

    sdWindow->statusbar = GTK_STATUSBAR(gtk_builder_get_object(builder, "statusbar"));

    sdWindow->treeview = GTK_TREE_VIEW(gtk_builder_get_object(builder, "treeview"));
    sdWindow->treeviewcolumn1 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "treeviewcolumn1"));
    sdWindow->treeviewcolumn2 = GTK_TREE_VIEW_COLUMN(gtk_builder_get_object(builder, "treeviewcolumn2"));
    sdWindow->liststore = GTK_LIST_STORE(gtk_builder_get_object(builder, "liststore"));

    sdWindow->popupmenu = GTK_MENU(gtk_builder_get_object(builder, "popupmenu"));
    sdWindow->menuitem_delete = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_delete"));
    sdWindow->menuitem_delete_all = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_delete_all"));
    sdWindow->menuitem_show = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_show"));

    sdWindow->menuitem_about = GTK_IMAGE_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_about"));
    sdWindow->menuitem_read = GTK_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_read"));
    sdWindow->menuitem_print = GTK_IMAGE_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_print"));
    sdWindow->menuitem_quit = GTK_IMAGE_MENU_ITEM(gtk_builder_get_object(builder, "menuitem_quit"));

    g_signal_connect(G_OBJECT(sdWindow->window), "destroy", G_CALLBACK(on_window_destroy), (gpointer) sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->readToolButton), "clicked", G_CALLBACK(on_readtoolbutton_clicked), (gpointer) sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->printToolButton), "clicked", G_CALLBACK(on_printtoolbutton_clicked), (gpointer) sdWindow);

    g_signal_connect(G_OBJECT(sdWindow->treeview), "row_activated", G_CALLBACK(on_treeview_row_activated), sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->treeview), "button_press_event", G_CALLBACK(on_treeview_button_press), sdWindow->popupmenu);
    g_signal_connect(G_OBJECT(sdWindow->menuitem_delete), "activate", G_CALLBACK(on_menuitem_delete_clicked), sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->menuitem_delete_all), "activate", G_CALLBACK(on_menuitem_delete_all_clicked), sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->menuitem_show), "activate", G_CALLBACK(on_menuitem_show_clicked), sdWindow);

    gtk_menu_attach_to_widget(sdWindow->popupmenu, GTK_WIDGET(sdWindow->treeview), NULL);

    g_signal_connect(G_OBJECT(sdWindow->menuitem_about), "activate", G_CALLBACK(on_menuitem_about_clicked), sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->menuitem_read), "activate", G_CALLBACK(on_menuitem_read_clicked), sdWindow);
    g_signal_connect(G_OBJECT(sdWindow->menuitem_print), "activate", G_CALLBACK(on_menuitem_print_clicked), sdWindow);
    g_signal_connect_swapped(G_OBJECT(sdWindow->menuitem_quit), "activate", G_CALLBACK(gtk_widget_destroy), sdWindow->window);

    g_object_unref(G_OBJECT(builder));

    sdArray = clksd_sddb_find_all(&error);
    if (sdArray == NULL)
    {
        handle_error(sdWindow, error);
        return NULL;
    }

    g_ptr_array_foreach (sdArray, sdArrayIterator, sdWindow);

    gtk_widget_show((GtkWidget *) sdWindow->window);

    return sdWindow;
}

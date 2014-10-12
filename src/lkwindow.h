/*
 * File:   lkwindow.h
 * Author: dkozic
 *
 * Created on September 9, 2013, 6:34 PM
 */

#ifndef LKWINDOW_H
#define	LKWINDOW_H

#ifdef	__cplusplus
extern "C" {
#endif
typedef struct LkWindowTag LkWindow;

#include "sdwindow.h"

struct LkWindowTag
{
    GtkWindow *window;

    GtkLabel *docRegNoTxt;
    GtkLabel *issuingDateTxt;
    GtkLabel *expiryDateTxt;
    GtkLabel *issuingAuthorityTxt;

    GtkLabel *personalNumberTxt;
    GtkLabel *surnameTxt;
    GtkLabel *givenNameTxt;
    GtkLabel *parentGivenNameTxt;
    GtkLabel *sexTxt;
    GtkLabel *placeOfBirthTxt;
    GtkLabel *stateOfBirthTxt;
    GtkLabel *dateOfBirthTxt;
    GtkLabel *communityOfBirthTxt;

    GtkLabel *stateTxt;
    GtkLabel *communityTxt;
    GtkLabel *placeTxt;
    GtkLabel *streetTxt;
    GtkLabel *houseNumberTxt;
    GtkLabel *houseLetterTxt;
    GtkLabel *entranceTxt;
    GtkLabel *floorTxt;
    GtkLabel *apartmentNumberTxt;

    GtkImage *image;

    GtkToolButton *printToolButton;
    GtkToolButton *readToolButton;
    GtkToolButton *sdToolButton;

    GtkTreeView *treeview;
    GtkTreeViewColumn *treeviewcolumn1;
    GtkTreeViewColumn *treeviewcolumn2;
    GtkListStore *liststore;

    GtkMenu *popupmenu;
    GtkMenuItem *menuitem_delete;
    GtkMenuItem *menuitem_delete_all;
    GtkMenuItem *menuitem_show;

    GtkMenuItem *menuitem_read;
    GtkImageMenuItem *menuitem_print;
    GtkImageMenuItem *menuitem_quit;
    GtkImageMenuItem *menuitem_about;

    GtkStatusbar *statusbar;

    Lk *lk;

    SdWindow *sdWindow;

};

LkWindow *clksd_lkwindow_new();

#ifdef	__cplusplus
}
#endif

#endif	/* LKWINDOW_H */

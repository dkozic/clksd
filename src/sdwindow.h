/*
 * File:   sdwindow.h
 * Author: dkozic
 *
 * Created on September 9, 2013, 6:34 PM
 */

#ifndef SDWINDOW_H
#define	SDWINDOW_H

#ifdef	__cplusplus
extern "C" {
#endif

typedef struct SdWindowTag
{
    GtkWindow *window;

    GtkLabel *stateIssuingTxt;
    GtkLabel *competentAuthorityTxt;
    GtkLabel *authorityIssuingTxt;
    GtkLabel *unambiguousNumberTxt;
    GtkLabel *issuingDateTxt;
    GtkLabel *expiryDateTxt;
    GtkLabel *serialNumberTxt;

    GtkLabel *dateOfFirstRegistrationTxt;
    GtkLabel *yearOfProductionTxt;
    GtkLabel *vehicleMakeTxt;
    GtkLabel *vehicleTypeTxt;
    GtkLabel *commercialDescriptionTxt;
    GtkLabel *vehicleIDNumberTxt;
    GtkLabel *registrationNumberOfVehicleTxt;
    GtkLabel *maximumNetPowerTxt;
    GtkLabel *engineCapacityTxt;
    GtkLabel *typeOfFuelTxt;
    GtkLabel *powerWeightRatioTxt;
    GtkLabel *vehicleMassTxt;
    GtkLabel *maximumPermissibleLadenMassTxt;
    GtkLabel *typeApprovalNumberTxt;
    GtkLabel *numberOfSeatsTxt;
    GtkLabel *numberOfStandingPlacesTxt;
    GtkLabel *engineIDNumberTxt;
    GtkLabel *numberOfAxlesTxt;
    GtkLabel *vehicleCategoryTxt;
    GtkLabel *colourOfVehicleTxt;
    GtkLabel *restrictionToChangeOwnerTxt;
    GtkLabel *vehicleLoadTxt;

    GtkLabel *ownersPersonalNoTxt;
    GtkLabel *ownersSurnameOrBusinessNameTxt;
    GtkLabel *ownerNameTxt;
    GtkLabel *ownerAddressTxt;
    GtkLabel *usersPersonalNoTxt;
    GtkLabel *usersSurnameOrBusinessNameTxt;
    GtkLabel *usersNameTxt;
    GtkLabel *usersAddressTxt;

    GtkToolButton *printToolButton;
    GtkToolButton *readToolButton;

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

    Sd *sd;
} SdWindow;

SdWindow *clksd_sdwindow_new();

#ifdef	__cplusplus
}
#endif

#endif	/* SDWINDOW_H */

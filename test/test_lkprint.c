#include <glib.h>
#include <windows.h>
#include <sqlite3.h>
#include <CelikApi.h>
#include "../src/lk.h"
#include "test_lk.h"
#include "../src/lkprint.h"

#define TEST_STRING "test"

void clksd_lkprint_Test0(void)
{
    Lk *lk;
    char *fname = "test.pdf";
    GError *error = NULL;

    lk = clksd_lk_new();
    clksd_lk_set_docRegNo(lk, "docRegNo");
    clksd_lk_set_issuingDate(lk, "issuingDate");
    clksd_lk_set_expiryDate(lk, "expiryDate");
    clksd_lk_set_issuingAuthority(lk, "issuingAuthority");

    clksd_lk_set_personalNumber(lk, "personalNumber");
    clksd_lk_set_surname(lk, "surname");
    clksd_lk_set_givenName(lk, "givenName");
    clksd_lk_set_parentGivenName(lk, "parentGivenName");
    clksd_lk_set_sex(lk, "sex");
    clksd_lk_set_placeOfBirth(lk, "placeOfBirth");
    clksd_lk_set_stateOfBirth(lk, "stateOfBirth");
    clksd_lk_set_dateOfBirth(lk, "dateOfBirth");
    clksd_lk_set_communityOfBirth(lk, "communityOfBirth");
    clksd_lk_set_state(lk, "state");
    clksd_lk_set_community(lk, "community");
    clksd_lk_set_place(lk, "place");
    clksd_lk_set_street(lk, "street");
    clksd_lk_set_houseNumber(lk, "houseNumber");
    clksd_lk_set_houseLetter(lk, "houseLetter");
    clksd_lk_set_entrance(lk, "entrance");
    clksd_lk_set_floor(lk, "floor");
    clksd_lk_set_apartmentNumber(lk, "apartmentNumber");

    //clksd_lk_set_portrait(lk, bytes, 4);

    clksd_lkprint_print (lk, fname, &error);

    ShellExecute(NULL, "open", fname, NULL, NULL, SW_SHOWNORMAL);
}

#include <glib.h>
#include <windows.h>
#include <sqlite3.h>
#include <CelikApi.h>
#include "../src/lk.h"
#include "../src/lkdb.h"
#include "test_lkdb.h"

void clksd_lkdb_Test0(void)
{
    int c0, c1, c2, c3;
    gboolean result;
    Lk *lk;
    Lk *lk1;
    GPtrArray *lkArray;
    //GError *error;
    BYTE bytes[] = {0x01, 0x02, 0x03, 0x04};

    clksd_lkdb_delete_all(NULL);
    c0 = clksd_lkdb_count_all(NULL);
    g_assert_cmpint (c0, ==, 0);

    lkArray = clksd_lkdb_find_all(NULL);
    g_assert_cmpint (lkArray->len, ==, 0);
    g_ptr_array_free(lkArray, TRUE);

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

    clksd_lk_set_portrait(lk, bytes, 4);

    c1 = clksd_lkdb_count_all(NULL);
    g_assert_cmpint (c1, ==, 0);

    result = clksd_lkdb_insert(lk, NULL);
    g_assert(result);

    lkArray = clksd_lkdb_find_all(NULL);
    g_assert_cmpint (lkArray->len, ==, 1);
    g_ptr_array_free(lkArray, TRUE);

    lk1 = clksd_lkdb_find (lk->id, NULL);
    g_assert (lk1 != NULL);

    g_assert_cmpstr (lk1->docRegNo, ==, "docRegNo");
    g_assert_cmpstr (lk1->issuingDate, ==, "issuingDate");
    g_assert_cmpstr (lk1->expiryDate, ==, "expiryDate");
    g_assert_cmpstr (lk1->issuingAuthority, ==, "issuingAuthority");

    g_assert_cmpstr (lk1->personalNumber, ==, "personalNumber");
    g_assert_cmpstr (lk1->surname, ==, "surname");
    g_assert_cmpstr (lk1->givenName, ==, "givenName");
    g_assert_cmpstr (lk1->parentGivenName, ==, "parentGivenName");
    g_assert_cmpstr (lk1->sex, ==, "sex");
    g_assert_cmpstr (lk1->placeOfBirth, ==, "placeOfBirth");
    g_assert_cmpstr (lk1->stateOfBirth, ==, "stateOfBirth");
    g_assert_cmpstr (lk1->dateOfBirth, ==, "dateOfBirth");
    g_assert_cmpstr (lk1->communityOfBirth, ==, "communityOfBirth");
    g_assert_cmpstr (lk1->state, ==, "state");
    g_assert_cmpstr (lk1->place, ==, "place");
    g_assert_cmpstr (lk1->street, ==, "street");
    g_assert_cmpstr (lk1->houseNumber, ==, "houseNumber");
    g_assert_cmpstr (lk1->houseLetter, ==, "houseLetter");
    g_assert_cmpstr (lk1->entrance, ==, "entrance");
    g_assert_cmpstr (lk1->floor, ==, "floor");
    g_assert_cmpstr (lk1->docRegNo, ==, "docRegNo");
    g_assert_cmpstr (lk1->apartmentNumber, ==, "apartmentNumber");

    g_assert_cmpint (clksd_lk_get_portraitSize(lk), ==, 4);

    c2 = clksd_lkdb_count_all(NULL);
    g_assert_cmpint (c2, ==, 1);
    g_assert_cmpint (c2, ==, c1 + 1);

    result = clksd_lkdb_delete(lk->id, NULL);
    g_assert (result);

    c3 = clksd_lkdb_count_all(NULL);
    g_assert_cmpint (c3, ==, c2 - 1);


}

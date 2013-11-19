#include <glib.h>
#include <windows.h>
#include <sqlite3.h>
#include <CelikApi.h>
#include "../src/lk.h"
#include "test_lk.h"

#define TEST_STRING "test"

void clksd_lk_Test0(void)
{
    Lk *lk;
    lk = clksd_lk_new();
    clksd_lk_free(lk);
}

void clksd_lk_Test1(void)
{
    Lk *lk;
    BYTE bytes[] = {0x01, 0x02, 0x03};

    lk = clksd_lk_new();
    g_assert( lk != NULL);

    clksd_lk_set_docRegNo(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_docRegNo(lk), ==, TEST_STRING);

    clksd_lk_set_expiryDate(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_expiryDate(lk), ==, TEST_STRING);

    clksd_lk_set_issuingDate(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_issuingDate(lk), ==, TEST_STRING);

    clksd_lk_set_issuingAuthority(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_issuingAuthority(lk), ==, TEST_STRING);

    clksd_lk_set_personalNumber(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_personalNumber(lk), ==, TEST_STRING);

    clksd_lk_set_surname(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_surname(lk), ==, TEST_STRING);

    clksd_lk_set_givenName(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_givenName(lk), ==, TEST_STRING);

    clksd_lk_set_parentGivenName(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_parentGivenName(lk), ==, TEST_STRING);

    clksd_lk_set_sex(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_sex(lk), ==, TEST_STRING);

    clksd_lk_set_placeOfBirth(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_placeOfBirth(lk), ==, TEST_STRING);

    clksd_lk_set_stateOfBirth(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_stateOfBirth(lk), ==, TEST_STRING);

    clksd_lk_set_dateOfBirth(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_dateOfBirth(lk), ==, TEST_STRING);

    clksd_lk_set_communityOfBirth(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_communityOfBirth(lk), ==, TEST_STRING);

    clksd_lk_set_state(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_state(lk), ==, TEST_STRING);

    clksd_lk_set_community(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_community(lk), ==, TEST_STRING);

    clksd_lk_set_place(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_place(lk), ==, TEST_STRING);

    clksd_lk_set_street(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_street(lk), ==, TEST_STRING);

    clksd_lk_set_houseNumber(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_houseNumber(lk), ==, TEST_STRING);

    clksd_lk_set_houseLetter(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_houseLetter(lk), ==, TEST_STRING);

    clksd_lk_set_entrance(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_entrance(lk), ==, TEST_STRING);

    clksd_lk_set_floor(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_floor(lk), ==, TEST_STRING);

    clksd_lk_set_apartmentNumber(lk, TEST_STRING);
    g_assert_cmpstr (clksd_lk_get_apartmentNumber(lk), ==, TEST_STRING);

    clksd_lk_set_portrait(lk, bytes, 3);

    clksd_lk_free(lk);

}

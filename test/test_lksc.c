#include <glib.h>
#include <windows.h>
#include <sqlite3.h>
#include <CelikApi.h>
#include "../src/lk.h"
#include "../src/lksc.h"

static void array_copy (char *dest, char *src, int srcSize)
{
    int i;
    for (i = 0; i < srcSize; i++)
    {
        dest[i] = src[i];
    }
}

static void array_copy1 (BYTE *dest, BYTE *src, int srcSize)
{
    int i;
    for (i = 0; i < srcSize; i++)
    {
        dest[i] = src[i];
    }
}

void clksd_lksc_Test0(void)
{
    Lk *lk = NULL;
    EID_DOCUMENT_DATA dData;
    EID_FIXED_PERSONAL_DATA fpData;
    EID_VARIABLE_PERSONAL_DATA vpData;
    EID_PORTRAIT portrait;
    char test1[] = {'a'};
    char test2[] = {'b', 'b'};
    char test3[] = {'c', 'c', 'c'};
    char test4[] = {'d', 'd', 'd', 'd'};
    char test5[] = {'e', 'e', 'e', 'e', 'e'};
    char test6[] = {'f', 'f','f','f','f','f'};
    char test7[] = {'g', 'g','g','g','g','g','g'};
    char test8[] = {'h','h','h','h','h','h','h','h'};
    BYTE test[] = {0x01, 0x02, 0x03};

    array_copy(dData.docRegNo, test1, 1);
    dData.docRegNoSize = 1;

    array_copy(dData.expiryDate, test2, 2);
    dData.expiryDateSize = 2;

    array_copy(dData.issuingDate, test3, 3);
    dData.issuingDateSize = 3;

    array_copy(dData.issuingAuthority, test4, 4);
    dData.issuingAuthoritySize = 4;

    array_copy(fpData.personalNumber, test5, 5);
    fpData.personalNumberSize = 5;

    array_copy(fpData.surname, test6, 6);
    fpData.surnameSize = 6;

    array_copy(fpData.givenName, test7, 7);
    fpData.givenNameSize = 7;

    array_copy(fpData.parentGivenName, test8, 8);
    fpData.parentGivenNameSize = 8;

    array_copy(fpData.sex, test2, 2);
    fpData.sexSize = 2;

    array_copy(fpData.placeOfBirth, test1, 1);
    fpData.placeOfBirthSize = 1;

    array_copy(fpData.stateOfBirth, test2, 2);
    fpData.stateOfBirthSize = 2;

    array_copy(fpData.dateOfBirth, test3, 3);
    fpData.dateOfBirthSize = 3;

    array_copy(fpData.communityOfBirth, test4, 4);
    fpData.communityOfBirthSize = 4;

    array_copy(vpData.state, test3, 3);
    vpData.stateSize = 3;

    array_copy(vpData.community, test5, 5);
    vpData.communitySize = 5;

    array_copy(vpData.place, test6, 6);
    vpData.placeSize = 6;

    array_copy(vpData.street, test7, 7);
    vpData.streetSize = 7;

    array_copy(vpData.houseNumber, test5, 5);
    vpData.houseNumberSize = 5;

    array_copy(vpData.houseLetter, test2, 2);
    vpData.houseLetterSize = 2;

    array_copy(vpData.entrance, test1, 1);
    vpData.entranceSize = 1;

    array_copy(vpData.floor, test2, 2);
    vpData.floorSize = 2;

    array_copy(vpData.apartmentNumber, test3, 3);
    vpData.apartmentNumberSize = 3;

    array_copy1(portrait.portrait, test, 3);
    portrait.portraitSize = 3;

    lk = clksd_lksc_new_from_eid(&dData, &fpData, &vpData, &portrait);
    g_assert( lk != NULL);

    g_assert_cmpstr (clksd_lk_get_docRegNo(lk), ==, "a");
    g_assert_cmpstr (clksd_lk_get_expiryDate(lk), ==, "bb");
    g_assert_cmpstr (clksd_lk_get_issuingDate(lk), ==, "ccc");
    g_assert_cmpstr (clksd_lk_get_issuingAuthority(lk), ==, "dddd");

    g_assert_cmpstr (clksd_lk_get_personalNumber(lk), ==, "eeeee");
    g_assert_cmpstr (clksd_lk_get_surname(lk), ==, "ffffff");
    g_assert_cmpstr (clksd_lk_get_givenName(lk), ==, "ggggggg");
    g_assert_cmpstr (clksd_lk_get_parentGivenName(lk), ==, "hhhhhhhh");
    g_assert_cmpstr (clksd_lk_get_sex(lk), ==, "bb");
    g_assert_cmpstr (clksd_lk_get_placeOfBirth(lk), ==, "a");
    g_assert_cmpstr (clksd_lk_get_stateOfBirth(lk), ==, "bb");
    g_assert_cmpstr (clksd_lk_get_dateOfBirth(lk), ==, "ccc");
    g_assert_cmpstr (clksd_lk_get_communityOfBirth(lk), ==, "dddd");
    g_assert_cmpstr (clksd_lk_get_state(lk), ==, "ccc");
    g_assert_cmpstr (clksd_lk_get_community(lk), ==, "eeeee");
    g_assert_cmpstr (clksd_lk_get_place(lk), ==, "ffffff");
    g_assert_cmpstr (clksd_lk_get_street(lk), ==, "ggggggg");
    g_assert_cmpstr (clksd_lk_get_houseNumber(lk), ==, "eeeee");
    g_assert_cmpstr (clksd_lk_get_houseLetter(lk), ==, "bb");
    g_assert_cmpstr (clksd_lk_get_entrance(lk), ==, "a");
    g_assert_cmpstr (clksd_lk_get_floor(lk), ==, "bb");
    g_assert_cmpstr (clksd_lk_get_apartmentNumber(lk), ==, "ccc");

    g_assert_cmpint (clksd_lk_get_portraitSize(lk), ==, 3);


    clksd_lk_free(lk);

}

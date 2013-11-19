#include <glib.h>
#include <windows.h>
#include <CelikApi.h>
#include <sqlite3.h>
#include "lk.h"

Lk *clksd_lk_new()
{
    Lk *lk;
    lk = (Lk *) g_new0(Lk, 1);
    return lk;
}

void clksd_lk_free (Lk *lk)
{
    if(lk == NULL)
    {
        return;
    }
    g_free (lk->docRegNo);
    g_free (lk->issuingDate);
    g_free (lk->expiryDate);
    g_free (lk->issuingAuthority);
    g_free (lk->personalNumber);
    g_free (lk->surname);
    g_free (lk->givenName);
    g_free (lk->parentGivenName);
    g_free (lk->sex);
    g_free (lk->placeOfBirth);
    g_free (lk->stateOfBirth);
    g_free (lk->dateOfBirth);
    g_free (lk->communityOfBirth);
    g_free (lk->state);
    g_free (lk->community);
    g_free (lk->place);
    g_free (lk->street);
    g_free (lk->houseNumber);
    g_free (lk->houseLetter);
    g_free (lk->entrance);
    g_free (lk->floor);
    g_free (lk->apartmentNumber);
    g_free (lk->portrait);
    g_free (lk);
}

void clksd_lk_set_id (Lk *lk, sqlite3_int64 id)
{
    lk->id = id;
}

sqlite3_int64 clksd_lk_get_id (Lk *lk)
{
    return lk->id;
}

void clksd_lk_set_docRegNo (Lk *lk, gchar *docRegNo)
{
    lk->docRegNo = g_strdup (docRegNo);
}

gchar *clksd_lk_get_docRegNo (Lk *lk)
{
    return lk->docRegNo;
}

void clksd_lk_set_issuingDate (Lk *lk, gchar *issuingDate)
{
    lk->issuingDate = g_strdup (issuingDate);
}

gchar *clksd_lk_get_issuingDate (Lk *lk)
{
    return lk->issuingDate;
}

void clksd_lk_set_expiryDate (Lk *lk, gchar *expiryDate)
{
    lk->expiryDate = g_strdup (expiryDate);
}

gchar *clksd_lk_get_expiryDate (Lk *lk)
{
    return lk->expiryDate;
}

void clksd_lk_set_issuingAuthority (Lk *lk, gchar *issuingAuthority)
{
    lk->issuingAuthority = g_strdup (issuingAuthority);
}

gchar *clksd_lk_get_issuingAuthority (Lk *lk)
{
    return lk->issuingAuthority;
}

void clksd_lk_set_personalNumber (Lk *lk, gchar *personalNumber)
{
    lk->personalNumber = g_strdup (personalNumber);
}

gchar *clksd_lk_get_personalNumber (Lk *lk)
{
    return lk->personalNumber;
}

void clksd_lk_set_surname (Lk *lk, gchar *surname)
{
    lk->surname = g_strdup (surname);
}

gchar *clksd_lk_get_surname (Lk *lk)
{
    return lk->surname;
}

void clksd_lk_set_givenName (Lk *lk, gchar *givenName)
{
    lk->givenName = g_strdup (givenName);
}

gchar *clksd_lk_get_givenName (Lk *lk)
{
    return lk->givenName;
}

void clksd_lk_set_parentGivenName (Lk *lk, gchar *parentGivenName)
{
    lk->parentGivenName = g_strdup (parentGivenName);
}

gchar *clksd_lk_get_parentGivenName (Lk *lk)
{
    return lk->parentGivenName;
}

void clksd_lk_set_sex (Lk *lk, gchar *sex)
{
    lk->sex = g_strdup (sex);
}

gchar *clksd_lk_get_sex (Lk *lk)
{
    return lk->sex;
}

void clksd_lk_set_placeOfBirth (Lk *lk, gchar *placeOfBirth)
{
    lk->placeOfBirth = g_strdup (placeOfBirth);
}

gchar *clksd_lk_get_placeOfBirth (Lk *lk)
{
    return lk->placeOfBirth;
}

void clksd_lk_set_stateOfBirth (Lk *lk, gchar *stateOfBirth)
{
    lk->stateOfBirth = g_strdup (stateOfBirth);
}

gchar *clksd_lk_get_stateOfBirth (Lk *lk)
{
    return lk->stateOfBirth;
}

void clksd_lk_set_dateOfBirth (Lk *lk, gchar *dateOfBirth)
{
    lk->dateOfBirth = g_strdup (dateOfBirth);
}

gchar *clksd_lk_get_dateOfBirth (Lk *lk)
{
    return lk->dateOfBirth;
}

void clksd_lk_set_communityOfBirth (Lk *lk, gchar *communityOfBirth)
{
    lk->communityOfBirth = g_strdup (communityOfBirth);
}

gchar *clksd_lk_get_communityOfBirth (Lk *lk)
{
    return lk->communityOfBirth;
}

void clksd_lk_set_state (Lk *lk, gchar *state)
{
    lk->state = g_strdup (state);
}

gchar *clksd_lk_get_state (Lk *lk)
{
    return lk->state;
}

void clksd_lk_set_community (Lk *lk, gchar *community)
{
    lk->community = g_strdup (community);
}

gchar *clksd_lk_get_community (Lk *lk)
{
    return lk->community;
}

void clksd_lk_set_place (Lk *lk, gchar *place)
{
    lk->place = g_strdup (place);
}

gchar *clksd_lk_get_place (Lk *lk)
{
    return lk->place;
}

void clksd_lk_set_street (Lk *lk, gchar *street)
{
    lk->street = g_strdup (street);
}

gchar *clksd_lk_get_street (Lk *lk)
{
    return lk->street;
}

void clksd_lk_set_houseNumber (Lk *lk, gchar *houseNumber)
{
    lk->houseNumber = g_strdup (houseNumber);
}

gchar *clksd_lk_get_houseNumber (Lk *lk)
{
    return lk->houseNumber;
}

void clksd_lk_set_houseLetter (Lk *lk, gchar *houseLetter)
{
    lk->houseLetter = g_strdup (houseLetter);
}

gchar *clksd_lk_get_houseLetter (Lk *lk)
{
    return lk->houseLetter;
}

void clksd_lk_set_entrance (Lk *lk, gchar *entrance)
{
    lk->entrance = g_strdup (entrance);
}

gchar *clksd_lk_get_entrance (Lk *lk)
{
    return lk->entrance;
}

void clksd_lk_set_floor (Lk *lk, gchar *floor)
{
    lk->floor = g_strdup (floor);
}

gchar *clksd_lk_get_floor (Lk *lk)
{
    return lk->floor;
}

void clksd_lk_set_apartmentNumber (Lk *lk, gchar *apartmentNumber)
{
    lk->apartmentNumber = g_strdup (apartmentNumber);
}

gchar *clksd_lk_get_apartmentNumber (Lk *lk)
{
    return lk->apartmentNumber;
}

void clksd_lk_set_portrait (Lk *lk, BYTE *portrait, int portraitSize)
{
    int i;
    lk->portrait = g_new0 (BYTE, portraitSize);

    for (i = 0; i < portraitSize; i++)
    {
        lk->portrait[i] = portrait[i];
    }
    lk->portraitSize = portraitSize;
}

BYTE *clksd_lk_get_portrait (Lk *lk)
{
    return lk->portrait;
}

gint clksd_lk_get_portraitSize (Lk *lk)
{
    return lk->portraitSize;
}

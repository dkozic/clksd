/*
 * File:   lk.h
 * Author: dkozic
 *
 * Created on October 4, 2013, 9:50 PM
 */

#ifndef LK_H
#define	LK_H

typedef struct LkTag
{
    sqlite3_int64 id;
    gchar *docRegNo;
    gchar *issuingDate;
    gchar *expiryDate;
    gchar *issuingAuthority;

    gchar *personalNumber;
    gchar *surname;
    gchar *givenName;
    gchar *parentGivenName;
    gchar *sex;
    gchar *placeOfBirth;
    gchar *stateOfBirth;
    gchar *dateOfBirth;
    gchar *communityOfBirth;

    gchar *state;
    gchar *community;
    gchar *place;
    gchar *street;
    gchar *houseNumber;
    gchar *houseLetter;
    gchar *entrance;
    gchar *floor;
    gchar *apartmentNumber;

    BYTE *portrait;
    gint portraitSize;

} Lk;

Lk *clksd_lk_new();
void clksd_lk_free (Lk *lk);

void clksd_lk_set_id (Lk *lk, sqlite3_int64 id);
sqlite3_int64 clksd_lk_get_id (Lk *lk);

void clksd_lk_set_docRegNo (Lk *lk, gchar *docRegNo);
gchar *clksd_lk_get_docRegNo (Lk *lk);

void clksd_lk_set_issuingDate (Lk *lk, gchar *issuingDate);
gchar *clksd_lk_get_issuingDate (Lk *lk);

void clksd_lk_set_expiryDate (Lk *lk, gchar *expiryDate);
gchar *clksd_lk_get_expiryDate (Lk *lk);

void clksd_lk_set_issuingAuthority (Lk *lk, gchar *issuingAuthority);
gchar *clksd_lk_get_issuingAuthority (Lk *lk);

void clksd_lk_set_personalNumber (Lk *lk, gchar *personalNumber);
gchar *clksd_lk_get_personalNumber (Lk *lk);

void clksd_lk_set_surname (Lk *lk, gchar *surname);
gchar *clksd_lk_get_surname (Lk *lk);

void clksd_lk_set_givenName (Lk *lk, gchar *givenName);
gchar *clksd_lk_get_givenName (Lk *lk);

void clksd_lk_set_parentGivenName (Lk *lk, gchar *parentGivenName);
gchar *clksd_lk_get_parentGivenName (Lk *lk);

void clksd_lk_set_sex (Lk *lk, gchar *sex);
gchar *clksd_lk_get_sex (Lk *lk);

void clksd_lk_set_placeOfBirth (Lk *lk, gchar *placeOfBirth);
gchar *clksd_lk_get_placeOfBirth (Lk *lk);

void clksd_lk_set_stateOfBirth (Lk *lk, gchar *stateOfBirth);
gchar *clksd_lk_get_stateOfBirth (Lk *lk);

void clksd_lk_set_dateOfBirth (Lk *lk, gchar *dateOfBirth);
gchar *clksd_lk_get_dateOfBirth (Lk *lk);

void clksd_lk_set_communityOfBirth (Lk *lk, gchar *communityOfBirth);
gchar *clksd_lk_get_communityOfBirth (Lk *lk);

void clksd_lk_set_state (Lk *lk, gchar *state);
gchar *clksd_lk_get_state (Lk *lk);

void clksd_lk_set_community (Lk *lk, gchar *community);
gchar *clksd_lk_get_community (Lk *lk);

void clksd_lk_set_place (Lk *lk, gchar *place);
gchar *clksd_lk_get_place (Lk *lk);

void clksd_lk_set_street (Lk *lk, gchar *street);
gchar *clksd_lk_get_street (Lk *lk);

void clksd_lk_set_houseNumber (Lk *lk, gchar *houseNumber);
gchar *clksd_lk_get_houseNumber (Lk *lk);

void clksd_lk_set_houseLetter (Lk *lk, gchar *houseLetter);
gchar *clksd_lk_get_houseLetter (Lk *lk);

void clksd_lk_set_entrance (Lk *lk, gchar *entrance);
gchar *clksd_lk_get_entrance (Lk *lk);

void clksd_lk_set_floor (Lk *lk, gchar *floor);
gchar *clksd_lk_get_floor (Lk *lk);

void clksd_lk_set_apartmentNumber (Lk *lk, gchar *apartmentNumber);
gchar *clksd_lk_get_apartmentNumber (Lk *lk);

void clksd_lk_set_portrait (Lk *lk, BYTE *portrait, int portraitSize);
BYTE *clksd_lk_get_portrait (Lk *lk);
gint clksd_lk_get_portraitSize (Lk *lk);

#endif	/* LK_H */

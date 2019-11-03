#include <glib.h>
#include <windows.h>
#include <CelikApi.h>
#include <sqlite3.h>
#include "lk.h"
#include "lksc.h"

GQuark clksd_lksc_error_quark()
{
    static GQuark q = 0;
    if (q == 0)
    {
        q = g_quark_from_static_string("clksd-lksc-error");
    }
    return q;
}

static char *eid_message(int error)
{
    char *errorMessage;

    switch (error)
    {
    case EID_E_GENERAL_ERROR:
        errorMessage = "GeneralError";
        break;
    case EID_E_INVALID_PARAMETER:
        errorMessage = "InvalidParameter";
        break;
    case EID_E_VERSION_NOT_SUPPORTED:
        errorMessage = "VersionNotSupported";
        break;
    case EID_E_NOT_INITIALIZED:
        errorMessage = "NotInitialized";
        break;
    case EID_E_UNABLE_TO_EXECUTE:
        errorMessage = "UnableToExecute";
        break;
    case EID_E_READER_ERROR:
        errorMessage = "ReaderError";
        break;
    case EID_E_CARD_MISSING:
        errorMessage = "CardMissing";
        break;
    case EID_E_CARD_UNKNOWN:
        errorMessage = "CardUnknown";
        break;
    case EID_E_CARD_MISMATCH:
        errorMessage = "CardMismatch";
        break;
    case EID_E_UNABLE_TO_OPEN_SESSION:
        errorMessage = "UnableToOpenSession";
        break;
    case EID_E_DATA_MISSING:
        errorMessage = "DataMissing";
        break;
    case EID_E_CARD_SECFORMAT_CHECK_ERROR:
        errorMessage = "CardSecFormatCheckError";
        break;
    case EID_E_SECFORMAT_CHECK_CERT_ERROR:
        errorMessage = "SecformatCheckCertError";
        break;
    default:
        errorMessage = "UnknownError";
    }
    return errorMessage;
}

static char *eid_str(char *str, char *data, int size)
{
    strncpy(str, data, size);
    str[size] = '\0';
    return str;
}

Lk *clksd_lksc_new_from_eid(EID_DOCUMENT_DATA *dData, EID_FIXED_PERSONAL_DATA *fpData, EID_VARIABLE_PERSONAL_DATA *vpData, EID_PORTRAIT *portrait)
{
    Lk *lk;
    gchar buffer[200];

    lk = clksd_lk_new();

    clksd_lk_set_docRegNo(lk, eid_str(buffer, dData->docRegNo, dData->docRegNoSize));
    clksd_lk_set_issuingDate(lk, eid_str(buffer, dData->issuingDate, dData->issuingDateSize));
    clksd_lk_set_expiryDate(lk, eid_str(buffer, dData->expiryDate, dData->expiryDateSize));
    clksd_lk_set_issuingAuthority(lk, eid_str(buffer, dData->issuingAuthority, dData->issuingAuthoritySize));

    clksd_lk_set_personalNumber(lk, eid_str(buffer, fpData->personalNumber, fpData->personalNumberSize));
    clksd_lk_set_surname(lk, eid_str(buffer, fpData->surname, fpData->surnameSize));
    clksd_lk_set_givenName(lk, eid_str(buffer, fpData->givenName, fpData->givenNameSize));
    clksd_lk_set_parentGivenName(lk, eid_str(buffer, fpData->parentGivenName, fpData->parentGivenNameSize));
    clksd_lk_set_sex(lk, eid_str(buffer, fpData->sex, fpData->sexSize));
    clksd_lk_set_placeOfBirth(lk, eid_str(buffer, fpData->placeOfBirth, fpData->placeOfBirthSize));
    clksd_lk_set_stateOfBirth(lk, eid_str(buffer, fpData->stateOfBirth, fpData->stateOfBirthSize));
    clksd_lk_set_dateOfBirth(lk, eid_str(buffer, fpData->dateOfBirth, fpData->dateOfBirthSize));
    clksd_lk_set_communityOfBirth(lk, eid_str(buffer, fpData->communityOfBirth, fpData->communityOfBirthSize));

    clksd_lk_set_state(lk, eid_str(buffer, vpData->state, vpData->stateSize));
    clksd_lk_set_community(lk, eid_str(buffer, vpData->community, vpData->communitySize));
    clksd_lk_set_place(lk, eid_str(buffer, vpData->place, vpData->placeSize));
    clksd_lk_set_street(lk, eid_str(buffer, vpData->street, vpData->streetSize));
    clksd_lk_set_houseNumber(lk, eid_str(buffer, vpData->houseNumber, vpData->houseNumberSize));
    clksd_lk_set_houseLetter(lk, eid_str(buffer, vpData->houseLetter, vpData->houseLetterSize));
    clksd_lk_set_entrance(lk, eid_str(buffer, vpData->entrance, vpData->entranceSize));
    clksd_lk_set_floor(lk, eid_str(buffer, vpData->floor, vpData->floorSize));
    clksd_lk_set_apartmentNumber(lk, eid_str(buffer, vpData->apartmentNumber, vpData->apartmentNumberSize));

    clksd_lk_set_portrait(lk, portrait->portrait, portrait->portraitSize);

    return lk;
}

Lk *clksd_lksc_read_eid(GError **error)
{
    EID_DOCUMENT_DATA dData;
    EID_FIXED_PERSONAL_DATA fpData;
    EID_VARIABLE_PERSONAL_DATA vpData;
    EID_PORTRAIT pData;
    Lk *lk = NULL;
    int result;

    result = EidStartup(2);
    if (result != EID_OK)
    {
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_STARTUP, "Can't startup: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    int pnCardVersion;
    result = EidBeginRead("", &pnCardVersion);
    if (result != EID_OK)
    {
        EidCleanup();
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_BEGIN_READ, "Can't begin read: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    result = EidReadDocumentData(&dData);
    if (result != EID_OK)
    {
        EidEndRead();
        EidCleanup();
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_READ_DOCUMENT_DATA, "Can't read document data: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    result = EidReadFixedPersonalData(&fpData);
    if (result != EID_OK)
    {
        EidEndRead();
        EidCleanup();
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_READ_FIXED_PERSONAL_DATA, "Can't read fixed personal data: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    result = EidReadVariablePersonalData(&vpData);
    if (result != EID_OK)
    {
        EidEndRead();
        EidCleanup();
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_READ_VARIABLE_PERSONAL_DATA, "Can't read variable personal data: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    result = EidReadPortrait(&pData);
    if (result != EID_OK)
    {
        EidEndRead();
        EidCleanup();
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_READ_PORTRAIT, "Can't read fixed portrait: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    result = EidEndRead();
    if (result!= EID_OK)
    {
        EidCleanup();
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_END_READ, "Can't end read: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    result = EidCleanup();
    if (result != EID_OK)
    {
        g_set_error(error, CLKSD_LKSC_ERROR ,CLKSD_LKSC_ERROR_CLEANUP, "Can't cleanup: errcode: %d, errmsg: %s", result, eid_message(result));
        return lk;
    }

    lk = clksd_lksc_new_from_eid(&dData, &fpData, &vpData, &pData);
    return lk;
}

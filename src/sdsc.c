#include <glib.h>
#include <windows.h>
#include <sqlite3.h>
#include <eVehicleRegistrationAPI.h>
#include "sd.h"
#include "sdsc.h"

GQuark clksd_sdsc_error_quark()
{
    static GQuark q = 0;
    if (q == 0)
    {
        q = g_quark_from_static_string("clksd-sdsc-error");
    }
    return q;
}

static char *esd_message(long error)
{
    char *errorMessage;

    switch (error)
    {
    case ERROR_BAD_FORMAT:
        errorMessage = "ErrorBadFormat";
        break;
    case ERROR_INVALID_ACCESS:
        errorMessage = "ErrorInvalidAccess";
        break;
    case ERROR_INVALID_DATA:
        errorMessage = "ErrorInvalidData";
        break;
    case ERROR_INVALID_PARAMETER:
        errorMessage = "ErrorInvalidParameter";
        break;
    case ERROR_SERVICE_ALREADY_RUNNING:
        errorMessage = "ErrorServiceAlreadyRunning";
        break;
    case ERROR_SERVICE_NOT_ACTIVE:
        errorMessage = "ErrorServiceNotActive";
        break;
    case E_POINTER:
        errorMessage = "EPointer";
        break;
    case SCARD_E_INSUFFICIENT_BUFFER:
        errorMessage = "ScardEInsufficientBuffer";
        break;
    case SCARD_E_UNKNOWN_READER:
        errorMessage = "ScardEUnknownReader";
        break;
    case SCARD_E_NO_SMARTCARD:
        errorMessage = "ScardENoSmartcard";
        break;
    case SCARD_E_INVALID_VALUE:
        errorMessage = "ScardEInvalidValue";
        break;
    case SCARD_E_READER_UNAVAILABLE:
        errorMessage = "ScardEReaderUnavailable";
        break;
    case SCARD_E_CARD_UNSUPPORTED:
        errorMessage = "ScardECardUnsupported";
        break;
    case SCARD_E_NO_READERS_AVAILABLE:
        errorMessage = "ScardENoReadersAvailable";
        break;
    default:
        errorMessage = "UnknownError";
    }

    return errorMessage;
}

Sd *clksd_sdsc_new_from_esd(SD_DOCUMENT_DATA *dData, SD_VEHICLE_DATA *vData, SD_PERSONAL_DATA *pData)
{
    Sd *sd;

    sd = clksd_sd_new();

    clksd_sd_set_stateIssuing(sd, dData->stateIssuing);
    clksd_sd_set_competentAuthority(sd, dData->competentAuthority);
    clksd_sd_set_authorityIssuing(sd, dData->authorityIssuing);
    clksd_sd_set_unambiguousNumber(sd, dData->unambiguousNumber);
    clksd_sd_set_issuingDate(sd, dData->issuingDate);
    clksd_sd_set_expiryDate(sd, dData->expiryDate);
    clksd_sd_set_serialNumber(sd, dData->serialNumber);

    clksd_sd_set_dateOfFirstRegistration(sd, vData->dateOfFirstRegistration);
    clksd_sd_set_yearOfProduction(sd, vData->yearOfProduction);
    clksd_sd_set_vehicleMake(sd, vData->vehicleMake);
    clksd_sd_set_vehicleType(sd, vData->vehicleType);
    clksd_sd_set_commercialDescription(sd, vData->commercialDescription);
    clksd_sd_set_vehicleIDNumber(sd, vData->vehicleIDNumber);
    clksd_sd_set_registrationNumberOfVehicle(sd, vData->registrationNumberOfVehicle);
    clksd_sd_set_maximumNetPower(sd, vData->maximumNetPower);
    clksd_sd_set_engineCapacity(sd, vData->engineCapacity);
    clksd_sd_set_typeOfFuel(sd, vData->typeOfFuel);
    clksd_sd_set_powerWeightRatio(sd, vData->powerWeightRatio);
    clksd_sd_set_vehicleMass(sd, vData->vehicleMass);
    clksd_sd_set_maximumPermissibleLadenMass(sd, vData->maximumPermissibleLadenMass);
    clksd_sd_set_typeApprovalNumber(sd, vData->typeApprovalNumber);
    clksd_sd_set_numberOfSeats(sd, vData->numberOfSeats);
    clksd_sd_set_numberOfStandingPlaces(sd, vData->numberOfStandingPlaces);
    clksd_sd_set_engineIDNumber(sd, vData->engineIDNumber);
    clksd_sd_set_numberOfAxles(sd, vData->numberOfAxles);
    clksd_sd_set_vehicleCategory(sd, vData->vehicleCategory);
    clksd_sd_set_colourOfVehicle(sd, vData->colourOfVehicle);
    clksd_sd_set_restrictionToChangeOwner(sd, vData->restrictionToChangeOwner);
    clksd_sd_set_vehicleLoad(sd, vData->vehicleLoad);

    clksd_sd_set_ownersPersonalNo(sd, pData->ownersPersonalNo);
    clksd_sd_set_ownersSurnameOrBusinessName(sd, pData->ownersSurnameOrBusinessName);
    clksd_sd_set_ownerName(sd, pData->ownerName);
    clksd_sd_set_ownerAddress(sd, pData->ownerAddress);
    clksd_sd_set_usersPersonalNo(sd, pData->usersPersonalNo);
    clksd_sd_set_usersSurnameOrBusinessName(sd, pData->usersSurnameOrBusinessName);
    clksd_sd_set_usersName(sd, pData->usersName);
    clksd_sd_set_usersAddress(sd, pData->usersAddress);

    return sd;
}

Sd *clksd_sdsc_read(GError **error)
{
    Sd *sd = NULL;
    SD_DOCUMENT_DATA dData;
    SD_VEHICLE_DATA vData;
    SD_PERSONAL_DATA pData;
    long result;
    char readerName[100];
    long readerNameSize = 100;


    result = sdStartup(1);
    if (result != S_OK)
    {
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_STARTUP, "Can't startup: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    result = GetReaderName(0L, readerName, &readerNameSize);
    if (result != S_OK)
    {
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_GET_READER_NAME, "Can't get reader name: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    result = SelectReader(readerName);
    if (result != S_OK)
    {
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_SELECT_READER, "Can't select reader: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    result = sdProcessNewCard();
    if (result != S_OK)
    {
        sdCleanup();
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_PROCESS_NEW_CARD, "Can't process new card: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }


    result = sdReadDocumentData(&dData);
    if (result != S_OK)
    {
        sdCleanup();
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_READ_DOCUMENT_DATA, "Can't read document data: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    result = sdReadVehicleData(&vData);
    if (result != S_OK)
    {
        sdCleanup();
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_READ_VEHICLE_DATA, "Can't read vehicle data: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    result = sdReadPersonalData(&pData);
    if (result != S_OK)
    {
        sdCleanup();
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_READ_PERSONAL_DATA, "Can't read personal data: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    result = sdCleanup();
    if (result != S_OK)
    {
        g_set_error(error, CLKSD_SDSC_ERROR ,CLKSD_SDSC_ERROR_CLEANUP, "Can't cleanup: errcode: %lu, errmsg: %s", result, esd_message(result));
        return sd;
    }

    sd = clksd_sdsc_new_from_esd(&dData, &vData, &pData);

    return sd;
}

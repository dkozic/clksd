#include <glib.h>
#include <windows.h>
#include <CelikApi.h>
#include <sqlite3.h>
#include "sd.h"

Sd *clksd_sd_new()
{
    Sd *sd;
    sd = (Sd *) g_new0(Sd, 1);
    return sd;
}

void clksd_sd_free (Sd *sd)
{
    if(sd == NULL)
    {
        return;
    }
    g_free (sd->stateIssuing);
    g_free (sd->competentAuthority);
    g_free (sd->authorityIssuing);
    g_free (sd->unambiguousNumber);
    g_free (sd->issuingDate);
    g_free (sd->expiryDate);
    g_free (sd->serialNumber);

    g_free (sd->dateOfFirstRegistration);
    g_free (sd->yearOfProduction);
    g_free (sd->vehicleMake);
    g_free (sd->vehicleType);
    g_free (sd->commercialDescription);
    g_free (sd->vehicleIDNumber);
    g_free (sd->registrationNumberOfVehicle);
    g_free (sd->maximumNetPower);
    g_free (sd->engineCapacity);
    g_free (sd->typeOfFuel);
    g_free (sd->powerWeightRatio);
    g_free (sd->vehicleMass);
    g_free (sd->maximumPermissibleLadenMass);
    g_free (sd->typeApprovalNumber);
    g_free (sd->numberOfSeats);
    g_free (sd->numberOfStandingPlaces);
    g_free (sd->engineIDNumber);
    g_free (sd->numberOfAxles);
    g_free (sd->vehicleCategory);
    g_free (sd->colourOfVehicle);
    g_free (sd->restrictionToChangeOwner);
    g_free (sd->vehicleLoad);

    g_free (sd->ownersPersonalNo);
    g_free (sd->ownersSurnameOrBusinessName);
    g_free (sd->ownerName);
    g_free (sd->ownerAddress);
    g_free (sd->usersPersonalNo);
    g_free (sd->usersSurnameOrBusinessName);
    g_free (sd->usersName);
    g_free (sd->usersAddress);

    g_free (sd);
}

void clksd_sd_set_id (Sd *sd, sqlite3_int64 id)
{
    sd->id = id;
}

sqlite3_int64 clksd_sd_get_id (Sd *sd)
{
    return sd->id;
}

void clksd_sd_set_stateIssuing (Sd *sd, gchar *stateIssuing)
{
    sd->stateIssuing = g_strdup (stateIssuing);
}

gchar *clksd_sd_get_stateIssuing (Sd *sd)
{
    return sd->stateIssuing;
}

void clksd_sd_set_competentAuthority (Sd *sd, gchar *competentAuthority)
{
    sd->competentAuthority = g_strdup (competentAuthority);
}

gchar *clksd_sd_get_competentAuthority (Sd *sd)
{
    return sd->competentAuthority;
}

void clksd_sd_set_authorityIssuing (Sd *sd, gchar *authorityIssuing)
{
    sd->authorityIssuing = g_strdup (authorityIssuing);
}

gchar *clksd_sd_get_authorityIssuing (Sd *sd)
{
    return sd->authorityIssuing;
}

void clksd_sd_set_unambiguousNumber (Sd *sd, gchar *unambiguousNumber)
{
    sd->unambiguousNumber = g_strdup (unambiguousNumber);
}

gchar *clksd_sd_get_unambiguousNumber (Sd *sd)
{
    return sd->unambiguousNumber;
}

void clksd_sd_set_issuingDate (Sd *sd, gchar *issuingDate)
{
    sd->issuingDate = g_strdup (issuingDate);
}

gchar *clksd_sd_get_issuingDate (Sd *sd)
{
    return sd->issuingDate;
}

void clksd_sd_set_expiryDate (Sd *sd, gchar *expiryDate)
{
    sd->expiryDate = g_strdup (expiryDate);
}

gchar *clksd_sd_get_expiryDate (Sd *sd)
{
    return sd->expiryDate;
}

void clksd_sd_set_serialNumber (Sd *sd, gchar *serialNumber)
{
    sd->serialNumber = g_strdup (serialNumber);
}

gchar *clksd_sd_get_serialNumber (Sd *sd)
{
    return sd->serialNumber;
}

void clksd_sd_set_dateOfFirstRegistration (Sd *sd, gchar *dateOfFirstRegistration)
{
    sd->dateOfFirstRegistration = g_strdup (dateOfFirstRegistration);
}

gchar *clksd_sd_get_dateOfFirstRegistration (Sd *sd)
{
    return sd->dateOfFirstRegistration;
}

void clksd_sd_set_yearOfProduction (Sd *sd, gchar *yearOfProduction)
{
    sd->yearOfProduction = g_strdup (yearOfProduction);
}

gchar *clksd_sd_get_yearOfProduction (Sd *sd)
{
    return sd->yearOfProduction;
}

void clksd_sd_set_vehicleMake (Sd *sd, gchar *vehicleMake)
{
    sd->vehicleMake = g_strdup (vehicleMake);
}

gchar *clksd_sd_get_vehicleMake (Sd *sd)
{
    return sd->vehicleMake;
}

void clksd_sd_set_vehicleType (Sd *sd, gchar *vehicleType)
{
    sd->vehicleType = g_strdup (vehicleType);
}

gchar *clksd_sd_get_vehicleType (Sd *sd)
{
    return sd->vehicleType;
}

void clksd_sd_set_commercialDescription (Sd *sd, gchar *commercialDescription)
{
    sd->commercialDescription = g_strdup (commercialDescription);
}

gchar *clksd_sd_get_commercialDescription (Sd *sd)
{
    return sd->commercialDescription;
}

void clksd_sd_set_vehicleIDNumber (Sd *sd, gchar *vehicleIDNumber)
{
    sd->vehicleIDNumber = g_strdup (vehicleIDNumber);
}

gchar *clksd_sd_get_vehicleIDNumber (Sd *sd)
{
    return sd->vehicleIDNumber;
}

void clksd_sd_set_registrationNumberOfVehicle (Sd *sd, gchar *registrationNumberOfVehicle)
{
    sd->registrationNumberOfVehicle = g_strdup (registrationNumberOfVehicle);
}

gchar *clksd_sd_get_registrationNumberOfVehicle (Sd *sd)
{
    return sd->registrationNumberOfVehicle;
}

void clksd_sd_set_maximumNetPower (Sd *sd, gchar *maximumNetPower)
{
    sd->maximumNetPower = g_strdup (maximumNetPower);
}

gchar *clksd_sd_get_maximumNetPower (Sd *sd)
{
    return sd->maximumNetPower;
}

void clksd_sd_set_engineCapacity (Sd *sd, gchar *engineCapacity)
{
    sd->engineCapacity = g_strdup (engineCapacity);
}

gchar *clksd_sd_get_engineCapacity (Sd *sd)
{
    return sd->engineCapacity;
}

void clksd_sd_set_typeOfFuel (Sd *sd, gchar *typeOfFuel)
{
    sd->typeOfFuel = g_strdup (typeOfFuel);
}

gchar *clksd_sd_get_typeOfFuel (Sd *sd)
{
    return sd->typeOfFuel;
}

void clksd_sd_set_powerWeightRatio (Sd *sd, gchar *powerWeightRatio)
{
    sd->powerWeightRatio = g_strdup (powerWeightRatio);
}

gchar *clksd_sd_get_powerWeightRatio (Sd *sd)
{
    return sd->powerWeightRatio;
}

void clksd_sd_set_vehicleMass (Sd *sd, gchar *vehicleMass)
{
    sd->vehicleMass = g_strdup (vehicleMass);
}

gchar *clksd_sd_get_vehicleMass (Sd *sd)
{
    return sd->vehicleMass;
}

void clksd_sd_set_maximumPermissibleLadenMass (Sd *sd, gchar *maximumPermissibleLadenMass)
{
    sd->maximumPermissibleLadenMass = g_strdup (maximumPermissibleLadenMass);
}

gchar *clksd_sd_get_maximumPermissibleLadenMass (Sd *sd)
{
    return sd->maximumPermissibleLadenMass;
}

void clksd_sd_set_typeApprovalNumber (Sd *sd, gchar *typeApprovalNumber)
{
    sd->typeApprovalNumber = g_strdup (typeApprovalNumber);
}

gchar *clksd_sd_get_typeApprovalNumber (Sd *sd)
{
    return sd->typeApprovalNumber;
}

void clksd_sd_set_numberOfSeats (Sd *sd, gchar *numberOfSeats)
{
    sd->numberOfSeats = g_strdup (numberOfSeats);
}

gchar *clksd_sd_get_numberOfSeats (Sd *sd)
{
    return sd->numberOfSeats;
}

void clksd_sd_set_numberOfStandingPlaces (Sd *sd, gchar *numberOfStandingPlaces)
{
    sd->numberOfStandingPlaces = g_strdup (numberOfStandingPlaces);
}

gchar *clksd_sd_get_numberOfStandingPlaces (Sd *sd)
{
    return sd->numberOfStandingPlaces;
}

void clksd_sd_set_engineIDNumber (Sd *sd, gchar *engineIDNumber)
{
    sd->engineIDNumber = g_strdup (engineIDNumber);
}

gchar *clksd_sd_get_engineIDNumber (Sd *sd)
{
    return sd->engineIDNumber;
}

void clksd_sd_set_numberOfAxles (Sd *sd, gchar *numberOfAxles)
{
    sd->numberOfAxles = g_strdup (numberOfAxles);
}

gchar *clksd_sd_get_numberOfAxles (Sd *sd)
{
    return sd->numberOfAxles;
}

void clksd_sd_set_vehicleCategory (Sd *sd, gchar *vehicleCategory)
{
    sd->vehicleCategory = g_strdup (vehicleCategory);
}

gchar *clksd_sd_get_vehicleCategory (Sd *sd)
{
    return sd->vehicleCategory;
}

void clksd_sd_set_colourOfVehicle (Sd *sd, gchar *colourOfVehicle)
{
    sd->colourOfVehicle = g_strdup (colourOfVehicle);
}

gchar *clksd_sd_get_colourOfVehicle (Sd *sd)
{
    return sd->colourOfVehicle;
}

void clksd_sd_set_restrictionToChangeOwner (Sd *sd, gchar *restrictionToChangeOwner)
{
    sd->restrictionToChangeOwner = g_strdup (restrictionToChangeOwner);
}

gchar *clksd_sd_get_restrictionToChangeOwner (Sd *sd)
{
    return sd->restrictionToChangeOwner;
}

void clksd_sd_set_vehicleLoad (Sd *sd, gchar *vehicleLoad)
{
    sd->vehicleLoad = g_strdup (vehicleLoad);
}

gchar *clksd_sd_get_vehicleLoad (Sd *sd)
{
    return sd->vehicleLoad;
}

void clksd_sd_set_ownersPersonalNo (Sd *sd, gchar *ownersPersonalNo)
{
    sd->ownersPersonalNo = g_strdup (ownersPersonalNo);
}

gchar *clksd_sd_get_ownersPersonalNo (Sd *sd)
{
    return sd->ownersPersonalNo;
}

void clksd_sd_set_ownersSurnameOrBusinessName (Sd *sd, gchar *ownersSurnameOrBusinessName)
{
    sd->ownersSurnameOrBusinessName = g_strdup (ownersSurnameOrBusinessName);
}

gchar *clksd_sd_get_ownersSurnameOrBusinessName (Sd *sd)
{
    return sd->ownersSurnameOrBusinessName;
}

void clksd_sd_set_ownerName (Sd *sd, gchar *ownerName)
{
    sd->ownerName = g_strdup (ownerName);
}

gchar *clksd_sd_get_ownerName (Sd *sd)
{
    return sd->ownerName;
}

void clksd_sd_set_ownerAddress (Sd *sd, gchar *ownerAddress)
{
    sd->ownerAddress = g_strdup (ownerAddress);
}

gchar *clksd_sd_get_ownerAddress (Sd *sd)
{
    return sd->ownerAddress;
}

void clksd_sd_set_usersPersonalNo (Sd *sd, gchar *usersPersonalNo)
{
    sd->usersPersonalNo = g_strdup (usersPersonalNo);
}

gchar *clksd_sd_get_usersPersonalNo (Sd *sd)
{
    return sd->usersPersonalNo;
}

void clksd_sd_set_usersSurnameOrBusinessName (Sd *sd, gchar *usersSurnameOrBusinessName)
{
    sd->usersSurnameOrBusinessName = g_strdup (usersSurnameOrBusinessName);
}

gchar *clksd_sd_get_usersSurnameOrBusinessName (Sd *sd)
{
    return sd->usersSurnameOrBusinessName;
}

void clksd_sd_set_usersName (Sd *sd, gchar *usersName)
{
    sd->usersName = g_strdup (usersName);
}

gchar *clksd_sd_get_usersName (Sd *sd)
{
    return sd->usersName;
}

void clksd_sd_set_usersAddress (Sd *sd, gchar *usersAddress)
{
    sd->usersAddress = g_strdup (usersAddress);
}

gchar *clksd_sd_get_usersAddress (Sd *sd)
{
    return sd->usersAddress;
}

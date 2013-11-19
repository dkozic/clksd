/*
 * File:   sd.h
 * Author: dkozic
 *
 * Created on October 19, 2013, 22:23 PM
 */

#ifndef SD_H
#define	SD_H

typedef struct SdTag
{

    sqlite3_int64 id;

    gchar *stateIssuing;
    gchar *competentAuthority;
    gchar *authorityIssuing;
    gchar *unambiguousNumber;
    gchar *issuingDate;
    gchar *expiryDate;
    gchar *serialNumber;

    gchar *dateOfFirstRegistration;
    gchar *yearOfProduction;
    gchar *vehicleMake;
    gchar *vehicleType;
    gchar *commercialDescription;
    gchar *vehicleIDNumber;
    gchar *registrationNumberOfVehicle;
    gchar *maximumNetPower;
    gchar *engineCapacity;
    gchar *typeOfFuel;
    gchar *powerWeightRatio;
    gchar *vehicleMass;
    gchar *maximumPermissibleLadenMass;
    gchar *typeApprovalNumber;
    gchar *numberOfSeats;
    gchar *numberOfStandingPlaces;
    gchar *engineIDNumber;
    gchar *numberOfAxles;
    gchar *vehicleCategory;
    gchar *colourOfVehicle;
    gchar *restrictionToChangeOwner;
    gchar *vehicleLoad;

    gchar *ownersPersonalNo;
    gchar *ownersSurnameOrBusinessName;
    gchar *ownerName;
    gchar *ownerAddress;
    gchar *usersPersonalNo;
    gchar *usersSurnameOrBusinessName;
    gchar *usersName;
    gchar *usersAddress;

} Sd;

Sd *clksd_sd_new();
void clksd_sd_free (Sd *sd);

void clksd_sd_set_id (Sd *lk, sqlite3_int64 id);
sqlite3_int64 clksd_sd_get_id (Sd *sd);
void clksd_sd_set_stateIssuing (Sd *sd, gchar *stateIssuing);
gchar *clksd_sd_get_stateIssuing (Sd *sd);
void clksd_sd_set_competentAuthority (Sd *sd, gchar *competentAuthority);
gchar *clksd_sd_get_competentAuthority (Sd *sd);
void clksd_sd_set_authorityIssuing (Sd *sd, gchar *authorityIssuing);
gchar *clksd_sd_get_authorityIssuing (Sd *sd);
void clksd_sd_set_unambiguousNumber (Sd *sd, gchar *unambiguousNumber);
gchar *clksd_sd_get_unambiguousNumber (Sd *sd);
void clksd_sd_set_issuingDate (Sd *sd, gchar *issuingDate);
gchar *clksd_sd_get_issuingDate (Sd *sd);
void clksd_sd_set_expiryDate (Sd *sd, gchar *expiryDate);
gchar *clksd_sd_get_expiryDate (Sd *sd);
void clksd_sd_set_serialNumber (Sd *sd, gchar *serialNumber);
gchar *clksd_sd_get_serialNumber (Sd *sd);

void clksd_sd_set_dateOfFirstRegistration (Sd *sd, gchar *dateOfFirstRegistration);
gchar *clksd_sd_get_dateOfFirstRegistration (Sd *sd);
void clksd_sd_set_yearOfProduction (Sd *sd, gchar *yearOfProduction);
gchar *clksd_sd_get_yearOfProduction (Sd *sd);
void clksd_sd_set_vehicleMake (Sd *sd, gchar *vehicleMake);
gchar *clksd_sd_get_vehicleMake (Sd *sd);
void clksd_sd_set_vehicleType (Sd *sd, gchar *vehicleType);
gchar *clksd_sd_get_vehicleType (Sd *sd);
void clksd_sd_set_commercialDescription (Sd *sd, gchar *commercialDescription);
gchar *clksd_sd_get_commercialDescription (Sd *sd);
void clksd_sd_set_vehicleIDNumber (Sd *sd, gchar *vehicleIDNumber);
gchar *clksd_sd_get_vehicleIDNumber (Sd *sd);
void clksd_sd_set_registrationNumberOfVehicle (Sd *sd, gchar *registrationNumberOfVehicle);
gchar *clksd_sd_get_registrationNumberOfVehicle (Sd *sd);
void clksd_sd_set_maximumNetPower (Sd *sd, gchar *maximumNetPower);
gchar *clksd_sd_get_maximumNetPower (Sd *sd);
void clksd_sd_set_engineCapacity (Sd *sd, gchar *engineCapacity);
gchar *clksd_sd_get_engineCapacity (Sd *sd);
void clksd_sd_set_typeOfFuel (Sd *sd, gchar *typeOfFuel);
gchar *clksd_sd_get_typeOfFuel (Sd *sd);
void clksd_sd_set_powerWeightRatio (Sd *sd, gchar *powerWeightRatio);
gchar *clksd_sd_get_powerWeightRatio (Sd *sd);
void clksd_sd_set_vehicleMass (Sd *sd, gchar *vehicleMass);
gchar *clksd_sd_get_vehicleMass (Sd *sd);
void clksd_sd_set_maximumPermissibleLadenMass (Sd *sd, gchar *maximumPermissibleLadenMass);
gchar *clksd_sd_get_maximumPermissibleLadenMass (Sd *sd);
void clksd_sd_set_typeApprovalNumber (Sd *sd, gchar *typeApprovalNumber);
gchar *clksd_sd_get_typeApprovalNumber (Sd *sd);
void clksd_sd_set_numberOfSeats (Sd *sd, gchar *numberOfSeats);
gchar *clksd_sd_get_numberOfSeats (Sd *sd);
void clksd_sd_set_numberOfStandingPlaces (Sd *sd, gchar *numberOfStandingPlaces);
gchar *clksd_sd_get_numberOfStandingPlaces (Sd *sd);
void clksd_sd_set_engineIDNumber (Sd *sd, gchar *engineIDNumber);
gchar *clksd_sd_get_engineIDNumber (Sd *sd);
void clksd_sd_set_numberOfAxles (Sd *sd, gchar *numberOfAxles);
gchar *clksd_sd_get_numberOfAxles (Sd *sd);
void clksd_sd_set_vehicleCategory (Sd *sd, gchar *vehicleCategory);
gchar *clksd_sd_get_vehicleCategory (Sd *sd);
void clksd_sd_set_colourOfVehicle (Sd *sd, gchar *colourOfVehicle);
gchar *clksd_sd_get_colourOfVehicle (Sd *sd);
void clksd_sd_set_restrictionToChangeOwner (Sd *sd, gchar *restrictionToChangeOwner);
gchar *clksd_sd_get_restrictionToChangeOwner (Sd *sd);
void clksd_sd_set_vehicleLoad (Sd *sd, gchar *vehicleLoad);
gchar *clksd_sd_get_vehicleLoad (Sd *sd);

void clksd_sd_set_ownersPersonalNo (Sd *sd, gchar *ownersPersonalNo);
gchar *clksd_sd_get_ownersPersonalNo (Sd *sd);
void clksd_sd_set_ownersSurnameOrBusinessName (Sd *sd, gchar *ownersSurnameOrBusinessName);
gchar *clksd_sd_get_ownersSurnameOrBusinessName (Sd *sd);
void clksd_sd_set_ownerName (Sd *sd, gchar *ownerName);
gchar *clksd_sd_get_ownerName (Sd *sd);
void clksd_sd_set_ownerAddress (Sd *sd, gchar *ownerAddress);
gchar *clksd_sd_get_ownerAddress (Sd *sd);
void clksd_sd_set_usersPersonalNo (Sd *sd, gchar *usersPersonalNo);
gchar *clksd_sd_get_usersPersonalNo (Sd *sd);
void clksd_sd_set_usersPersonalNo (Sd *sd, gchar *usersPersonalNo);
gchar *clksd_sd_get_usersPersonalNo (Sd *sd);
void clksd_sd_set_usersSurnameOrBusinessName (Sd *sd, gchar *usersSurnameOrBusinessName);
gchar *clksd_sd_get_usersSurnameOrBusinessName (Sd *sd);
void clksd_sd_set_usersName (Sd *sd, gchar *usersName);
gchar *clksd_sd_get_usersName (Sd *sd);
void clksd_sd_set_usersAddress (Sd *sd, gchar *usersAddress);
gchar *clksd_sd_get_usersAddress (Sd *sd);

#endif	/* SD_H */

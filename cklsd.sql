CREATE TABLE lk (
id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL,
docRegNo TEXT,
issuingDate TEXT,
expiryDate TEXT,
issuingAuthority TEXT,
personalNumber TEXT,
surname TEXT,
givenName TEXT,
parentGivenName TEXT,
sex TEXT,
placeOfBirth TEXT,
stateOfBirth TEXT,
dateOfBirth TEXT,
communityOfBirth TEXT,
state TEXT,
community TEXT,
place TEXT,
street TEXT,
houseNumber TEXT,
houseLetter TEXT,
entrance TEXT,
floor TEXT,
apartmentNumber TEXT,
portrait BLOB,
portraitSize INTEGER
);

CREATE TABLE sd (
id INTEGER PRIMARY KEY  AUTOINCREMENT  NOT NULL,
stateIssuing TEXT,
competentAuthority TEXT,
authorityIssuing TEXT,
unambiguousNumber TEXT,
issuingDate TEXT,
expiryDate TEXT,
serialNumber TEXT,
dateOfFirstRegistration TEXT,
yearOfProduction TEXT,
vehicleMake TEXT,
vehicleType TEXT,
commercialDescription TEXT,
vehicleIDNumber TEXT,
registrationNumberOfVehicle TEXT,
maximumNetPower TEXT,
engineCapacity TEXT,
typeOfFuel TEXT,
powerWeightRatio TEXT,
vehicleMass TEXT,
maximumPermissibleLadenMass TEXT,
typeApprovalNumber TEXT,
numberOfSeats TEXT,
numberOfStandingPlaces TEXT,
engineIDNumber TEXT,
numberOfAxles TEXT,
vehicleCategory TEXT,
colourOfVehicle TEXT,
restrictionToChangeOwner TEXT,
vehicleLoad TEXT,
ownersPersonalNo TEXT,
ownersSurnameOrBusinessName TEXT,
ownerName TEXT,
ownerAddress TEXT,
usersPersonalNo TEXT,
usersSurnameOrBusinessName TEXT,
usersName TEXT,
usersAddress TEXT
);
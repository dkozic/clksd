#include <glib.h>
#include <windows.h>
#include <CelikApi.h>
#include <sqlite3.h>
#include "sd.h"
#include "sddb.h"

GQuark clksd_sddb_error_quark()
{
    static GQuark q = 0;
    if (q == 0)
    {
        q = g_quark_from_static_string("clksd-sddb-error");
    }
    return q;
}

static const char *dbName = "clksd.sqlite";

gboolean clksd_sddb_insert (Sd *sd, GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *pzTail;
    char *zSql = "insert into sd (stateIssuing, competentAuthority, authorityIssuing, unambiguousNumber, issuingDate, expiryDate, serialNumber, " \
                 " dateOfFirstRegistration, yearOfProduction, vehicleMake, vehicleType, commercialDescription, " \
                 " vehicleIDNumber, registrationNumberOfVehicle, maximumNetPower, engineCapacity, typeOfFuel, " \
                 " powerWeightRatio, vehicleMass, maximumPermissibleLadenMass, typeApprovalNumber, numberOfSeats," \
                 " numberOfStandingPlaces, engineIDNumber, numberOfAxles, vehicleCategory, colourOfVehicle, " \
                 " restrictionToChangeOwner, vehicleLoad, ownersPersonalNo, ownersSurnameOrBusinessName, " \
                 " ownerName, ownerAddress, usersPersonalNo, usersSurnameOrBusinessName, usersName, usersAddress) " \
                 "values (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, " \
                 "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, " \
                 "?, ?, ?, ?, ?, ?, ?, ?, ?, ?, " \
                 "?, ?, ?, ?, ?, ?, ?)";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 1, sd->stateIssuing, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 1: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 2, sd->competentAuthority, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 2: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 3, sd->authorityIssuing, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 3: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 4, sd->unambiguousNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 4: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 5, sd->issuingDate, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 5: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 6, sd->expiryDate, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 6: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 7, sd->serialNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 7: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 8, sd->dateOfFirstRegistration, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 8: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 9, sd->yearOfProduction, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 9: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 10, sd->vehicleMake, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 10: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 11, sd->vehicleType, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 11: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 12, sd->commercialDescription, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 12: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 13, sd->vehicleIDNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 13: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 14, sd->registrationNumberOfVehicle, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 14: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 15, sd->maximumNetPower, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 15: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 16, sd->engineCapacity, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 16: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 17, sd->typeOfFuel, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 17: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 18, sd->powerWeightRatio, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 18: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 19, sd->vehicleMass, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 19: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 20, sd->maximumPermissibleLadenMass, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 20: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 21, sd->typeApprovalNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 21: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 22, sd->numberOfSeats, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 22: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 23, sd->numberOfStandingPlaces, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 23: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 24, sd->engineIDNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 24: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 25, sd->numberOfAxles, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 25: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 26, sd->vehicleCategory, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 26: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 27, sd->colourOfVehicle, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 27: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 28, sd->restrictionToChangeOwner, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 28: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 29, sd->vehicleLoad, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 29: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 30, sd->ownersPersonalNo, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 30: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 31, sd->ownersSurnameOrBusinessName, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 31: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 32, sd->ownerName, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 32: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 33, sd->ownerAddress, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 33: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 34, sd->usersPersonalNo, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 34: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 35, sd->usersSurnameOrBusinessName, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 35: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 36, sd->usersName, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 36: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }
    rc = sqlite3_bind_text(stmt, 37, sd->usersAddress, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 37: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE)
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    sd->id = sqlite3_last_insert_rowid(db);

    return TRUE;
}

gboolean clksd_sddb_delete (sqlite3_int64 id, GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *pzTail;
    int rc;
    char *zSql = "delete from sd where id = ?";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_int64(stmt, 1, id);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter 1: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE)
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FINALIZE, "Can't finalize database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    return TRUE;
}

gboolean clksd_sddb_delete_all (GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *pzTail;
    int rc;
    char *zSql = "delete from sd";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE)
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    return TRUE;
}

gint clksd_sddb_count_all (GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    gint result = 0;
    int rc;
    const char *pzTail;
    char *zSql = "select count(*) from lk";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_ROW)
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    result = sqlite3_column_int(stmt, 0);

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    return result;
}

Sd *clksd_sddb_find (sqlite3_int64 id, GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    Sd *sd;
    int rc;
    const char *pzTail;
    char *zSql = "select id, stateIssuing, competentAuthority, authorityIssuing, unambiguousNumber, issuingDate, expiryDate, serialNumber, " \
                 " dateOfFirstRegistration, yearOfProduction, vehicleMake, vehicleType, commercialDescription, " \
                 " vehicleIDNumber, registrationNumberOfVehicle, maximumNetPower, engineCapacity, typeOfFuel, " \
                 " powerWeightRatio, vehicleMass, maximumPermissibleLadenMass, typeApprovalNumber, numberOfSeats," \
                 " numberOfStandingPlaces, engineIDNumber, numberOfAxles, vehicleCategory, colourOfVehicle, " \
                 " restrictionToChangeOwner, vehicleLoad, ownersPersonalNo, ownersSurnameOrBusinessName, " \
                 " ownerName, ownerAddress, usersPersonalNo, usersSurnameOrBusinessName, usersName, usersAddress " \
                 "from sd where id = ?";


    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_bind_int64(stmt, 1, id);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_BIND, "Can't bind parameter: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_step(stmt);
    if( rc == SQLITE_DONE)
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    if( rc != SQLITE_ROW)
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FAILED, "Can't read database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    sd = clksd_sd_new();
    sd->id = id;

    clksd_sd_set_stateIssuing(sd, (gchar *)sqlite3_column_text(stmt, 1));
    clksd_sd_set_competentAuthority(sd, (gchar *)sqlite3_column_text(stmt, 2));
    clksd_sd_set_authorityIssuing(sd, (gchar *)sqlite3_column_text(stmt, 3));
    clksd_sd_set_unambiguousNumber(sd, (gchar *)sqlite3_column_text(stmt, 4));
    clksd_sd_set_issuingDate(sd, (gchar *)sqlite3_column_text(stmt, 5));
    clksd_sd_set_expiryDate(sd, (gchar *)sqlite3_column_text(stmt, 6));
    clksd_sd_set_serialNumber(sd, (gchar *)sqlite3_column_text(stmt, 7));

    clksd_sd_set_dateOfFirstRegistration(sd, (gchar *)sqlite3_column_text(stmt, 8));
    clksd_sd_set_yearOfProduction(sd, (gchar *)sqlite3_column_text(stmt, 9));
    clksd_sd_set_vehicleMake(sd, (gchar *)sqlite3_column_text(stmt, 10));
    clksd_sd_set_vehicleType(sd, (gchar *)sqlite3_column_text(stmt, 11));
    clksd_sd_set_commercialDescription(sd, (gchar *)sqlite3_column_text(stmt, 12));
    clksd_sd_set_vehicleIDNumber(sd, (gchar *)sqlite3_column_text(stmt, 13));
    clksd_sd_set_registrationNumberOfVehicle(sd, (gchar *)sqlite3_column_text(stmt, 14));
    clksd_sd_set_maximumNetPower(sd, (gchar *)sqlite3_column_text(stmt, 15));
    clksd_sd_set_engineCapacity(sd, (gchar *)sqlite3_column_text(stmt, 16));
    clksd_sd_set_typeOfFuel(sd, (gchar *)sqlite3_column_text(stmt, 17));
    clksd_sd_set_powerWeightRatio(sd, (gchar *)sqlite3_column_text(stmt, 18));
    clksd_sd_set_vehicleMass(sd, (gchar *)sqlite3_column_text(stmt, 19));
    clksd_sd_set_maximumPermissibleLadenMass(sd, (gchar *)sqlite3_column_text(stmt, 20));
    clksd_sd_set_typeApprovalNumber(sd, (gchar *)sqlite3_column_text(stmt, 21));
    clksd_sd_set_numberOfSeats(sd, (gchar *)sqlite3_column_text(stmt, 22));
    clksd_sd_set_numberOfStandingPlaces(sd, (gchar *)sqlite3_column_text(stmt, 23));
    clksd_sd_set_engineIDNumber(sd, (gchar *)sqlite3_column_text(stmt, 24));
    clksd_sd_set_numberOfAxles(sd, (gchar *)sqlite3_column_text(stmt, 25));
    clksd_sd_set_vehicleCategory(sd, (gchar *)sqlite3_column_text(stmt, 26));
    clksd_sd_set_colourOfVehicle(sd, (gchar *)sqlite3_column_text(stmt, 27));
    clksd_sd_set_restrictionToChangeOwner(sd, (gchar *)sqlite3_column_text(stmt, 28));
    clksd_sd_set_vehicleLoad(sd, (gchar *)sqlite3_column_text(stmt, 29));

    clksd_sd_set_ownersPersonalNo(sd, (gchar *)sqlite3_column_text(stmt, 30));
    clksd_sd_set_ownersSurnameOrBusinessName(sd, (gchar *)sqlite3_column_text(stmt, 31));
    clksd_sd_set_ownerName(sd, (gchar *)sqlite3_column_text(stmt, 32));
    clksd_sd_set_ownerAddress(sd, (gchar *)sqlite3_column_text(stmt, 33));
    clksd_sd_set_usersPersonalNo(sd, (gchar *)sqlite3_column_text(stmt, 34));
    clksd_sd_set_usersSurnameOrBusinessName(sd, (gchar *)sqlite3_column_text(stmt, 35));
    clksd_sd_set_usersName(sd, (gchar *)sqlite3_column_text(stmt, 36));
    clksd_sd_set_usersAddress(sd, (gchar *)sqlite3_column_text(stmt, 37));

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        clksd_sd_free(sd);
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        clksd_sd_free(sd);
        return NULL;
    }

    return sd;
}

static void array_free_func (gpointer data)
{
    Sd *sd = (Sd *)data;
    clksd_sd_free(sd);
}

GPtrArray *clksd_sddb_find_all (GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    Sd *sd;
    int rc;
    GPtrArray *sdArray = g_ptr_array_new_with_free_func(array_free_func);
    const char *pzTail;
    char *zSql = "select id, stateIssuing, competentAuthority, authorityIssuing, unambiguousNumber, issuingDate, expiryDate, serialNumber, " \
                 " dateOfFirstRegistration, yearOfProduction, vehicleMake, vehicleType, commercialDescription, " \
                 " vehicleIDNumber, registrationNumberOfVehicle, maximumNetPower, engineCapacity, typeOfFuel, " \
                 " powerWeightRatio, vehicleMass, maximumPermissibleLadenMass, typeApprovalNumber, numberOfSeats," \
                 " numberOfStandingPlaces, engineIDNumber, numberOfAxles, vehicleCategory, colourOfVehicle, " \
                 " restrictionToChangeOwner, vehicleLoad, ownersPersonalNo, ownersSurnameOrBusinessName, " \
                 " ownerName, ownerAddress, usersPersonalNo, usersSurnameOrBusinessName, usersName, usersAddress " \
                 "from sd";


    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    while (TRUE)
    {
        rc = sqlite3_step(stmt);
        if( rc == SQLITE_DONE)
        {
            break;
        }

        if( rc != SQLITE_ROW)
        {
            g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_close(db);
            g_ptr_array_free(sdArray, TRUE);
            return NULL;
        }


        sd = clksd_sd_new();

        clksd_sd_set_id(sd, sqlite3_column_int64(stmt, 0));

        clksd_sd_set_stateIssuing(sd, (gchar *)sqlite3_column_text(stmt, 1));
        clksd_sd_set_competentAuthority(sd, (gchar *)sqlite3_column_text(stmt, 2));
        clksd_sd_set_authorityIssuing(sd, (gchar *)sqlite3_column_text(stmt, 3));
        clksd_sd_set_unambiguousNumber(sd, (gchar *)sqlite3_column_text(stmt, 4));
        clksd_sd_set_issuingDate(sd, (gchar *)sqlite3_column_text(stmt, 5));
        clksd_sd_set_expiryDate(sd, (gchar *)sqlite3_column_text(stmt, 6));
        clksd_sd_set_serialNumber(sd, (gchar *)sqlite3_column_text(stmt, 7));

        clksd_sd_set_dateOfFirstRegistration(sd, (gchar *)sqlite3_column_text(stmt, 8));
        clksd_sd_set_yearOfProduction(sd, (gchar *)sqlite3_column_text(stmt, 9));
        clksd_sd_set_vehicleMake(sd, (gchar *)sqlite3_column_text(stmt, 10));
        clksd_sd_set_vehicleType(sd, (gchar *)sqlite3_column_text(stmt, 11));
        clksd_sd_set_commercialDescription(sd, (gchar *)sqlite3_column_text(stmt, 12));
        clksd_sd_set_vehicleIDNumber(sd, (gchar *)sqlite3_column_text(stmt, 13));
        clksd_sd_set_registrationNumberOfVehicle(sd, (gchar *)sqlite3_column_text(stmt, 14));
        clksd_sd_set_maximumNetPower(sd, (gchar *)sqlite3_column_text(stmt, 15));
        clksd_sd_set_engineCapacity(sd, (gchar *)sqlite3_column_text(stmt, 16));
        clksd_sd_set_typeOfFuel(sd, (gchar *)sqlite3_column_text(stmt, 17));
        clksd_sd_set_powerWeightRatio(sd, (gchar *)sqlite3_column_text(stmt, 18));
        clksd_sd_set_vehicleMass(sd, (gchar *)sqlite3_column_text(stmt, 19));
        clksd_sd_set_maximumPermissibleLadenMass(sd, (gchar *)sqlite3_column_text(stmt, 20));
        clksd_sd_set_typeApprovalNumber(sd, (gchar *)sqlite3_column_text(stmt, 21));
        clksd_sd_set_numberOfSeats(sd, (gchar *)sqlite3_column_text(stmt, 22));
        clksd_sd_set_numberOfStandingPlaces(sd, (gchar *)sqlite3_column_text(stmt, 23));
        clksd_sd_set_engineIDNumber(sd, (gchar *)sqlite3_column_text(stmt, 24));
        clksd_sd_set_numberOfAxles(sd, (gchar *)sqlite3_column_text(stmt, 25));
        clksd_sd_set_vehicleCategory(sd, (gchar *)sqlite3_column_text(stmt, 26));
        clksd_sd_set_colourOfVehicle(sd, (gchar *)sqlite3_column_text(stmt, 27));
        clksd_sd_set_restrictionToChangeOwner(sd, (gchar *)sqlite3_column_text(stmt, 28));
        clksd_sd_set_vehicleLoad(sd, (gchar *)sqlite3_column_text(stmt, 29));

        clksd_sd_set_ownersPersonalNo(sd, (gchar *)sqlite3_column_text(stmt, 30));
        clksd_sd_set_ownersSurnameOrBusinessName(sd, (gchar *)sqlite3_column_text(stmt, 31));
        clksd_sd_set_ownerName(sd, (gchar *)sqlite3_column_text(stmt, 32));
        clksd_sd_set_ownerAddress(sd, (gchar *)sqlite3_column_text(stmt, 33));
        clksd_sd_set_usersPersonalNo(sd, (gchar *)sqlite3_column_text(stmt, 34));
        clksd_sd_set_usersSurnameOrBusinessName(sd, (gchar *)sqlite3_column_text(stmt, 35));
        clksd_sd_set_usersName(sd, (gchar *)sqlite3_column_text(stmt, 36));
        clksd_sd_set_usersAddress(sd, (gchar *)sqlite3_column_text(stmt, 37));

        g_ptr_array_add(sdArray, (gpointer)sd);

    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_SDDB_ERROR, CLKSD_SDDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    return sdArray;
}

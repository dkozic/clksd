#include <glib.h>
#include <windows.h>
#include <CelikApi.h>
#include <sqlite3.h>
#include "lk.h"
#include "lkdb.h"

GQuark clksd_lkdb_error_quark()
{
    static GQuark q = 0;
    if (q == 0)
    {
        q = g_quark_from_static_string("clksd-lkdb-error");
    }
    return q;
}
/*
static gchar *sqlite_message(int rc)
{
    gchar *errorMessage;

    switch (rc)
    {
    case SQLITE_OK:
        errorMessage = "Successful result";
        break;
    case SQLITE_ERROR:
        errorMessage = "SQL error or missing database";
        break;
    case SQLITE_INTERNAL:
        errorMessage = "Internal logic error in SQLite";
        break;
    case SQLITE_PERM:
        errorMessage = "Access permission denied";
        break;
    case SQLITE_ABORT:
        errorMessage = "Callback routine requested an abort";
        break;
    case SQLITE_BUSY:
        errorMessage = "The database file is locked";
        break;
    case SQLITE_LOCKED:
        errorMessage = "A table in the database is locked";
        break;
    case SQLITE_NOMEM:
        errorMessage = "A malloc() failed";
        break;
    case SQLITE_READONLY:
        errorMessage = "Attempt to write a readonly database";
        break;
    case SQLITE_INTERRUPT:
        errorMessage = "Operation terminated by sqlite3_interrupt()";
        break;
    case SQLITE_IOERR:
        errorMessage = "Some kind of disk I/O error occurred";
        break;
    case SQLITE_CORRUPT:
        errorMessage = "The database disk image is malformed";
        break;
    case SQLITE_NOTFOUND:
        errorMessage = "Unknown opcode in sqlite3_file_control()";
        break;
    case SQLITE_FULL:
        errorMessage = "Insertion failed because database is full";
        break;
    case SQLITE_CANTOPEN:
        errorMessage = "Unable to open the database file";
        break;
    case SQLITE_PROTOCOL:
        errorMessage = "Database lock protocol error";
        break;
    case SQLITE_EMPTY:
        errorMessage = "Database is empty";
        break;
    case SQLITE_SCHEMA:
        errorMessage = "The database schema changed";
        break;
    case SQLITE_TOOBIG:
        errorMessage = "String or BLOB exceeds size limit";
        break;
    case SQLITE_CONSTRAINT:
        errorMessage = "Abort due to constraint violation";
        break;
    case SQLITE_MISMATCH:
        errorMessage = "Data type mismatch";
        break;
    case SQLITE_MISUSE:
        errorMessage = "Library used incorrectly";
        break;
    case SQLITE_NOLFS:
        errorMessage = "Uses OS features not supported on host";
        break;
    case SQLITE_AUTH:
        errorMessage = "Authorization denied";
        break;
    case SQLITE_FORMAT:
        errorMessage = "Auxiliary database format error";
        break;
    case SQLITE_RANGE:
        errorMessage = "2nd parameter to sqlite3_bind out of range";
        break;
    case SQLITE_NOTADB:
        errorMessage = "File opened that is not a database file";
        break;
    case SQLITE_NOTICE:
        errorMessage = "Notifications from sqlite3_log()";
        break;
    case SQLITE_WARNING:
        errorMessage = "Warnings from sqlite3_log()";
        break;
    case SQLITE_ROW:
        errorMessage = "sqlite3_step() has another row ready";
        break;
    case SQLITE_DONE:
        errorMessage = "sqlite3_step() has finished executing";
        break;
    default:
        errorMessage = "Unknown Sqlite Error";
    }
    return errorMessage;
}
*/

static const char *dbName = "clksd.sqlite";

gboolean clksd_lkdb_insert (Lk *lk, GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    const char *pzTail;
    char *zSql = "insert into lk (docRegNo, issuingDate, expiryDate, issuingAuthority, " \
                 "personalNumber, surname, givenName, parentGivenName, sex, placeOfBirth, stateOfBirth, dateOfBirth, communityOfBirth, " \
                 "state, community, place, street, houseNumber, houseLetter, entrance, floor, apartmentNumber, " \
                 "portrait, portraitSize) " \
                 "values (?, ?, ?, ?, " \
                 "?, ?, ?, ?, ?, ?, ?, ?, ?, " \
                 "?, ?, ?, ?, ?, ?, ?, ?, ?, " \
                 "?, ?)";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 1, lk->docRegNo, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 1: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 2, lk->issuingDate, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 2: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 3, lk->expiryDate, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 3: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 4, lk->issuingAuthority, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 4: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 5, lk->personalNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 5: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 6, lk->surname, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 6: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 7, lk->givenName, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 7: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 8, lk->parentGivenName, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 8: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 9, lk->sex, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 9: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 10, lk->placeOfBirth, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 10: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 11, lk->stateOfBirth, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 11: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 12, lk->dateOfBirth, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 12: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 13, lk->communityOfBirth, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 13: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 14, lk->state, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 14: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 15, lk->community, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 15: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 16, lk->place, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 16: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 17, lk->street, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 17: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 18, lk->houseNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 18: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 19, lk->houseLetter, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 19: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 20, lk->entrance, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 20: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 21, lk->floor, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 21: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_text(stmt, 22, lk->apartmentNumber, -1,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 22: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_blob(stmt, 23, lk->portrait, lk->portraitSize,  SQLITE_STATIC);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 23: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_int(stmt, 24, lk->portraitSize);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 24: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE)
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    lk->id = sqlite3_last_insert_rowid(db);

    return TRUE;
}

gboolean clksd_lkdb_delete (sqlite3_int64 id, GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *pzTail;
    int rc;
    char *zSql = "delete from lk where id = ?";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_bind_int64(stmt, 1, id);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter 1: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE)
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FINALIZE, "Can't finalize database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    return TRUE;
}

gboolean clksd_lkdb_delete_all (GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *pzTail;
    int rc;
    char *zSql = "delete from lk";

    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_DONE)
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return FALSE;
    }

    return TRUE;
}

gint clksd_lkdb_count_all (GError **error)
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
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_step(stmt);
    if( rc != SQLITE_ROW)
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    result = sqlite3_column_int(stmt, 0);

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    return result;
}

Lk *clksd_lkdb_find (sqlite3_int64 id, GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    Lk *lk;
    int rc;
    const char *pzTail;
    char *zSql = "select id, docRegNo, issuingDate, expiryDate, issuingAuthority, " \
                 "personalNumber, surname, givenName, parentGivenName, sex, placeOfBirth, stateOfBirth, dateOfBirth, communityOfBirth, " \
                 "state, community, place, street, houseNumber, houseLetter, entrance, floor, apartmentNumber, " \
                 "portrait, portraitSize " \
                 "from lk where id = ?";


    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_bind_int64(stmt, 1, id);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_BIND, "Can't bind parameter: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_step(stmt);
    if( rc == SQLITE_DONE)
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    if( rc != SQLITE_ROW)
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FAILED, "Can't read database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    lk = clksd_lk_new();
    lk->id = id;
    clksd_lk_set_docRegNo(lk, (gchar *)sqlite3_column_text(stmt, 1));
    clksd_lk_set_issuingDate(lk, (gchar *)sqlite3_column_text(stmt, 2));
    clksd_lk_set_expiryDate(lk, (gchar *)sqlite3_column_text(stmt, 3));
    clksd_lk_set_issuingAuthority(lk, (gchar *)sqlite3_column_text(stmt, 4));

    clksd_lk_set_personalNumber(lk, (gchar *)sqlite3_column_text(stmt, 5));
    clksd_lk_set_surname(lk, (gchar *)sqlite3_column_text(stmt, 6));
    clksd_lk_set_givenName(lk, (gchar *)sqlite3_column_text(stmt, 7));
    clksd_lk_set_parentGivenName(lk, (gchar *)sqlite3_column_text(stmt, 8));
    clksd_lk_set_sex(lk, (gchar *)sqlite3_column_text(stmt, 9));
    clksd_lk_set_placeOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 10));
    clksd_lk_set_stateOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 11));
    clksd_lk_set_dateOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 12));
    clksd_lk_set_communityOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 13));
    clksd_lk_set_state(lk, (gchar *)sqlite3_column_text(stmt, 14));
    clksd_lk_set_community(lk, (gchar *)sqlite3_column_text(stmt, 15));
    clksd_lk_set_place(lk, (gchar *)sqlite3_column_text(stmt, 16));
    clksd_lk_set_street(lk, (gchar *)sqlite3_column_text(stmt, 17));
    clksd_lk_set_houseNumber(lk, (gchar *)sqlite3_column_text(stmt, 18));
    clksd_lk_set_houseLetter(lk, (gchar *)sqlite3_column_text(stmt, 19));
    clksd_lk_set_entrance(lk, (gchar *)sqlite3_column_text(stmt, 20));
    clksd_lk_set_floor(lk, (gchar *)sqlite3_column_text(stmt, 21));
    clksd_lk_set_apartmentNumber(lk, (gchar *)sqlite3_column_text(stmt, 22));

    clksd_lk_set_portrait(lk, (BYTE *)sqlite3_column_blob(stmt, 23), sqlite3_column_bytes(stmt, 23));

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        clksd_lk_free(lk);
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        clksd_lk_free(lk);
        return NULL;
    }

    return lk;
}

static void array_free_func (gpointer data)
{
    Lk *lk = (Lk *)data;
    clksd_lk_free(lk);
}

GPtrArray *clksd_lkdb_find_all (GError **error)
{
    sqlite3 *db;
    sqlite3_stmt *stmt;
    Lk *lk;
    int rc;
    GPtrArray *lkArray = g_ptr_array_new_with_free_func(array_free_func);
    const char *pzTail;
    char *zSql = "select id, docRegNo, issuingDate, expiryDate, issuingAuthority, " \
                 "personalNumber, surname, givenName, parentGivenName, sex, placeOfBirth, stateOfBirth, dateOfBirth, communityOfBirth, " \
                 "state, community, place, street, houseNumber, houseLetter, entrance, floor, apartmentNumber, " \
                 "portrait, portraitSize " \
                 "from lk";


    rc = sqlite3_open(dbName, &db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_OPEN, "Can't open database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_prepare_v2(db, zSql, -1, &stmt, &pzTail);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_PREPARE, "Can't prepare statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
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
            g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_STEP, "Can't step statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
            sqlite3_close(db);
            g_ptr_array_free(lkArray, TRUE);
            return NULL;
        }


        lk = clksd_lk_new();
        clksd_lk_set_id(lk, sqlite3_column_int64(stmt, 0));
        clksd_lk_set_docRegNo(lk, (gchar *)sqlite3_column_text(stmt, 1));
        clksd_lk_set_issuingDate(lk, (gchar *)sqlite3_column_text(stmt, 2));
        clksd_lk_set_expiryDate(lk, (gchar *)sqlite3_column_text(stmt, 3));
        clksd_lk_set_issuingAuthority(lk, (gchar *)sqlite3_column_text(stmt, 4));

        clksd_lk_set_personalNumber(lk, (gchar *)sqlite3_column_text(stmt, 5));
        clksd_lk_set_surname(lk, (gchar *)sqlite3_column_text(stmt, 6));
        clksd_lk_set_givenName(lk, (gchar *)sqlite3_column_text(stmt, 7));
        clksd_lk_set_parentGivenName(lk, (gchar *)sqlite3_column_text(stmt, 8));
        clksd_lk_set_sex(lk, (gchar *)sqlite3_column_text(stmt, 9));
        clksd_lk_set_placeOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 10));
        clksd_lk_set_stateOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 11));
        clksd_lk_set_dateOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 12));
        clksd_lk_set_communityOfBirth(lk, (gchar *)sqlite3_column_text(stmt, 13));
        clksd_lk_set_state(lk, (gchar *)sqlite3_column_text(stmt, 14));
        clksd_lk_set_community(lk, (gchar *)sqlite3_column_text(stmt, 15));
        clksd_lk_set_place(lk, (gchar *)sqlite3_column_text(stmt, 16));
        clksd_lk_set_street(lk, (gchar *)sqlite3_column_text(stmt, 17));
        clksd_lk_set_houseNumber(lk, (gchar *)sqlite3_column_text(stmt, 18));
        clksd_lk_set_houseLetter(lk, (gchar *)sqlite3_column_text(stmt, 19));
        clksd_lk_set_entrance(lk, (gchar *)sqlite3_column_text(stmt, 20));
        clksd_lk_set_floor(lk, (gchar *)sqlite3_column_text(stmt, 21));
        clksd_lk_set_apartmentNumber(lk, (gchar *)sqlite3_column_text(stmt, 22));

        clksd_lk_set_portrait(lk, (BYTE *)sqlite3_column_blob(stmt, 23), sqlite3_column_bytes(stmt, 23));

        g_ptr_array_add(lkArray, (gpointer)lk);

    }

    rc = sqlite3_finalize(stmt);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_FINALIZE, "Can't finalize statement: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    rc = sqlite3_close(db);
    if( rc )
    {
        g_set_error(error, CLKSD_LKDB_ERROR, CLKSD_LKDB_ERROR_CLOSE, "Can't close database: errcode: %d, errmsg: %s", sqlite3_errcode(db), sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    return lkArray;
}

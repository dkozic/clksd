/*
 * File:   sddb.h
 * Author: dkozic
 *
 * Created on October 19, 2013, 22:51 PM
 */

#ifndef SDDB_H
#define	SDDB_H

#define CLKSD_SDDB_ERROR (clksd_sddb_error_quark())

enum
{
    CLKSD_SDDB_ERROR_OPEN,
    CLKSD_SDDB_ERROR_PREPARE,
    CLKSD_SDDB_ERROR_BIND,
    CLKSD_SDDB_ERROR_STEP,
    CLKSD_SDDB_ERROR_FINALIZE,
    CLKSD_SDDB_ERROR_CLOSE,
    CLKSD_SDDB_ERROR_FAILED
};

GQuark clksd_sddb_error_quark();

gboolean clksd_sddb_insert (Sd *sd, GError **error);
gboolean clksd_sddb_delete (sqlite3_int64 id, GError **error);
gboolean clksd_sddb_delete_all (GError **error);
gint clksd_sddb_count_all (GError **error);
Sd *clksd_sddb_find (sqlite3_int64 id, GError **error);
GPtrArray *clksd_sddb_find_all (GError **error);


#endif	/* SDDB_H */

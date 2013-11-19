/*
 * File:   lkdb.h
 * Author: dkozic
 *
 * Created on October 9, 2013, 9:21 PM
 */

#ifndef LKDB_H
#define	LKDB_H

#define CLKSD_LKDB_ERROR (clksd_lkdb_error_quark())

enum
{
    CLKSD_LKDB_ERROR_OPEN,
    CLKSD_LKDB_ERROR_PREPARE,
    CLKSD_LKDB_ERROR_BIND,
    CLKSD_LKDB_ERROR_STEP,
    CLKSD_LKDB_ERROR_FINALIZE,
    CLKSD_LKDB_ERROR_CLOSE,
    CLKSD_LKDB_ERROR_FAILED
};

GQuark clksd_lkdb_error_quark();

gboolean clksd_lkdb_insert (Lk *lk, GError **error);
gboolean clksd_lkdb_delete (sqlite3_int64 id, GError **error);
gboolean clksd_lkdb_delete_all (GError **error);
gint clksd_lkdb_count_all (GError **error);
Lk *clksd_lkdb_find (sqlite3_int64 id, GError **error);
GPtrArray *clksd_lkdb_find_all (GError **error);

#endif	/* LKDB_H */

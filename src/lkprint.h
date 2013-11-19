/*
 * File:   lkprint.h
 * Author: dkozic
 *
 * Created on October 8, 2013, 10:22 PM
 */

#ifndef LKPRINT_H
#define	LKPRINT_H

#define CLKSD_LKPRINT_ERROR (clksd_lkprint_error_quark())

enum
{
    CLKSD_LKPRINT_ERROR_NEW,
    CLKSD_LKPRINT_ERROR_FAILED
};

GQuark clksd_lkprint_error_quark();

gboolean clksd_lkprint_print (Lk *lk, char *fname, GError **error);
#endif	/* LKPRINT_H */

/*
 * File:   lksc.h
 * Author: dkozic
 *
 * Created on October 9, 2013, 10:27 PM
 */

#ifndef LKSC_H
#define	LKSC_H

#define CLKSD_LKSC_ERROR (clksd_lksc_error_quark())

enum
{
    CLKSD_LKSC_ERROR_STARTUP,
    CLKSD_LKSC_ERROR_BEGIN_READ,
    CLKSD_LKSC_ERROR_READ_DOCUMENT_DATA,
    CLKSD_LKSC_ERROR_READ_FIXED_PERSONAL_DATA,
    CLKSD_LKSC_ERROR_READ_VARIABLE_PERSONAL_DATA,
    CLKSD_LKSC_ERROR_READ_PORTRAIT,
    CLKSD_LKSC_ERROR_END_READ,
    CLKSD_LKSC_ERROR_CLEANUP,
    CLKSD_LKSC_ERROR_FAILED
};

GQuark clksd_lksc_error_quark();

Lk *clksd_lksc_new_from_eid(EID_DOCUMENT_DATA *dData, EID_FIXED_PERSONAL_DATA *fpData, EID_VARIABLE_PERSONAL_DATA *vpData, EID_PORTRAIT *portrait);
Lk *clksd_lksc_read_eid(GError **error);

#endif	/* LKSC_H */

/*
 * File:   sdprint.h
 * Author: dkozic
 *
 * Created on October 20, 2013, 19:12 PM
 */

#ifndef SDPRINT_H
#define	SDPRINT_H

#define CLKSD_SDPRINT_ERROR (clksd_sdprint_error_quark())

enum
{
    CLKSD_SDPRINT_ERROR_NEW,
    CLKSD_SDPRINT_ERROR_FAILED
};

GQuark clksd_sdprint_error_quark();

gboolean clksd_sdprint_print (Sd *sd, char *fname, GError **error);
#endif	/* SDPRINT_H */

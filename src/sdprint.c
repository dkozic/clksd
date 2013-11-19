#include <glib.h>
#include <sqlite3.h>
#include <hpdf.h>
#include <windows.h>
#include <CelikApi.h>
#include <setjmp.h>
#include "sd.h"
#include "sdprint.h"

jmp_buf env;

GQuark clksd_sdprint_error_quark()
{
    static GQuark q = 0;
    if (q == 0)
    {
        q = g_quark_from_static_string("clksd-sdprint-error");
    }
    return q;
}

static void hpdf_error_handler(HPDF_STATUS error_no,
                               HPDF_STATUS detail_no,
                               void *user_data)
{
    GError **error;
    error = (GError **)user_data;
    g_set_error(error, CLKSD_SDPRINT_ERROR, CLKSD_SDPRINT_ERROR_FAILED, "Can't generate pdf: error_no=%04X, detail_no=%u", (HPDF_UINT) error_no, (HPDF_UINT) detail_no);
    longjmp(env, 1);
}

static gchar *convert_string_lat (const gchar *str)
{
    gsize bytes_read;
    gsize bytes_written;
    GError *error = NULL;
    gchar *result = NULL;

    result = g_convert(str, -1, "ISO8859-2", "UTF-8", &bytes_read, &bytes_written, &error);
    if (error != NULL)
    {
        g_debug("Error in convert_string_lat: %s", error->message);
        g_error_free(error);
    }
    return result;
}

gboolean clksd_sdprint_print (Sd *sd, char *fname, GError **error)
{
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font lat_font;
    HPDF_REAL height;
    HPDF_REAL width;
    gchar *text;
    gchar *text1;

    const char *font_name;

    pdf = HPDF_New(hpdf_error_handler, error);
    if (!pdf)
    {
        g_set_error(error, CLKSD_SDPRINT_ERROR, CLKSD_SDPRINT_ERROR_NEW, "Can't create PdfDoc object");
        return FALSE;
    }

    if (setjmp(env))
    {
        HPDF_Free(pdf);
        return FALSE;
    }

    /* Add a new page object. */
    page = HPDF_AddPage(pdf);

    HPDF_Page_SetSize (page, HPDF_PAGE_SIZE_A4, HPDF_PAGE_PORTRAIT);

    height = HPDF_Page_GetHeight(page);
    width = HPDF_Page_GetWidth(page);

    font_name = HPDF_LoadTTFontFromFile (pdf, "fonts/arial.ttf", HPDF_TRUE);

    lat_font = HPDF_GetFont(pdf, font_name, "ISO8859-2");
    HPDF_Page_SetFontAndSize(page, lat_font, 14);

    /* Print the line of the page */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 50);
    HPDF_Page_LineTo(page, width - 50, height - 50);
    HPDF_Page_Stroke(page);

    /* Print the title */
    HPDF_Page_BeginText(page);
    text = convert_string_lat("ČITAČ SAOBRAĆAJNE DOZVOLE");
    HPDF_Page_TextOut(page, 50, height - 70, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 80);
    HPDF_Page_LineTo(page, width - 50, height - 80);
    HPDF_Page_Stroke(page);

    /* output registrationNumberOfVehicle */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Registarska oznaka: %s", sd->registrationNumberOfVehicle);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 100, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output issuingDate */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Datum izdavanja: %s", sd->issuingDate);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 135, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output expiryDate */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Važi do: %s", sd->expiryDate);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 135, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output stateIssuing */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Saobraćajnu izdao: %s", sd->stateIssuing);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 160, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output restrictionToChangeOwner */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Zabrana otuđenja: %s", sd->restrictionToChangeOwner);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 160, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output restrictionToChangeOwner */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("%s, %s", sd->authorityIssuing, sd->competentAuthority);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 185, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output unambiguousNumber */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj saobraćajne: %s", sd->unambiguousNumber);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 210, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output serialNumber */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj saobraćajne: %s", sd->serialNumber);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 235, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 265);
    HPDF_Page_LineTo(page, width - 50, height - 265);
    HPDF_Page_Stroke(page);

    /* Print the title */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Podaci o vlasniku");
    HPDF_Page_TextOut(page, 50, height - 280, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 285);
    HPDF_Page_LineTo(page, width - 50, height - 285);
    HPDF_Page_Stroke(page);

    /* output owner. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Vlasnik: %s", sd->ownersSurnameOrBusinessName);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 305, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output ownerName. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Ime vlasnika: %s", sd->ownerName);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 330, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output ownerAddress. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Adresa vlasnika: %s", sd->ownerAddress);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 355, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output ownersPersonalNo. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("JMBG vlasnika: %s", sd->ownersPersonalNo);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 380, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output usersSurnameOrBusinessName. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Korisnik: %s", sd->usersSurnameOrBusinessName);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 405, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output usersName. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Ime korisnika: %s", sd->usersName);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 430, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output usersAddress. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Adresa korisnika: %s", sd->usersAddress);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 455, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output usersPersonalNo. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("JMBG korisnika: %s", sd->usersPersonalNo);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 480, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 490);
    HPDF_Page_LineTo(page, width - 50, height - 490);
    HPDF_Page_Stroke(page);

    /* output label. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Podaci o vozilu: ");
    HPDF_Page_TextOut(page, 50, height - 505, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 510);
    HPDF_Page_LineTo(page, width - 50, height - 510);
    HPDF_Page_Stroke(page);

    /* output dateOfFirstRegistration. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Datum prve registracije: %s", sd->dateOfFirstRegistration);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 530, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output yearOfProduction. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Datum prve registracije: %s", sd->yearOfProduction);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 530, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output vehicleMake. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Marka: %s Model: %s", sd->vehicleMake, sd->commercialDescription);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 555, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output vehicleType. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Tip: %s Homologacijska oznaka: %s", sd->vehicleType, sd->typeApprovalNumber);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 580, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output colourOfVehicle. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Boja: %s", sd->colourOfVehicle);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 605, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output numberOfAxles. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj osovina: %s", sd->numberOfAxles);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 605, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output vehicleIDNumber. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj šasije: %s", sd->vehicleIDNumber);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 630, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output engineCapacity. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Zapremina motora: %s", sd->engineCapacity);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 630, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output engineIDNumber. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj motora: %s", sd->engineIDNumber);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 655, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output vehicleMass. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Masa: %s", sd->vehicleMass);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 655, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output maximumNetPower. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Snaga motora: %s", sd->maximumNetPower);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 680, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output vehicleLoad. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Nosivost: %s", sd->vehicleLoad);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 680, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output powerWeightRatio. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Odnos snaga/masa: %s", sd->powerWeightRatio);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 705, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output maximumPermissibleLadenMass. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Ukupna masa: %s", sd->maximumPermissibleLadenMass);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 705, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output vehicleCategory. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Kategorija: %s", sd->vehicleCategory);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 730, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output typeOfFuel. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Pogonsko gorivo: %s", sd->typeOfFuel);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 755, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output numberOfSeats. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj mesta za sedenje: %s", sd->numberOfSeats);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 50, height - 780, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output numberOfStandingPlaces. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("Broj mesta za stajanje: %s", sd->numberOfStandingPlaces);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 350, height - 780, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, 50);
    HPDF_Page_LineTo(page, width - 50, 50);
    HPDF_Page_Stroke(page);

    /* output footer. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 10);
    text = convert_string_lat("cLKSD");
    HPDF_Page_TextOut(page, 270, 40, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* save to file. */
    HPDF_SaveToFile(pdf, fname);

    /* clean up */
    HPDF_Free(pdf);

    return TRUE;

}

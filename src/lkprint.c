#include <glib.h>
#include <sqlite3.h>
#include <hpdf.h>
#include <windows.h>
#include <CelikApi.h>
#include <setjmp.h>
#include "lk.h"
#include "lkprint.h"

jmp_buf env;

GQuark clksd_lkprint_error_quark()
{
    static GQuark q = 0;
    if (q == 0)
    {
        q = g_quark_from_static_string("clksd-lkprint-error");
    }
    return q;
}

static void hpdf_error_handler(HPDF_STATUS error_no,
                               HPDF_STATUS detail_no,
                               void *user_data)
{
    GError **error;
    error = (GError **)user_data;
    g_set_error(error, CLKSD_LKPRINT_ERROR, CLKSD_LKPRINT_ERROR_FAILED, "Can't generate pdf: error_no=%04X, detail_no=%u", (HPDF_UINT) error_no, (HPDF_UINT) detail_no);
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

static gchar *convert_string_cyr (const gchar *str)
{
    gsize bytes_read;
    gsize bytes_written;
    GError *error = NULL;
    gchar *result = NULL;

    result = g_convert(str, -1, "ISO8859-5", "UTF-8", &bytes_read, &bytes_written, &error);
    if (error != NULL)
    {
        g_debug("Error in convert_string_cyr: %s", error->message);
        g_error_free(error);
    }
    return result;
}

gboolean clksd_lkprint_print (Lk *lk, char *fname, GError **error)
{
    HPDF_Doc pdf;
    HPDF_Page page;
    HPDF_Font lat_font;
    HPDF_Font cyr_font;
    HPDF_REAL height;
    HPDF_REAL width;
    HPDF_Image image;
    gchar *text, *text1;

    double iw;
    double ih;

    const char *font_name;

    pdf = HPDF_New(hpdf_error_handler, error);
    if (!pdf)
    {
        g_set_error(error, CLKSD_LKPRINT_ERROR, CLKSD_LKPRINT_ERROR_NEW, "Can't create PdfDoc object");
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
    cyr_font = HPDF_GetFont(pdf, font_name, "ISO8859-5");
    HPDF_Page_SetFontAndSize(page, lat_font, 14);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 50);
    HPDF_Page_LineTo(page, width - 50, height - 50);
    HPDF_Page_Stroke(page);

    /* Print the title */
    HPDF_Page_BeginText(page);
    text = convert_string_lat("ČITAČ ELEKTRONSKE LIČNE KARTE: ŠTAMPA PODATAKA");
    HPDF_Page_TextOut(page, 50, height - 70, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 80);
    HPDF_Page_LineTo(page, width - 50, height - 80);
    HPDF_Page_Stroke(page);

    /* Print image. */
    if (lk->portrait != NULL)
    {
        image = HPDF_LoadJpegImageFromMem(pdf, lk->portrait, lk->portraitSize);
        iw = HPDF_Image_GetWidth (image);
        ih = HPDF_Image_GetHeight (image);
        HPDF_Page_DrawImage(page, image, 50, height - 255, iw/2, ih/2);
    }

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 265);
    HPDF_Page_LineTo(page, width - 50, height - 265);
    HPDF_Page_Stroke(page);

    /* Print the title */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Podaci o građaninu");
    HPDF_Page_TextOut(page, 50, height - 280, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 285);
    HPDF_Page_LineTo(page, width - 50, height - 285);
    HPDF_Page_Stroke(page);

    /* output surname. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Prezime: ");
    HPDF_Page_TextOut(page, 50, height - 305, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, cyr_font, 12);
    text = convert_string_cyr(lk->surname);
    HPDF_Page_TextOut(page, 200, height - 305, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output name. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Ime: ");
    HPDF_Page_TextOut(page, 50, height - 330, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, cyr_font, 12);
    text = convert_string_cyr(lk->givenName);
    HPDF_Page_TextOut(page, 200, height - 330, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output parentGivenName. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Ime jednog roditelja: ");
    HPDF_Page_TextOut(page, 50, height - 355, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->parentGivenName);
    HPDF_Page_TextOut(page, 200, height - 355, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output dateOfBirth. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Datum rođenja: ");
    HPDF_Page_TextOut(page, 50, height - 380, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->dateOfBirth);
    HPDF_Page_TextOut(page, 200, height - 380, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output placeOfBirth. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Mesto rođenja: ");
    HPDF_Page_TextOut(page, 50, height - 405, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("%s, %s, %s", lk->placeOfBirth, lk->communityOfBirth, lk->stateOfBirth);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 200, height - 405, text);
    g_free(text);
    g_free(text1);
    HPDF_Page_EndText(page);

    /* output prebivaliste. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Prebivalište: ");
    HPDF_Page_TextOut(page, 50, height - 430, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text1 = g_strdup_printf("%s, %s, %s/%s", lk->place, lk->street, lk->houseNumber, lk->apartmentNumber);
    text = convert_string_lat(text1);
    HPDF_Page_TextOut(page, 200, height - 430, text);
    g_free(text1);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output personalNumber. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("JMBG: ");
    HPDF_Page_TextOut(page, 50, height - 455, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->personalNumber);
    HPDF_Page_TextOut(page, 200, height - 455, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output sex. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Pol: ");
    HPDF_Page_TextOut(page, 50, height - 480, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->sex);
    HPDF_Page_TextOut(page, 200, height - 480, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 490);
    HPDF_Page_LineTo(page, width - 50, height - 490);
    HPDF_Page_Stroke(page);

    /* output label. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Podaci o dokumentu: ");
    HPDF_Page_TextOut(page, 50, height - 505, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* Print the line of the page. */
    HPDF_Page_SetLineWidth(page, 0.5);
    HPDF_Page_MoveTo(page, 50, height - 510);
    HPDF_Page_LineTo(page, width - 50, height - 510);
    HPDF_Page_Stroke(page);

    /* output issuingAuthority. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Dokument izdaje: ");
    HPDF_Page_TextOut(page, 50, height - 530, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->issuingAuthority);
    HPDF_Page_TextOut(page, 200, height - 530, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output docRegNo. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Broj dokumenta: ");
    HPDF_Page_TextOut(page, 50, height - 555, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->docRegNo);
    HPDF_Page_TextOut(page, 200, height - 555, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output issuingDate. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Datum izdavanja: ");
    HPDF_Page_TextOut(page, 50, height - 580, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->issuingDate);
    HPDF_Page_TextOut(page, 200, height - 580, text);
    g_free(text);
    HPDF_Page_EndText(page);

    /* output expiryDate. */
    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat("Važi do: ");
    HPDF_Page_TextOut(page, 50, height - 605, text);
    g_free(text);
    HPDF_Page_EndText(page);

    HPDF_Page_BeginText(page);
    HPDF_Page_SetFontAndSize(page, lat_font, 12);
    text = convert_string_lat(lk->expiryDate);
    HPDF_Page_TextOut(page, 200, height - 605, text);
    g_free(text);
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

#include <glib.h>
#include "test_lk.h"
#include "test_lkdb.h"
#include "test_lkprint.h"
#include "test_lksc.h"

int main(int argc, char** argv)
{
    g_test_init(&argc, &argv, NULL);
    g_test_add_func("/clksd/lk/clksd_lk_Test0", clksd_lk_Test0);
    g_test_add_func("/clksd/lk/clksd_lk_Test1", clksd_lk_Test1);

    g_test_add_func("/clksd/lksc/clksd_lksc_Test0", clksd_lksc_Test0);

    g_test_add_func("/clksd/lkdb/clksd_lkdb_Test0", clksd_lkdb_Test0);

    g_test_add_func("/clksd/lkprint/clksd_lkprint_Test0", clksd_lkprint_Test0);
    return g_test_run();
}

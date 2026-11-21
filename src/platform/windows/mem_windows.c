#include "platform/mem.h"
#include <stdlib.h>
/* Preview only; never apply the TV's aggressive memory pressure thresholds. */
int plat_mem_free_mb(void) {
 const char *e=getenv("SB_MEMFREE"); return e?atoi(e):4096;
}
void plat_mem_self(int *rssMb,int *swapMb) {
 if(rssMb) *rssMb=-1;
 if(swapMb) *swapMb=-1;
}

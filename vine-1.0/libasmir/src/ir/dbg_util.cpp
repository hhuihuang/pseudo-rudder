#include <inttypes.h>
#include "H_vulscan_config.h"

#ifdef H_DEBUG_TEST
uint32_t dbg_interested_stmt;

void dbg_set_interested_IR_stmt(uint32_t stmt)
{
    dbg_interested_stmt = stmt;
}// end of dbg_set_interested_IR_stmt( )

#endif

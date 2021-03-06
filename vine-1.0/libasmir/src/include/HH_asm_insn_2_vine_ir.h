#ifndef H_HH_ASM_INSN_2_VINE_IR_H
    #define H_HH_ASM_INSN_2_VINE_IR_H

    #include <inttypes.h>
    #include "irtoir.h"
    #include "../ir/IR_operation.h"

    vine_block_t * HH_asm_insn_2_vine_ir( PIR_module_t module_entry,
					  uint32_t     insn_vaddr,
					  uint8_t *    insn_bytes,
				          uint32_t     insn_count
			 	        );

#endif

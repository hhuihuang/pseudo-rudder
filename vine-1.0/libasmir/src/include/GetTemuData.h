#ifndef H_GET_TEMU_DATA_H
	#define H_GET_TEMU_DATA_H

	using namespace std;

	// #include <string.h>
	#include <ctype.h>
	#include <inttypes.h>
	
	#include "H_cpu.h"

	#include "H_taint_record.h"



	// extern void (*H_term_printf)( const char * fstr, ... );

	
// 封装给 Temu 的插件的接口，以方便本模块得到 Temu 的相关信息
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
	
	// 读取机器信息
	void Set_HH_TEMU_concrete_read( uint32_t * con_regs,
					uint8_t    con_reg_bitmap,
					
					void *	   con_mem_list,
	
					int (* f_read_mem)(uint32_t vaddr, int len, void *buf),
			      		void (* f_read_register)(int reg_id, int reg_offset, int reg_size, void *buf),
	
					void (* f_write_mem)(uint32_t vaddr, int len, void *buf), 
					void (* f_write_register)(int reg_id, int reg_offset, int reg_size, void *buf),
		
					uint64_t (* f_taintcheck_memory_check)(uint32_t addr, int size,  uint8_t * records),
					uint64_t (* f_taintcheck_register_check)(int reg, int offset, int size, uint8_t * records),

					uint64_t (* f_taintcheck_taint_memory)(uint32_t addr, int size, uint64_t taint, uint8_t * records),
					uint64_t (* f_taintcheck_taint_register)(int reg, int offset, int size, uint64_t taint, uint8_t * records),

				        uint32_t * HH_vad_root,
					int ( *HH_build_symaddr_invalid_constraint)( HVC      hvc,
				        					     HExpr    symaddr_expr,
						  	            	             int      access_mode,      
										     /* 1 - read; 2 - write; 4 - execute */
									             uint32_t vad_root,
				        					     HExpr *  out_of_range_expr,
				       					 	     HExpr *  invalid_access_expr
			      	           					   ),

					void (*my_symaddr_obtain_stack_range_constraint)( HVC     hvc,
									     		  HExpr   symaddr,
									   	          HExpr * out_of_range_constraint
									        	)

				      );


	/*  封装给外部插件提供的完全接口，
   	    便于本部件获取 Temu 相关的信息外部的完全信息
 	  */
	void Get_HH_TEMU_Info( uint32_t * 	 TEMU_EFLAGS,   // TEMU_cpu_eflags
			       uint32_t *   	 TEMU_EIP,
			       uint32_t *  	 TEMU_CPU_REGS, // array of CPU general-purpose registers, such as R_EAX, R_EBX
			       tpage_entry_t **  tpage_table,

			       uint64_t * 	 regs_bitmap, 	//!<bitmap for registers
			       uint8_t  *	 regs_records,  //!<taint records for registers
	
			       uint32_t *	 eflags_bitmap, //!<bitmap for eflags
			       uint8_t  * 	 eflags_records //!<taint records for eflags			       
			     );
	
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
// 封装给 Temu 的插件的接口，以方便本模块得到 Temu 的相关信息



	
	

// 提供给符号执行的服务
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

	int GetTEMUReg_AccessIDByIndex( int index ) ;

	int GetReg_SizeByIndex(int index);

	int GetReg_Index(string name);

	char * GetRegNameByIndex(int index);

	int GetEFLAG_Bit_Index(string name);

	char * GetEFLAGBitNameByIndex(int index);

	


	// 具体机器状态的获取
	/* ================================================================= */		

	// 读取 TEMU 机器执行中的内存具体值
	void  GetConcreteMemData( uint32_t address, 
				  int 	   len, 
				  void *   buf
				);
	
	void SetConcreteMemData( uint32_t address,
				 int	  len,
				 void *   buf
			       );



	// 读取 TEMU 机器执行中的寄存器具体值
	uint32_t GetConcreteRegData( int reg_idx );
	
	void SetConcreteRegData( int reg_idx,
				 void * buf
			       );
	

	// 读取 TEMU 机器执行中的EFLAGS 的 bit 的具体值
	uint32_t GetConcreteEFLAGData( string bitname );

	void SetConcreteEFLAGData( int bit_index,
				   int bit_value
				 );
	/* ================================================================= */

	


	// 符号机器状态的获取
	// 要求用户预先分配缓冲区
	/* ================================================================= */
	uint64_t HH_Query_TemuRegisterTaintStatus( string 	      reg_name,
					           H_taint_record_t * h_reg_records
						 );

	
	uint32_t HH_Query_TemuEFLAGSTaintStatus( string       	    eflag_name,
						 H_taint_record_t * eflag_bit_expr
					       );


	uint64_t HH_Query_TemuMemTaintStatus( uint32_t    	   m_address,
					      int		   m_length,
					      H_taint_record_t *   h_taint_recoird
					    );
	/* ================================================================= */
	// 符号机器状态的获取



	// 符号机器状态的设置
	/* ================================================================= */
	void HH_symexe_taint_register( int reg_index,
				       int size,
				       H_taint_record_t *  taint_record
				     );



	int HH_Set_TemuRegisterByteTaintRecord( string	  	    reg_name,
				 		int		    taint_bitmap,
						H_taint_record_t *  taint_record
					      );


	int HH_Set_TemuEFAGSTaintRecord( int 		    index,  // Now input the real index !
					 H_taint_record_t * taint_record
				       );

	/*
	int HH_Set_TemuEFAGSTaintRecord( string	  	     bit_name,
					 H_taint_record_t *  taint_record
				       );
	*/


	// 设置特定内存字节的符号值
	void HH_Set_TemuMemByteTaintRecord( uint32_t  		address,
					    uint32_t		size,
				   	    uint64_t	 	taint_bitmap,
					    H_taint_record_t *  taint_record
					  );	
	/* ================================================================= */
	// 符号机器状态的设置

	HExpr obtain_expr_from_TEMU_virtmem( uint32_t vaddr,
					     int      size,
					     HVC      hvc
					   );


/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */ 
// 提供给符号执行的服务
	

	
#endif

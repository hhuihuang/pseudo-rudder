#ifndef H_SYMEXE_H


	#include "exp.h"
	#include "i386_reg_init.h"
	#include "H_STP_stub.h"

	#include "branch_save.h"

	
	extern int     symexe_error_fd_num;

	extern HExpr * HHui_current_path_expr;
	

	// symbolic execution for a single asm-instruction
	int symexe_asm_vine_block( HVC         hvc, 
				   HExpr *     global_path_expr,
				   HExpr *     local_path_expr,	   // only used by CJMPs !
				   // uint32_t *  ir_fbranch_eip,

				   int	       predicate,	   // real predicate !
				   uint32_t    tbranch,
				   uint32_t    fbranch,
				   
				   BRANCH_SAVE mybranch_save 
				   // int	       error_fd_num      // seq_num of file records ERROR path-expression
				 );


	// look-up the index for the temp variable
	int  Find_VarDecl( string temp_name);

	
	// retrieve the right-value for temp variable by the index in SymbolTable
	H_R_VALUE * GetVarDecl_ValueByIndex( int index );

	
	// get the type of the temp variable by index in SymbolTable
	reg_t GetVarDecl_TypeByIndex(int index);

	
	// set the right value for the temp variable by its index in SymbolTables 
	void SetVarDecl_ValueByIndex( int 	  index, 
			  	      H_R_value * h_r_value
			    	    );
	

	extern int stp_fd;


	
	// concrete value for predicate in JCC
	// extern int jcc_predicate_value;

#endif

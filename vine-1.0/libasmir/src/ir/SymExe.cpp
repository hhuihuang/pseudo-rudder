#include <inttypes.h>

#include "irtoir.h"

#include "stmt.h"

//#include "taintcheck.h"
#include "i386_reg_init.h"

// #include "hc_interface.h"
#include "SymExe.h"

#include <fcntl.h>

#include "H_STP_stub.h"
#include "branch_save.h"

#include "label_queue.h"

#ifndef H_STP_FILE_NAME
    #define H_STP_FILE_NAME "./stp.record"
#endif

#include "H_vulscan_config.h"
#include "HH_IR_translate_config.h"

#ifdef H_DEBUG_TEST
extern uint32_t dbg_interested_stmt;
#endif

using namespace std;


/*
	struct vine_block_s
	{
	  Instruction     *inst;
	  IRSB            *vex_ir;
	  vector<Stmt *>  *vine_ir;
	};

  */


// concrete value for predicate in JCC
// int jcc_predicate_value;


extern uint32_t GetConcreteEFLAGData( string bitname );

extern vine_block_t  *  current_vine_block ;
extern asm_program_t *  prog_t;


extern int * H_vulscan_once_enough_err_found;

int stp_fd;

#ifndef H_term_printf_H
   #define H_term_printf_H
   extern void (*H_term_printf)( const char * fstr, ... );
#endif

// 通用寄存器、EFLAGS   标记位等的声明
// vector<VarDecl *>  reg_decls ;


// 具体指令的临时变量声明列表
vector<VarDecl *>  temp_decls ;


void delete_vine_ir_block( )
{
    delete (current_vine_block->inst);
    delete (current_vine_block->vine_ir);

    // As VEX-IRs are all allocated by vx_Alloc( ), calling vx_FreeAll( ) would be enough ! 
    vx_FreeAll( );

    // delete (current_vine_block->vex_ir);
    delete current_vine_block;
}// end of delete_vine_ir_block( )


/* ---------------------------------------------------- */


/*  一条指令对应的符号执行。最终更新相关的符号记录
    注意:
    		  目前的实现为在对应的具体指令刚刚开始执行的时刻.
    		  污点状态已经传递,    而本函数的作用即在于为对应的污
    		  点计算相应的符号表达式
  */

/*  参数为当前具体指令之前的机器的污点情况和对应的
     符号机器状态
  */
  
/*
    symexe_asm_vine_block( HHui_VC,
			   &predicate_expr,
			   &branch_addr,

			   H_predicate,
			   tbranch,
			   fbranch,
			   branch_save   
			 );
 */

HExpr * HHui_current_path_expr = NULL;

HVC HHui_HVC  = NULL;

int StmtIsREP = 0;
int LastREP   = 0; // denoting the last instruction is the last one in the REP sequence.

uint32_t HHui_insn_addr = 0;


int symexe_asm_vine_block( HVC         hvc, 
			   HExpr *     global_path_expr,
			   HExpr *     local_path_expr,	   // only used by CJMPs !
			   // uint32_t *  ir_fbranch_eip,

			   int	       predicate,	   // real predicate !
			   uint32_t    tbranch,
			   uint32_t    fbranch,			   
			   BRANCH_SAVE mybranch_save,      // branch-saving util provided by TEMU-plugin

			   int	       isREP
			 )
{	
	HHui_HVC = hvc;
	/*
	if( (StmtIsREP == 0) && 
	    (isREP != 0)
	  )
	{
	    StmtIsREP = 1;
	}// end of if(StmtIsREP)
	*/
	if( (isREP == 0) &&
	    (StmtIsREP == 1)
	  )
	{
	    LastREP = 1;
	}// end of if()

	StmtIsREP = isREP;

	HHui_current_path_expr = global_path_expr;

	vector<Stmt *>  * vine_irs = current_vine_block->vine_ir;

	init_label_queues( );
	
	uint32_t label_id   = 0;
	int	 label_type = 0;
	int 	 j	    = 0;
	int	 total_size = 0;

	VarDecl * temp_vardecl = NULL;

	for( j = 0; j< vine_irs->size(); j++ )
	{
	    if( vine_irs->at(j)->stmt_type == LABEL)
	    {
		( (Label *)( vine_irs->at(j)
			   )
		)->pre_parse( &label_type,
			      &label_id
			    );

		/* we assume that the first stmt of every vine-IR-block 
		   would be the label with the insn's pc-address !
		 */
		if(j == 0)
		{
		    HHui_insn_addr = label_id;
		}// end of if(j)

		label_queue_add_entry( label_type,
				       label_id,   // stmt's name 
				       j	   // stmt's index in the vector
			  	     );

	    }// end of if( )

	}// end of for{ }

	i386_reg_init( );


	/* --------------------------------------------------------------------------------------------------------- */

	// temporary-variables !
	if(temp_decls.size( ) != 0 )
	{
	    total_size = temp_decls.size( );

	    // Just retain the 4 CC_OP-like VarDecls in list !
	    for(j = 4; j < total_size; j=j+1)
	    {
		temp_decls.pop_back( );
	    }// end of for{ }
	}
	else
	{
	    temp_vardecl = new VarDecl( "R_CC_OP",
				 	REG_32
				      );
	    (temp_vardecl->H_value).r_value_type      = R_CON_VALUE;
	    ((temp_vardecl->H_value).r_value).value   = 0;
	    (temp_vardecl->H_value).r_value_bits_size = 32;
	    temp_decls.push_back(temp_vardecl);	

  	    temp_vardecl = new VarDecl( "R_CC_DEP1",
				        REG_32
				      );
	    (temp_vardecl->H_value).r_value_type      = R_CON_VALUE;
	    ((temp_vardecl->H_value).r_value).value   = 0;
	    (temp_vardecl->H_value).r_value_bits_size = 32;
	    temp_decls.push_back(temp_vardecl);

	    temp_vardecl = new VarDecl( "R_CC_DEP2",
				        REG_32
				      );
	    (temp_vardecl->H_value).r_value_type      = R_CON_VALUE;
	    ((temp_vardecl->H_value).r_value).value   = 0;
	    (temp_vardecl->H_value).r_value_bits_size = 32;
 	    temp_decls.push_back(temp_vardecl);

	    temp_vardecl = new VarDecl( "R_CC_NDEP",
				        REG_32
				      );
	    (temp_vardecl->H_value).r_value_type      = R_CON_VALUE;
	    ((temp_vardecl->H_value).r_value).value   = 0;
	    (temp_vardecl->H_value).r_value_bits_size = 32;
	    temp_decls.push_back(temp_vardecl);
	}// end of if( )        

        // R_DFLAG:reg32_t
  	/* =================================================================================== */
	temp_vardecl = new VarDecl( "R_DFLAG",
				    REG_32
				  );
	(temp_vardecl->H_value).r_value_type = R_CON_VALUE;

	uint8_t DF_value = GetConcreteEFLAGData("R_DF");	
	if(DF_value == 0)
	{
	    ((temp_vardecl->H_value).r_value).value = 1;
	}
	else
	{
	    ((temp_vardecl->H_value).r_value).value = -1;
	}// end of if( )

	(temp_vardecl->H_value).r_value_bits_size = 32;
	temp_decls.push_back(temp_vardecl);
  	/* =================================================================================== */
        // R_DFLAG:reg32_t

	/* --------------------------------------------------------------------------------------------------------- */
        


	VarDecl * new_vardecl	   = NULL;

	int next_stmt 	   = -1;	
	int next_stmt_type = -1;

	for ( int i = 0; i< vine_irs->size(); )
    	{
	/*
	#ifdef H_DEBUG_TEST
	    if(i == dbg_interested_stmt)
	    {
		H_term_printf( "IR_SYMEXE: dbg-interested-stmt = %d\n",
			       dbg_interested_stmt
			     );
	    }// end of if(i)
	#endif
	*/

	#ifdef H_VULSCAN_ONCE_ENOUGH
	    if(*H_vulscan_once_enough_err_found != 0)
	    {
		return 0;
	    }// end of if(*H_vulscan_once_enough_err_found)
	#endif

    	    //  临时变量声明----  加入临时变量符号表
    	    if( vine_irs->at(i)->stmt_type == VARDECL )
    	    {
	        new_vardecl = new VarDecl(  *( (VarDecl *)( vine_irs->at(i) ) 
					     ) 
				   	 );

		// indicating temp-variable !
		new_vardecl->var_type = 2;		  
			
    	    	temp_decls.push_back(new_vardecl);
		  
    	    }
	    else if( vine_irs->at(i)->stmt_type == CJMP )
	    {	    
	        next_stmt = ( (CJmp *)( vine_irs->at(i) ) )->symexe_pathvc( hvc,
									    global_path_expr,
							        	    local_path_expr,
						
									    predicate,
									    tbranch,
									    fbranch,
									    mybranch_save,
									    
									    &next_stmt_type,
			   						    isREP
							      		  );
	    }
	    else if( vine_irs->at(i)->stmt_type != COMMENT )
	    {
	        vine_irs->at(i)->symexe( hvc,
					 *global_path_expr // current-path-constraint
				       );
	    }// end of if( )
	    
	    /*
	    H_term_printf( "\n ===IR stmt %d executed ! =\n  ",
			   i
			 );	  
	    */

	    // virtual address
	    if(next_stmt_type != -1)
	    {
		 i = fetch_stmtid_by_content( next_stmt_type,
				    	      next_stmt
			   		    );
		if(i == -1)
		{
		    break;
		}// end of if( )

	    }
	    else
	    {
		i = i + 1;
		// break;
	    }// end of if( )
 
	    next_stmt_type = -1;

	    /*  
	    H_term_printf( "IR stmt %d executed -- ",
			   i
			 );
	    */
       }// end of for{i}
       

       // For REP instruction, We would make and apply to TEMU the summary at the end of the ocurring sequence.
       /*
       if(LastREP == 1)
       {
	   
       }// end of if(LastREP)
       */

       LastREP = 0;

       delete_label_queues( );

       // H_term_printf("OK! sym-exe finished !\n");

       return 0 ;

}//symexe_vine_block(vine_block_t * vine_block )



// 临时变量的属性计算
/* ======================================================================================================================= */

// 返回对应的临时变量在当前指令的临时变量列表中的索引位置
int  Find_VarDecl( string temp_name)
{
	/*
	H_term_printf( "temp variable's name is %s\n",
		       temp_name.c_str( )
		     );
	*/

	VarDecl * decl = NULL ;
		
	for ( int i = 0; i< temp_decls.size( ); i++ )
	{
		decl = temp_decls.at(i) ;
		if( strcmp( (decl->name).c_str( ),
			    temp_name.c_str( ) 
			  ) == 0  
		  )
		{
		    // H_term_printf(" temp_decls --- found !\n");
		    return i;
		}// end of if( )
		
	}// end of for{ }

	return -1;
}// end of Find_VarDecl( )



H_R_VALUE * GetVarDecl_ValueByIndex( int index )
{
	VarDecl * decl = temp_decls.at(index) ;


	return  &(decl->H_value);
}// end of GetVarDecl_ValueByIndex( )


reg_t GetVarDecl_TypeByIndex(int index)
{
	VarDecl * decl = temp_decls.at(index) ;
	
	return decl->typ;
}// end of GetVarDecl_TypeByIndex( )



void SetVarDecl_ValueByIndex( int 	  index, 
			      H_R_value * h_r_value
			    )
{
	VarDecl * decl = temp_decls.at(index) ;
	
	(decl->H_value).r_value_type 	  = h_r_value->r_value_type;
	(decl->H_value).r_value_bits_size  = h_r_value->r_value_bits_size;

	if( (decl->H_value).r_value_type == R_CON_VALUE)
	{
		(decl->H_value).r_value.value 	    = (h_r_value->r_value).value;
	}
	else 
	{
		(decl->H_value).r_value.expression = (h_r_value->r_value).expression;
	}// end of if( )		
		
	
}//end of SetVarDecl_ValueByIndex( )

/* ======================================================================================================================= */



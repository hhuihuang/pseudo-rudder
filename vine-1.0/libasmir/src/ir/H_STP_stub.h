/********************************************************************
 * AUTHORS: Vijay Ganesh, David L. Dill
 *
 * BEGIN DATE: November, 2005
 *
 * LICENSE: Please view LICENSE file in the home dir of this Program
 ********************************************************************/
// -*- c++ -*-
#ifndef _cvcl__include__c_interface_h_
#define _cvcl__include__c_interface_h_

#ifndef __cplusplus
    #define __cplusplus
#endif


#ifdef __cplusplus
extern "C" {
#endif


  //This gives absolutely no pointer typing at compile-time. Most C
  //users prefer this over stronger typing. User is the king. A
  //stronger typed interface is in the works.
  typedef void* HVC;
  typedef void* HExpr;
  typedef void* HType;



  // o  : optimizations
  // c  : check counterexample
  // p  : print counterexample
  // h  : help
  // s  : stats
  // v  : print nodes
  typedef void (*VC_SETFLAGS)(char c);
         
  //! Flags can be NULL
  typedef HVC (*VC_CREATEVALIDITYCHECKER)(void);
  		
  // Basic types
  typedef HType (*VC_BOOLTYPE)(HVC vc);
	  

  //! Create an array type
  typedef HType (*VC_ARRAYTYPE)( HVC   vc,
				 HType typeIndex, 
				 HType typeData
			       );
  

  /////////////////////////////////////////////////////////////////////////////
  // Expr manipulation methods                                               //
  /////////////////////////////////////////////////////////////////////////////

  //! Create a variable with a given name and type 
  /*! The type cannot be a function type. The var name can contain
    only variables, numerals and underscore. If you use any other
    symbol, you will get a segfault. */  
  typedef HExpr (*VC_VAREXPR)( HVC    vc, 
			       char * name, 
			       HType  type
			     );
	

  //The var name can contain only variables, numerals and
  //underscore. If you use any other symbol, you will get a segfault.
  typedef HExpr (*VC_VAREXPR1)( HVC   vc, 
			     	char* name, 
		  	     	int   indexwidth, 
			     	int   valuewidth
			      );

		

  typedef int (*VC_GETBVLENGTH)(HVC vc, HExpr e);//		   myvc_getBVLength

  //! Get the expression and type associated with a name.
  /*!  If there is no such Expr, a NULL Expr is returned. */
  //Expr vc_lookupVar(VC vc, char* name, Type* type);
  
  //! Get the type of the Expr.
  typedef HType (*VC_GETTYPE)( HVC   vc, 
			       HExpr e
			     );
    

  //! Create an equality expression.  The two children must have the same type.
  typedef HExpr (*VC_EQEXPR)(HVC vc, HExpr child0, HExpr child1);
  
  // Boolean expressions
  
  // The following functions create Boolean expressions.  The children provided
  // as arguments must be of type Boolean.
  typedef HExpr (*VC_TRUEEXPR)(HVC vc);
  typedef HExpr (*VC_FALSEEXPR)(HVC vc);
  typedef HExpr (*VC_NOTEXPR)(HVC vc, HExpr child);

  typedef HExpr (*VC_ANDEXPR)( HVC vc, 
			       HExpr left, 
			       HExpr right
			     );

  typedef HExpr (*VC_ANDEXPRN)( HVC    vc, 
				HExpr* children, 
				int    numOfChildNodes
			      );

  typedef HExpr (*VC_OREXPR)( HVC   vc, 
			      HExpr left,
			      HExpr right
			    );

  typedef HExpr (*VC_OREXPRN)( HVC    vc, 
			       HExpr* children, 
			       int    numOfChildNodes
			     );

  // ->
  typedef HExpr (*VC_IMPLIESEXPR)( HVC   vc, 
				   HExpr hyp, 
				   HExpr conc
				 );
  
  typedef HExpr (*VC_IFFEXPR)( HVC   vc, 
			       HExpr left, 
			       HExpr right
			     );

  // if --- then --- else
  typedef HExpr (*VC_ITEEXPR)( HVC   vc, 
			       HExpr ifpart, 
			       HExpr thenpart, 
			       HExpr elsepart
			     );

  
  //Boolean to single bit BV Expression
  typedef HExpr (*VC_BOOLTOBVEXPR)( HVC   vc, 
				    HExpr form
			          );

  // Arrays

/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
  //! Create an expression for the value of array at the given index
  typedef HExpr (*VC_READEXPR)( HVC   vc, 
				HExpr array, 
				HExpr index
			      );

  //! Array update; equivalent to "array WITH [index] := newValue"
  typedef HExpr (*VC_WRITEEXPR)( HVC   vc, 
			      	 HExpr array, 
			      	 HExpr index, 
			      	 HExpr newValue
			       );
/* ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */  


  // Expr I/O
  //! Expr vc_parseExpr(VC vc, char* s);

  //! Prints 'e' to stdout.
  typedef void (*VC_PRINTEXPR)( HVC   vc, 
			        HExpr e
			      );

  //! Prints 'e' into an open file descriptor 'fd'
  typedef void (*VC_PRINTEXPRFILE)( HVC   vc, 
				    HExpr e, 
				    int   fd
				  );

  //! Prints state of 'vc' into malloc'd buffer '*buf' and stores the 
  //  length into '*len'.  It is the responsibility of the caller to 
  //  free the buffer.
  typedef void (*VC_PRINTSTATETOBUFFER)( HVC    	vc, 
					 char **	buf, 
					 unsigned long *len
				       );

  //! Prints 'e' to malloc'd buffer '*buf'.  Sets '*len' to the length of 
  //  the buffer. It is the responsibility of the caller to free the buffer.
  typedef void (*VC_PRINTEXPRTOBUFFER)( HVC    	        vc, 
				        HExpr  	        e, 
				        char **	        buf, 
				        unsigned long * len
				      );

  //! Prints counterexample to stdout.
  typedef void (*VC_PRINTCOUNTEREXAMPLE)(HVC vc);

  //! Prints variable declarations to stdout.
  typedef void (*VC_PRINTVARDECLS)(HVC vc);

  //! Prints asserts to stdout.
  typedef void (*VC_PRINTASSERTS)(HVC vc);

  //! Prints the state of the query to malloc'd buffer '*buf' and stores
  //! the length of the buffer to '*len'.  It is the responsibility of the
  //  caller to free the buffer.
  typedef void (*VC_PRINTQUERYSTATETOBUFFER)( HVC	      vc, 
					      HExpr 	      e,
					      char **	      buf,
					      unsigned long * len
					    );

  //! Prints query to stdout.
  typedef void (*VC_PRINTQUERY)(HVC vc);

  /////////////////////////////////////////////////////////////////////////////
  // Context-related methods                                                 //
  /////////////////////////////////////////////////////////////////////////////
  
  //! Assert a new formula in the current context.  
  /*! The formula must have Boolean type. */
  typedef void (*VC_ASSERTFORMULA)( HVC   vc, 
				    HExpr e
				  );
  
  //! Simplify e with respect to the current context
  typedef HExpr (*VC_SIMPLIFY)( HVC   vc, 
				HExpr e
			      );
  
  //! Check validity of e in the current context. e must be a FORMULA
  //
  //if returned 0 then input is INVALID. 
  //
  //if returned 1 then input is VALID
  //
  //if returned 2 then ERROR
  typedef int (*VC_QUERY)( HVC   vc, 
			   HExpr e
			 );
  
  //! Return the counterexample after a failed query.
  typedef HExpr (*VC_GETCOUNTEREXAMPLE)( HVC  vc, 
					 HExpr e
				       );

  //! get size of counterexample, i.e. the number of variables/array
  //locations in the counterexample.
  typedef int (*VC_COUNTEREXAMPLE_SIZE)(HVC vc);
  
  //! Checkpoint the current context and increase the scope level
  typedef void (*VC_PUSH)(HVC vc);
  
  //! Restore the current context to its state at the last checkpoint
  typedef void (*VC_POP)(HVC vc);
  
  //! Return an int from a constant bitvector expression
  typedef int (*GETBVINT)(HExpr e);


  //! Return an unsigned int from a constant bitvector expression
  typedef unsigned int (*GETBVUNSIGNED)(HExpr e);


  //! Return an unsigned long long int from a constant bitvector expressions
  typedef unsigned long long int (*GETBVUNSIGNEDLONGLONG)(HExpr e);
  
  /**************************/
  /* BIT VECTOR OPERATIONS  */
  /**************************/
  typedef HType (*VC_BVTYPE)( HVC vc, 
			      int no_bits
			    );

  typedef HType (*VC_BV32TYPE)(HVC vc);
  
  typedef HExpr (*VC_BVCONSTEXPRFROMSTR)( HVC   vc, 
				          char* binary_repr
				        );


  typedef HExpr (*VC_BVCONSTEXPRFROMINT)( HVC	       vc, 
					  int 	       n_bits, 
					  unsigned int value
					);


  typedef HExpr (*VC_BVCONSTEXPRFROMLL)( HVC		    vc, 
					 int		    n_bits, 
					 unsigned long long value
				       );


  typedef HExpr (*VC_BV32CONSTEXPRFROMINT)( HVC 	 vc, 
					    unsigned int value
					  );
  
  typedef HExpr (*VC_BVCONCATEXPR)( HVC   vc, 
				    HExpr left, 
				    HExpr right
				  );

  typedef HExpr (*VC_BVPLUSEXPR)( HVC   vc, 
				  int   n_bits, 
				  HExpr left, 
				  HExpr right
				);


  typedef HExpr (*VC_BV32PLUSEXPR)( HVC   vc, 
				    HExpr left, 
				    HExpr right
				  );


  typedef HExpr (*VC_BVMINUSEXPR)( HVC   vc, 
				   int   n_bits, 
				   HExpr left, 
				   HExpr right
				 );


  typedef HExpr (*VC_BV32MINUSEXPR)( HVC   vc, 
				     HExpr left, 
				     HExpr right
				   );


  typedef HExpr (*VC_BVMULTEXPR)( HVC   vc, 
				  int   n_bits, 
				  HExpr left, 
				  HExpr right
				);

  typedef HExpr (*VC_BV32MULTEXPR)( HVC   vc, 
				    HExpr left,
				    HExpr right
				  );

  // left divided by right i.e. left/right
  typedef HExpr (*VC_BVDIVEXPR)( HVC   vc, 
				 int   n_bits, 
				 HExpr left, 
				 HExpr right
			       );

  // left modulo right i.e. left%right
  typedef HExpr (*VC_BVMODEXPR)( HVC   vc, 
				 int   n_bits, 
				 HExpr left, 
				 HExpr right
			       );


  // left divided by right i.e. left/right
  typedef HExpr (*VC_SIGNBVDIVEXPR)( HVC   vc, 
				     int   n_bits, 
				     HExpr left, 
				     HExpr right
				   );


  // left modulo right i.e. left%right
  typedef HExpr (*VC_SIGNBVMODEXPR)( HVC   vc, 
				     int   n_bits, 
				     HExpr left, 
				     HExpr right
				   );

  // <
  typedef HExpr (*VC_BVLTEXPR)( HVC   vc, 
				HExpr left, 
				HExpr right
			      );

  // <=
  typedef HExpr (*VC_BVLEEXPR)( HVC   vc, 
				HExpr left, 
				HExpr right
			      );

  // >
  typedef HExpr (*VC_BVGTEXPR)( HVC   vc, 
				HExpr left, 
				HExpr right
			      );

  // >=
  typedef HExpr (*VC_BVGEEXPR)( HVC   vc, 
				HExpr left, 
				HExpr right
			      );

  
  typedef HExpr (*VC_SBVLTEXPR)( HVC   vc, 
				 HExpr left, 
				 HExpr right
			       );

  typedef HExpr (*VC_SBVLEEXPR)( HVC   vc, 
				 HExpr left, 
				 HExpr right
			       );


  typedef HExpr (*VC_SBVGTEXPR)( HVC   vc, 
				 HExpr left, 
				 HExpr right
			       );

  typedef HExpr (*VC_SBVGEEXPR)( HVC   vc, 
				 HExpr left, 
				 HExpr right
			       );
  
  typedef HExpr (*VC_BVUMINUSEXPR)( HVC   vc, 
				    HExpr child
				  );

  // bitwise operations: these are terms not formulas  
  typedef HExpr (*VC_BVANDEXPR)( HVC   vc, 
				 HExpr left, 
				 HExpr right
			       );


  typedef HExpr (*VC_BVOREXPR)( HVC   vc, 
				HExpr left, 
				HExpr right
			      );

  typedef HExpr (*VC_BVXOREXPR)( HVC   vc, 
				 HExpr left, 
				 HExpr right
			       );

  typedef HExpr (*VC_BVNOTEXPR)( HVC   vc, 
				 HExpr child
			       );

  
  typedef HExpr (*VC_BVLEFTSHIFTEXPR)( HVC   vc, 
				       int   sh_amt, 
				       HExpr child
				     );


  typedef HExpr (*VC_BVRIGHTSHIFTEXPR)( HVC   vc, 
					int   sh_amt, 
					HExpr child
				      );


  /* Same as vc_bvLeftShift only that the answer in 32 bits long */
  typedef HExpr (*VC_BV32LEFTSHIFTEXPR)( HVC   vc, 
					 int   sh_amt, 
					 HExpr child
				       );


  /* Same as vc_bvRightShift only that the answer in 32 bits long */
  typedef HExpr (*VC_BV32RIGHTSHIFTEXPR)( HVC   vc, 
					  int   sh_amt, 
					  HExpr child
					);


  typedef HExpr (*VC_BVVAR32LEFTSHIFTEXPR)( HVC   vc, 
					    HExpr sh_amt, 
					    HExpr child
					  );

  typedef HExpr (*VC_BVVAR32RIGHTSHIFTEXPR)( HVC   vc, 
					     HExpr sh_amt, 
					     HExpr child
					   );


  typedef HExpr (*VC_BVVAR32DIVBYPOWEROFTWOEXPR)( HVC   vc, 
						  HExpr child, 
						  HExpr rhs
						);

  typedef HExpr (*VC_BVEXTRACT)( HVC   vc, 
				 HExpr child, 
				 int   high_bit_no, 
			  	 int   low_bit_no
			       );


  typedef HExpr (*VC_BVBOOLEXTRACT)( HVC   vc, 
				     HExpr child, 
				     int   bit_no
				   );  

  typedef HExpr (*VC_BVSIGNEXTEND)( HVC   vc, 
				    HExpr child, 
				    int   nbits
				  );
  
  /*C pointer support:  C interface to support C memory arrays in CVCL */
  typedef HExpr (*VC_BV_CREATEMEMORYARRAY)( HVC    vc, 
					    char * arrayName
					  );
  typedef HExpr (*VC_BVREADMEMORYARRAY)( HVC   vc, 
			  		 HExpr array, 
					 HExpr byteIndex, 
					 int   numOfBytes
				       );
  
  typedef HExpr (*VC_BVWRITETOMEMORYARRAY)( HVC   vc, 
			       		    HExpr array, 
					    HExpr byteIndex, 
					    HExpr element, 
					    int   numOfBytes
					  );
  
  /*
  typedef HExpr (*VC_BV32CONSTEXPRFROMINT)( HVC		 vc, 
					    unsigned int value
					  );
  */  

  typedef char* (*EXPRSTRING)(HExpr e);
  
  typedef char* (*TYPESTRING)(HType t);

  typedef HExpr (*GETCHILD)( HExpr e, 
			     int   i
			   );


  //1.if input expr is TRUE then the function returns 1;
  //
  //2.if input expr is FALSE then function returns 0;
  //
  //3.otherwise the function returns -1
  typedef int (*VC_ISBOOL)(HExpr e);

  /* Register the given error handler to be called for each fatal error.*/
  typedef void (*VC_REGISTERERRORHANDLER)( void (*error_hdlr)(const char* err_msg) );

  typedef int (*VC_GETHASHQUERYSTATETOBUFFER)( HVC   vc, 
					       HExpr query
					     );

  //destroys the STP instance, and removes all the created expressions
  typedef void (*VC_DESTROY)(HVC vc);

#ifdef __cplusplus
};
#endif

extern void Obtain_stp_utils_From_plugin( VC_CREATEVALIDITYCHECKER   myvc_createValidityChecker,
				   VC_SETFLAGS		      myvc_setFlags,

				   VC_BOOLTYPE		   myvc_boolType,
				VC_ARRAYTYPE  		   myvc_arrayType,

				VC_VAREXPR		   myvc_varExpr,
				VC_VAREXPR1		   myvc_varExpr1,


				VC_GETTYPE		   myvc_getType,
				VC_GETBVLENGTH		   myvc_getBVLength,

				VC_EQEXPR		   myvc_eqExpr,
				VC_TRUEEXPR		   myvc_trueExpr,
				VC_FALSEEXPR		   myvc_falseExpr,

				VC_NOTEXPR		   myvc_notExpr,
				VC_ANDEXPR		   myvc_andExpr,
				VC_ANDEXPRN		   myvc_andExprN,
				VC_OREXPR		   myvc_orExpr,
				VC_OREXPRN		   myvc_orExprN,
				VC_IMPLIESEXPR		   myvc_impliesExpr,
				VC_IFFEXPR		   myvc_iffExpr,
				VC_ITEEXPR		   myvc_iteExpr,

				VC_BOOLTOBVEXPR		   myvc_boolToBVExpr,

				VC_READEXPR		   myvc_readExpr,
				VC_WRITEEXPR		   myvc_writeExpr,

				VC_PRINTEXPR 		   myvc_printExpr,
				VC_PRINTEXPRFILE	   myvc_printExprFile,
				VC_PRINTSTATETOBUFFER      myvc_printStateToBuffer,
				VC_PRINTEXPRTOBUFFER	   myvc_printExprToBuffer,

				VC_PRINTCOUNTEREXAMPLE     myvc_printCounterExample,
				VC_PRINTVARDECLS	   myvc_printVarDecls,
				VC_PRINTASSERTS		   myvc_printAsserts,

				VC_PRINTQUERYSTATETOBUFFER myvc_printQueryStateToBuffer,
				VC_PRINTQUERY		   myvc_printQuery,
				VC_ASSERTFORMULA	   myvc_assertFormula,

				VC_SIMPLIFY		   myvc_simplify,
				VC_QUERY		   myvc_query,

				VC_GETCOUNTEREXAMPLE	   myvc_getCounterExample,
				VC_COUNTEREXAMPLE_SIZE     myvc_counterexample_size,

				VC_PUSH			   myvc_push,
				VC_POP			   myvc_pop,

				GETBVINT		   mygetBVInt,
				GETBVUNSIGNED		   mygetBVUnsigned,
				GETBVUNSIGNEDLONGLONG	   mygetBVUnsignedLongLong,


				VC_BVTYPE		   myvc_bvType,
				VC_BV32TYPE		   myvc_bv32Type,

				VC_BVCONSTEXPRFROMSTR	   myvc_bvConstExprFromStr,
				VC_BVCONSTEXPRFROMINT      myvc_bvConstExprFromInt,
				VC_BVCONSTEXPRFROMLL	   myvc_bvConstExprFromLL,
				VC_BV32CONSTEXPRFROMINT    myvc_bv32ConstExprFromInt,

				VC_BVCONCATEXPR		   myvc_bvConcatExpr,

				VC_BVPLUSEXPR		   myvc_bvPlusExpr,
				VC_BV32PLUSEXPR		   myvc_bv32PlusExpr,

				VC_BVMINUSEXPR		   myvc_bvMinusExpr,
				VC_BV32MINUSEXPR	   myvc_bv32MinusExpr,

				VC_BVMULTEXPR		   myvc_bvMultExpr,
				VC_BV32MULTEXPR		   myvc_bv32MultExpr,

				VC_BVDIVEXPR		   myvc_bvDivExpr,
				VC_BVMODEXPR		   myvc_bvModExpr,
				VC_SIGNBVDIVEXPR	   myvc_sbvDivExpr,
				VC_SIGNBVMODEXPR	   myvc_sbvModExpr,

				VC_BVLTEXPR		   myvc_bvLtExpr,
				VC_BVLEEXPR		   myvc_bvLeExpr,

				VC_BVGTEXPR		   myvc_bvGtExpr,
				VC_BVGEEXPR		   myvc_bvGeExpr,


				VC_SBVLTEXPR		   myvc_sbvLtExpr,
				VC_SBVLEEXPR		   myvc_sbvLeExpr,

				VC_SBVGTEXPR		   myvc_sbvGtExpr,
				VC_SBVGEEXPR		   myvc_sbvGeExpr,

				VC_BVUMINUSEXPR		   myvc_bvUMinusExpr,

				VC_BVANDEXPR		   myvc_bvAndExpr,
				VC_BVOREXPR		   myvc_bvOrExpr,
				VC_BVXOREXPR		   myvc_bvXorExpr,
				VC_BVNOTEXPR		   myvc_bvNotExpr,

				VC_BVLEFTSHIFTEXPR	   myvc_bvLeftShiftExpr,
				VC_BVRIGHTSHIFTEXPR	   myvc_bvRightShiftExpr,

				VC_BV32LEFTSHIFTEXPR	   myvc_bv32LeftShiftExpr,
				VC_BV32RIGHTSHIFTEXPR	   myvc_bv32RightShiftExpr,

				VC_BVVAR32LEFTSHIFTEXPR	   myvc_bvVar32LeftShiftExpr,
				VC_BVVAR32RIGHTSHIFTEXPR   myvc_bvVar32RightShiftExpr,


				VC_BVVAR32DIVBYPOWEROFTWOEXPR myvc_bvVar32DivByPowOfTwoExpr,

				VC_BVEXTRACT		      myvc_bvExtract,
				VC_BVBOOLEXTRACT	      myvc_bvBoolExtract,

				VC_BVSIGNEXTEND		      myvc_bvSignExtend,


				VC_BV_CREATEMEMORYARRAY	      myvc_bvCreateMemoryArray,

				VC_BVREADMEMORYARRAY	      myvc_bvReadMemoryArray,

				VC_BVWRITETOMEMORYARRAY	      myvc_bvWriteToMemoryArray,

				// VC_BV32CONSTEXPRFROMINT	      myvc_bv32ConstExprFromInt,


				EXPRSTRING		      myexprString,
				TYPESTRING		      mytypeString,


				GETCHILD		      mygetChild,

				VC_ISBOOL		      myvc_isBool,
				VC_REGISTERERRORHANDLER	      myvc_registerErrorHandler,

				VC_GETHASHQUERYSTATETOBUFFER  myvc_getHashQueryStateToBuffer,

				VC_DESTROY		      myvc_Destroy
 
				 );



extern VC_CREATEVALIDITYCHECKER   vc_createValidityChecker;
extern VC_SETFLAGS		   vc_setFlags;

extern VC_BOOLTYPE		   vc_boolType;
extern VC_ARRAYTYPE  		   vc_arrayType;

extern VC_VAREXPR		   vc_varExpr;
extern VC_VAREXPR1		   vc_varExpr1;


extern VC_GETBVLENGTH		   vc_getBVLength;
extern VC_GETTYPE		   vc_getType;

extern VC_EQEXPR		   vc_eqExpr;
extern VC_TRUEEXPR		   vc_trueExpr;
extern VC_FALSEEXPR		   vc_falseExpr;

extern VC_NOTEXPR		   vc_notExpr;
extern VC_ANDEXPR		   vc_andExpr;
extern VC_ANDEXPRN		   vc_andExprN;
extern VC_OREXPR		   vc_orExpr;
extern VC_OREXPRN		   vc_orExprN;
extern VC_IMPLIESEXPR		   vc_impliesExpr;
extern VC_IFFEXPR		   vc_iffExpr;
extern VC_ITEEXPR		   vc_iteExpr;

extern VC_BOOLTOBVEXPR		   vc_boolToBVExpr;

extern VC_READEXPR		   vc_readExpr;
extern VC_WRITEEXPR		   vc_writeExpr;

extern VC_PRINTEXPR 		   vc_printExpr;
extern VC_PRINTEXPRFILE	   vc_printExprFile;
extern VC_PRINTSTATETOBUFFER      vc_printStateToBuffer;
extern VC_PRINTEXPRTOBUFFER	   vc_printExprToBuffer;

extern VC_PRINTCOUNTEREXAMPLE     vc_printCounterExample;
extern VC_PRINTVARDECLS	   vc_printVarDecls;
extern VC_PRINTASSERTS		   vc_printAsserts;

extern VC_PRINTQUERYSTATETOBUFFER vc_printQueryStateToBuffer;
extern VC_PRINTQUERY		   vc_printQuery;
extern VC_ASSERTFORMULA	   vc_assertFormula;

extern VC_SIMPLIFY		   vc_simplify;
extern VC_QUERY		   vc_query;

extern VC_GETCOUNTEREXAMPLE	   vc_getCounterExample;
extern VC_COUNTEREXAMPLE_SIZE     vc_counterexample_size;

extern VC_PUSH			   vc_push;
extern VC_POP			   vc_pop;

extern GETBVINT		   getBVInt;
extern GETBVUNSIGNED		   getBVUnsigned;
extern GETBVUNSIGNEDLONGLONG	   getBVUnsignedLongLong;


extern VC_BVTYPE		   vc_bvType;
extern VC_BV32TYPE		   vc_bv32Type;

extern VC_BVCONSTEXPRFROMSTR	   vc_bvConstExprFromStr;
extern VC_BVCONSTEXPRFROMINT      vc_bvConstExprFromInt;
extern VC_BVCONSTEXPRFROMLL	   vc_bvConstExprFromLL;
extern VC_BV32CONSTEXPRFROMINT    vc_bv32ConstExprFromInt;

extern VC_BVCONCATEXPR		   vc_bvConcatExpr;

extern VC_BVPLUSEXPR		   vc_bvPlusExpr;
extern VC_BV32PLUSEXPR		   vc_bv32PlusExpr;

extern VC_BVMINUSEXPR		   vc_bvMinusExpr;
extern VC_BV32MINUSEXPR	   vc_bv32MinusExpr;

extern VC_BVMULTEXPR		   vc_bvMultExpr;
extern VC_BV32MULTEXPR		   vc_bv32MultExpr;

extern VC_BVDIVEXPR		   vc_bvDivExpr;
extern VC_BVMODEXPR		   vc_bvModExpr;
extern VC_SIGNBVDIVEXPR	   vc_sbvDivExpr;
extern VC_SIGNBVMODEXPR	   vc_sbvModExpr;

extern VC_BVLTEXPR		   vc_bvLtExpr;
extern VC_BVLEEXPR		   vc_bvLeExpr;

extern VC_BVGTEXPR		   vc_bvGtExpr;
extern VC_BVGEEXPR		   vc_bvGeExpr;


extern VC_SBVLTEXPR		   vc_sbvLtExpr;
extern VC_SBVLEEXPR		   vc_sbvLeExpr;

extern VC_SBVGTEXPR		   vc_sbvGtExpr;
extern VC_SBVGEEXPR		   vc_sbvGeExpr;

extern VC_BVUMINUSEXPR		   vc_bvUMinusExpr;

extern VC_BVANDEXPR		   vc_bvAndExpr;
extern VC_BVOREXPR		   vc_bvOrExpr;
extern VC_BVXOREXPR		   vc_bvXorExpr;
extern VC_BVNOTEXPR		   vc_bvNotExpr;

extern VC_BVLEFTSHIFTEXPR	   vc_bvLeftShiftExpr;
extern VC_BVRIGHTSHIFTEXPR	   vc_bvRightShiftExpr;

extern VC_BV32LEFTSHIFTEXPR	   vc_bv32LeftShiftExpr;
extern VC_BV32RIGHTSHIFTEXPR	   vc_bv32RightShiftExpr;

extern VC_BVVAR32LEFTSHIFTEXPR	   vc_bvVar32LeftShiftExpr;
extern VC_BVVAR32RIGHTSHIFTEXPR   vc_bvVar32RightShiftExpr;


extern VC_BVVAR32DIVBYPOWEROFTWOEXPR vc_bvVar32DivByPowOfTwoExpr;

extern VC_BVEXTRACT		      vc_bvExtract;
extern VC_BVBOOLEXTRACT	      vc_bvBoolExtract;

extern VC_BVSIGNEXTEND		      vc_bvSignExtend;


extern VC_BV_CREATEMEMORYARRAY	      vc_bvCreateMemoryArray;

extern VC_BVREADMEMORYARRAY	      vc_bvReadMemoryArray;

extern VC_BVWRITETOMEMORYARRAY	      vc_bvWriteToMemoryArray;

// VC_BV32CONSTEXPRFROMINT	      vc_bv32ConstExprFromInt;


extern EXPRSTRING		      exprString;
extern TYPESTRING		      typeString;


extern GETCHILD		      getChild;

extern VC_ISBOOL		      vc_isBool;
extern VC_REGISTERERRORHANDLER	      vc_registerErrorHandler;

extern VC_GETHASHQUERYSTATETOBUFFER  vc_getHashQueryStateToBuffer;

extern VC_DESTROY		      vc_Destroy;

#endif



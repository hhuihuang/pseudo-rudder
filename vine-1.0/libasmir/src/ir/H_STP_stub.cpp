#include "../include/H_STP_stub.h"
#include "../include/stp_variables.h"

extern void (*H_term_printf)( const char * fstr, ... );

VC_CREATEVALIDITYCHECKER   vc_createValidityChecker;
VC_SETFLAGS		   vc_setFlags;

VC_BOOLTYPE		   vc_boolType;
VC_ARRAYTYPE  		   vc_arrayType;

VC_VAREXPR		   vc_varExpr;
VC_VAREXPR1		   vc_varExpr1;


VC_GETTYPE		   vc_getType;
VC_GETBVLENGTH		   vc_getBVLength;

VC_EQEXPR		   vc_eqExpr;
VC_TRUEEXPR		   vc_trueExpr;
VC_FALSEEXPR		   vc_falseExpr;

VC_NOTEXPR		   vc_notExpr;
VC_ANDEXPR		   vc_andExpr;
VC_ANDEXPRN		   vc_andExprN;
VC_OREXPR		   vc_orExpr;
VC_OREXPRN		   vc_orExprN;
VC_IMPLIESEXPR		   vc_impliesExpr;
VC_IFFEXPR		   vc_iffExpr;
VC_ITEEXPR		   vc_iteExpr;

VC_BOOLTOBVEXPR		   vc_boolToBVExpr;

VC_READEXPR		   vc_readExpr;
VC_WRITEEXPR		   vc_writeExpr;

VC_PRINTEXPR 		   vc_printExpr;
VC_PRINTEXPRFILE	   vc_printExprFile;
VC_PRINTSTATETOBUFFER      vc_printStateToBuffer;
VC_PRINTEXPRTOBUFFER	   vc_printExprToBuffer;

VC_PRINTCOUNTEREXAMPLE     vc_printCounterExample;
VC_PRINTVARDECLS	   vc_printVarDecls;
VC_PRINTASSERTS		   vc_printAsserts;

VC_PRINTQUERYSTATETOBUFFER vc_printQueryStateToBuffer;
VC_PRINTQUERY		   vc_printQuery;
VC_ASSERTFORMULA	   vc_assertFormula;

VC_SIMPLIFY		   vc_simplify;
VC_QUERY		   vc_query;

VC_GETCOUNTEREXAMPLE	   vc_getCounterExample;
VC_COUNTEREXAMPLE_SIZE     vc_counterexample_size;

VC_PUSH			   vc_push;
VC_POP			   vc_pop;

GETBVINT		   getBVInt;
GETBVUNSIGNED		   getBVUnsigned;
GETBVUNSIGNEDLONGLONG	   getBVUnsignedLongLong;


VC_BVTYPE		   vc_bvType;
VC_BV32TYPE		   vc_bv32Type;

VC_BVCONSTEXPRFROMSTR	   vc_bvConstExprFromStr;
VC_BVCONSTEXPRFROMINT      vc_bvConstExprFromInt;
VC_BVCONSTEXPRFROMLL	   vc_bvConstExprFromLL;
VC_BV32CONSTEXPRFROMINT    vc_bv32ConstExprFromInt;

VC_BVCONCATEXPR		   vc_bvConcatExpr;

VC_BVPLUSEXPR		   vc_bvPlusExpr;
VC_BV32PLUSEXPR		   vc_bv32PlusExpr;

VC_BVMINUSEXPR		   vc_bvMinusExpr;
VC_BV32MINUSEXPR	   vc_bv32MinusExpr;

VC_BVMULTEXPR		   vc_bvMultExpr;
VC_BV32MULTEXPR		   vc_bv32MultExpr;

VC_BVDIVEXPR		   vc_bvDivExpr;
VC_BVMODEXPR		   vc_bvModExpr;
VC_SIGNBVDIVEXPR	   vc_sbvDivExpr;
VC_SIGNBVMODEXPR	   vc_sbvModExpr;

VC_BVLTEXPR		   vc_bvLtExpr;
VC_BVLEEXPR		   vc_bvLeExpr;

VC_BVGTEXPR		   vc_bvGtExpr;
VC_BVGEEXPR		   vc_bvGeExpr;


VC_SBVLTEXPR		   vc_sbvLtExpr;
VC_SBVLEEXPR		   vc_sbvLeExpr;

VC_SBVGTEXPR		   vc_sbvGtExpr;
VC_SBVGEEXPR		   vc_sbvGeExpr;

VC_BVUMINUSEXPR		   vc_bvUMinusExpr;

VC_BVANDEXPR		   vc_bvAndExpr;
VC_BVOREXPR		   vc_bvOrExpr;
VC_BVXOREXPR		   vc_bvXorExpr;
VC_BVNOTEXPR		   vc_bvNotExpr;

VC_BVLEFTSHIFTEXPR	   vc_bvLeftShiftExpr;
VC_BVRIGHTSHIFTEXPR	   vc_bvRightShiftExpr;

VC_BV32LEFTSHIFTEXPR	   vc_bv32LeftShiftExpr;
VC_BV32RIGHTSHIFTEXPR	   vc_bv32RightShiftExpr;

VC_BVVAR32LEFTSHIFTEXPR	   vc_bvVar32LeftShiftExpr;
VC_BVVAR32RIGHTSHIFTEXPR   vc_bvVar32RightShiftExpr;


VC_BVVAR32DIVBYPOWEROFTWOEXPR vc_bvVar32DivByPowOfTwoExpr;

VC_BVEXTRACT		      vc_bvExtract;
VC_BVBOOLEXTRACT	      vc_bvBoolExtract;

VC_BVSIGNEXTEND		      vc_bvSignExtend;


VC_BV_CREATEMEMORYARRAY	      vc_bvCreateMemoryArray;

VC_BVREADMEMORYARRAY	      vc_bvReadMemoryArray;

VC_BVWRITETOMEMORYARRAY	      vc_bvWriteToMemoryArray;

// VC_BV32CONSTEXPRFROMINT	      vc_bv32ConstExprFromInt;


EXPRSTRING		      exprString;
TYPESTRING		      typeString;


GETCHILD		      getChild;

VC_ISBOOL		      vc_isBool;
VC_REGISTERERRORHANDLER	      vc_registerErrorHandler;

VC_GETHASHQUERYSTATETOBUFFER  vc_getHashQueryStateToBuffer;

VC_DESTROY		      vc_Destroy;
VC_DELETEEXPR		      vc_DeleteExpr;

VC_GET_WHOLECOUNTEREXAMPLE    vc_getWholeCounterExample;
VC_GET_TERMFROMCOUNTEREXAMPLE vc_getTermFromCounterExample;


void Obtain_stp_utils_From_plugin( VC_CREATEVALIDITYCHECKER   myvc_createValidityChecker,
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

				VC_DESTROY		      myvc_Destroy,
				VC_DELETEEXPR		      myvc_DeleteExpr,


				VC_GET_WHOLECOUNTEREXAMPLE    myvc_getWholeCounterExample,
				VC_GET_TERMFROMCOUNTEREXAMPLE myvc_getTermFromCounterExample,

				OBTAIN_STP_VARS_ARRAY         myobtain_stp_vars_array
 
				 )
{

vc_createValidityChecker = myvc_createValidityChecker;

vc_setFlags = myvc_setFlags;

vc_boolType = myvc_boolType;

vc_arrayType = myvc_arrayType;

vc_varExpr  = myvc_varExpr;

vc_varExpr1 = myvc_varExpr1;

vc_getType = myvc_getType;

vc_getBVLength = myvc_getBVLength;


vc_eqExpr = myvc_eqExpr;

vc_trueExpr = myvc_trueExpr;

vc_falseExpr = myvc_falseExpr;

vc_notExpr = myvc_notExpr;

vc_andExpr = myvc_andExpr;

vc_andExprN = myvc_andExprN;

vc_orExpr = myvc_orExpr;

vc_orExprN = myvc_orExprN;

vc_impliesExpr = myvc_impliesExpr;

vc_iffExpr = myvc_iffExpr;

vc_iteExpr = myvc_iteExpr;


vc_boolToBVExpr = myvc_boolToBVExpr;

vc_readExpr = myvc_readExpr;

vc_writeExpr = myvc_writeExpr;

vc_printExpr = myvc_printExpr;

vc_printExprFile = myvc_printExprFile;

vc_printStateToBuffer = myvc_printStateToBuffer;

vc_printExprToBuffer = myvc_printExprToBuffer;

vc_printCounterExample = myvc_printCounterExample;

vc_printVarDecls = myvc_printVarDecls;

vc_printAsserts = myvc_printAsserts;

vc_printQueryStateToBuffer = myvc_printQueryStateToBuffer;

vc_printQuery = myvc_printQuery;

vc_assertFormula = myvc_assertFormula;

vc_simplify = myvc_simplify;

vc_query = myvc_query;

vc_getCounterExample = myvc_getCounterExample;

vc_counterexample_size = myvc_counterexample_size;

vc_push = myvc_push;

vc_pop = myvc_pop;


getBVInt = mygetBVInt;

getBVUnsigned = mygetBVUnsigned;

getBVUnsignedLongLong = mygetBVUnsignedLongLong;


vc_bvType = myvc_bvType;

vc_bv32Type = myvc_bv32Type;

vc_bvConstExprFromStr = myvc_bvConstExprFromStr;

vc_bvConstExprFromInt = myvc_bvConstExprFromInt;

vc_bvConstExprFromLL = myvc_bvConstExprFromLL;

vc_bv32ConstExprFromInt = myvc_bv32ConstExprFromInt;


vc_bvConcatExpr = myvc_bvConcatExpr;

vc_bvPlusExpr = myvc_bvPlusExpr;

vc_bv32PlusExpr = myvc_bv32PlusExpr;


vc_bvMinusExpr = myvc_bvMinusExpr;

vc_bv32MinusExpr = myvc_bv32MinusExpr;

vc_bvMultExpr = myvc_bvMultExpr;

vc_bv32MultExpr = myvc_bv32MultExpr;

vc_bvDivExpr = myvc_bvDivExpr;

vc_bvModExpr = myvc_bvModExpr;


vc_sbvDivExpr = myvc_sbvDivExpr;


vc_sbvModExpr = myvc_sbvModExpr;


vc_bvLtExpr = myvc_bvLtExpr;

vc_bvLeExpr = myvc_bvLeExpr;

vc_bvGtExpr = myvc_bvGtExpr;

vc_bvGeExpr = myvc_bvGeExpr;


vc_sbvLtExpr = myvc_sbvLtExpr;

vc_sbvLeExpr = myvc_sbvLeExpr;

vc_sbvGtExpr = myvc_sbvGtExpr;

vc_sbvGeExpr = myvc_sbvGeExpr;

vc_bvUMinusExpr = myvc_bvUMinusExpr;

vc_bvAndExpr = myvc_bvAndExpr;

vc_bvOrExpr = myvc_bvOrExpr;

vc_bvXorExpr = myvc_bvXorExpr;

vc_bvNotExpr = myvc_bvNotExpr;

vc_bvLeftShiftExpr = myvc_bvLeftShiftExpr;

vc_bvRightShiftExpr = myvc_bvRightShiftExpr;

vc_bv32LeftShiftExpr = myvc_bv32LeftShiftExpr;

vc_bv32RightShiftExpr = myvc_bv32RightShiftExpr;

vc_bvVar32LeftShiftExpr = myvc_bvVar32LeftShiftExpr;

vc_bvVar32RightShiftExpr = myvc_bvVar32RightShiftExpr;

vc_bvVar32DivByPowOfTwoExpr = myvc_bvVar32DivByPowOfTwoExpr;

vc_bvExtract = myvc_bvExtract;

vc_bvBoolExtract = myvc_bvBoolExtract;

vc_bvSignExtend = myvc_bvSignExtend;

vc_bvCreateMemoryArray = myvc_bvCreateMemoryArray;

vc_bvReadMemoryArray = myvc_bvReadMemoryArray;

vc_bvWriteToMemoryArray = myvc_bvWriteToMemoryArray;

// vc_bv32ConstExprFromInt = myvc_bv32ConstExprFromInt;

exprString = myexprString;

typeString = mytypeString;

getChild = mygetChild;

vc_isBool = myvc_isBool;

vc_registerErrorHandler = myvc_registerErrorHandler;

vc_getHashQueryStateToBuffer = myvc_getHashQueryStateToBuffer;

vc_Destroy = myvc_Destroy;

vc_DeleteExpr = myvc_DeleteExpr;


vc_getWholeCounterExample    = myvc_getWholeCounterExample;
vc_getTermFromCounterExample = myvc_getTermFromCounterExample;


obtain_stp_vars_array = myobtain_stp_vars_array;

}// end of Obtain_stp_utils_From_plugin





















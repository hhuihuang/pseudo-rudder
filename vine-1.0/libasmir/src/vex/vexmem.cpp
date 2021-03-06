/*
Vine is Copyright (C) 2006-2009, BitBlaze Team.

You can redistribute and modify it under the terms of the GNU GPL,
version 2 or later, but it is made available WITHOUT ANY WARRANTY.
See the top-level README file for more details.

For more information about Vine and other BitBlaze software, see our
web site at: http://bitblaze.cs.berkeley.edu/
*/

//======================================================================
//
// This file contains the functions for memory management needed by 
// the binary to VEX IR translation interface. A large part of this
// file was copied from irdefs.c in VEX.
//
//======================================================================

#include "libvex_basictypes.h"
#include "libvex_ir.h"
#include "libvex.h"

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <malloc.h>

#include <unistd.h>
#include <fcntl.h>
#include <string.h>

#include "vexmem.h"

//
// Function for panicking
//
void vx_panic ( HChar* str )
{
    printf("\nvex: the `impossible' happened:\n   %s\n", str);
    exit(-1);
}

//======================================================================
//
// Mem management functions
//
//======================================================================


// original
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
//
// Currently 256 MB
//
// #define HUGE_BLOCK_SIZE (1 << 28)
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */

// HHui modified at Jan 8th, 2012 
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */
//
// Currently 256 MB
//
#define HUGE_BLOCK_SIZE (1 << 30)
/* xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx */



//
// Note:
//
// Because the memory allocated (via LibVEX_Alloc) in lib VEX is only
// live during translation and not usable afterwards, we have to write
// our own deep copy constructor to allocate memory from elsewhere and
// copy the translated IRSB from VEX memory to our memory before we can
// use it. 
//
// To avoid having to write matching destructors for every constructor
// (and there are a lot of them), we use a huge block of static memory
// for all allocations, and then free the entire block all at once when
// we're done with the IRSB. (Arena allocation style)
//
// TODO: Allocate this from the heap so that we can grow it at run time
//       if needed.


/* +++++++++++++++++++++++++++ HHui temply modified for dynamic allocation at Jan 14th, 2012 +++++++++++++++++++++++++++ */
/* ------------------------------------------------------------------------ */
// temply deleted, which are the originals.
/*
unsigned char huge_block[ (unsigned int)HUGE_BLOCK_SIZE ];
unsigned char *next_free = huge_block;
*/

/* HHui-Fixme[TODO:] I suppose here that, for a single ASM-instruction,
   the size of the VEX-irs generated for it won't be larger than a single 
   page's size ...--------- (possibly this could be even smaller !)
 */
unsigned char huge_block[1024 * 4];
unsigned char *next_free = huge_block;

/* ------------------------------------------------------------------------ */

/*
unsigned char ** huge_block     = NULL;
unsigned int     occupied_count = 0;
unsigned int     total_count    = 0;
#ifndef H_BLOCK_INCRE_COUNT
    #define H_BLOCK_INCRE_COUNT 1024
#endif
*/

static int h_vx_fd = -1;

static uint32_t h_vx_a2i(char * str)
{
    uint32_t data = 0;
    for(int i = 0; str[i] != '\0'; i = i + 1)
    {
  	if(str[i] > 0x39)
	{
	    if(str[i] >= 0x61)
	    {
	 	data = data * 16 + str[i] - 0x61 + 10;
	    }
	    else
	    {
		data = data * 16 + str[i] - 0x41 + 10;
	    }// end of if(str[i])
	}
	else
	{
	    data = data * 16 + str[i] - 0x30;
        }// end of if(str[i])
    }// end of for{i}

    // term_printf("%s --- %d ; ",str, data);
    return data;
}// end of h_a2i( )


/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

void *vx_Alloc( Int nbytes )
{

/* +++++++++++++++++++++++++++ HHui temply modified for dynamic allocation at Jan 14th, 2012 +++++++++++++++++++++++++++ */
    
    // temply deleted, which are the originals.
    /* ------------------------------------------------------------------------ */    
    assert(nbytes > 0);

    void *this_block = next_free;

    next_free += nbytes; 

    assert( next_free < huge_block + HUGE_BLOCK_SIZE );

    return this_block;    
    /* ------------------------------------------------------------------------ */

    /*
    assert(nbytes > 0);
    if(huge_block == NULL)
    {
	huge_block  = (unsigned char **)malloc( H_BLOCK_INCRE_COUNT * sizeof(unsigned char *) );	
	total_count = H_BLOCK_INCRE_COUNT;

        assert(huge_block != NULL);
    }// end of if(huge_block)    
	
    if(total_count == occupied_count)
    {
	huge_block  = (unsigned char **)realloc( huge_block,
						 (H_BLOCK_INCRE_COUNT + total_count) * sizeof(unsigned char *) 
					       );
	total_count = H_BLOCK_INCRE_COUNT + total_count;
	assert(huge_block != NULL);
    }// end of if(nbytes)    

    huge_block[occupied_count] = (unsigned char *)malloc(sizeof(unsigned char) * nbytes);
    assert(huge_block[occupied_count] != NULL);

    occupied_count = occupied_count + 1;
    return huge_block[occupied_count - 1];
    */
    /*
    assert(nbytes > 0);
    unsigned char * tmp_ptr = (unsigned char *)malloc(sizeof(unsigned char) * nbytes);
    char buffer[10];
    int  count = 0;

    assert(tmp_ptr != NULL);

    if(h_vx_fd < 0)
    {
	umask(0);
        h_vx_fd = open( "./vx_Alloc_IR_tmp",
		        (O_CREAT | O_RDWR),
		        (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH)
		      );	
    }// end of if(h_vx_fd)

    count = sprintf( buffer,
		     "%8x-",
		     (uint32_t)tmp_ptr
		   );
    buffer[count] = '\0';

    write( h_vx_fd,
	   buffer,
	   count
	 );
    return tmp_ptr;    
    */
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */
    
}

void vx_FreeAll()
{
/* +++++++++++++++++++++++++++ HHui temply modified for dynamic allocation at Jan 14th, 2012 +++++++++++++++++++++++++++ */
    
    // temply deleted, which are the originals.
    /* ------------------------------------------------------------------------ */
    
    next_free = huge_block;    
    
    /* ------------------------------------------------------------------------ */
    
    /*
    int i = 0;
    for(i = 0; i < occupied_count; i = i + 1)
    {
	free(huge_block[i]);
    }// end of for{i}
 
    if(huge_block != NULL)
    {
        free(huge_block);
    }// end of if(huge_block)
    
    huge_block = NULL;
    */

    /*
    char     buffer[9];
    int	     count = 0;
    uint32_t value = 0;

    if(h_vx_fd > 0)
    {
	close(h_vx_fd);
        h_vx_fd = open( "./vx_Alloc_IR_tmp",
		        O_RDWR
		      );	
	do
	{
	    count = read( h_vx_fd,
		          buffer,
		          9
		        );	
	    if(count <= 0)
	    {
		break;
	    }// end of if(count)

	    buffer[8] = '\0';
	    value = h_vx_a2i(buffer);
	    if(value != 0)
	    {
	        free((void *)value);
	    }// end of if(value)
	}while(1);
	
	close(h_vx_fd);
    }// end of if(h_vx_fd)

    h_vx_fd = -1;
    */
/* +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ */

}


//======================================================================
//
// Constructors
//
//======================================================================

/* Constructors -- IRConst */

IRConst* vx_IRConst_U1 ( Bool bit )
{
   IRConst* c = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag     = Ico_U1;
   c->Ico.U1  = bit;
   /* call me paranoid; I don't care :-) */
   assert(bit == False || bit == True);
   return c;
}
IRConst* vx_IRConst_U8 ( UChar u8 )
{
   IRConst* c = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag     = Ico_U8;
   c->Ico.U8  = u8;
   return c;
}
IRConst* vx_IRConst_U16 ( UShort u16 )
{
   IRConst* c = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag     = Ico_U16;
   c->Ico.U16 = u16;
   return c;
}
IRConst* vx_IRConst_U32 ( UInt u32 )
{
   IRConst* c = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag     = Ico_U32;
   c->Ico.U32 = u32;
   return c;
}
IRConst* vx_IRConst_U64 ( ULong u64 )
{
   IRConst* c = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag     = Ico_U64;
   c->Ico.U64 = u64;
   return c;
}
IRConst* vx_IRConst_F64 ( Double f64 )
{
   IRConst* c = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag     = Ico_F64;
   c->Ico.F64 = f64;
   return c;
}
IRConst* vx_IRConst_F64i ( ULong f64i )
{
   IRConst* c  = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag      = Ico_F64i;
   c->Ico.F64i = f64i;
   return c;
}
IRConst* vx_IRConst_V128 ( UShort con )
{
   IRConst* c  = (IRConst *)vx_Alloc(sizeof(IRConst));
   c->tag      = Ico_V128;
   c->Ico.V128 = con;
   return c;
}

/* Constructors -- IRCallee */

IRCallee* vx_mkIRCallee ( Int regparms, HChar* name, void* addr )
{
   IRCallee* ce = (IRCallee *)vx_Alloc(sizeof(IRCallee));
   ce->regparms = regparms;
   ce->name     = name;
   ce->addr     = addr;
   ce->mcx_mask = 0;
   assert(regparms >= 0 && regparms <= 3);
   assert(name != NULL);
   assert(addr != 0);
   return ce;
}


/* Constructors -- IRRegArray */

IRRegArray* vx_mkIRRegArray ( Int base, IRType elemTy, Int nElems )
{
   IRRegArray* arr = (IRRegArray *)vx_Alloc(sizeof(IRRegArray));
   arr->base    = base;
   arr->elemTy  = elemTy;
   arr->nElems  = nElems;
   assert(!(arr->base < 0 || arr->base > 10000 /* somewhat arbitrary */));
   assert(!(arr->elemTy == Ity_I1));
   assert(!(arr->nElems <= 0 || arr->nElems > 500 /* somewhat arbitrary */));
   return arr;
}


/* Constructors -- IRExpr */

IRExpr* vx_IRExpr_Binder ( Int binder ) {
   IRExpr* e            = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag               = Iex_Binder;
   e->Iex.Binder.binder = binder;
   return e;
}
IRExpr* vx_IRExpr_Get ( Int off, IRType ty ) {
   IRExpr* e         = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag            = Iex_Get;
   e->Iex.Get.offset = off;
   e->Iex.Get.ty     = ty;
   return e;
}
IRExpr* vx_IRExpr_GetI ( IRRegArray* descr, IRExpr* ix, Int bias ) {
   IRExpr* e         = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag            = Iex_GetI;
   e->Iex.GetI.descr = descr;
   e->Iex.GetI.ix    = ix;
   e->Iex.GetI.bias  = bias;
   return e;
}
IRExpr* vx_IRExpr_Tmp ( IRTemp tmp ) {
   IRExpr* e      = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag         = Iex_RdTmp;
   e->Iex.RdTmp.tmp = tmp;
   return e;
}
IRExpr* vx_IRExpr_Qop ( IROp op, IRExpr* arg1, IRExpr* arg2, 
                              IRExpr* arg3, IRExpr* arg4 ) {
   IRExpr* e       = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag          = Iex_Qop;
   e->Iex.Qop.op   = op;
   e->Iex.Qop.arg1 = arg1;
   e->Iex.Qop.arg2 = arg2;
   e->Iex.Qop.arg3 = arg3;
   e->Iex.Qop.arg4 = arg4;
   return e;
}
IRExpr* vx_IRExpr_Triop  ( IROp op, IRExpr* arg1, 
                                 IRExpr* arg2, IRExpr* arg3 ) {
   IRExpr* e         = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag            = Iex_Triop;
   e->Iex.Triop.op   = op;
   e->Iex.Triop.arg1 = arg1;
   e->Iex.Triop.arg2 = arg2;
   e->Iex.Triop.arg3 = arg3;
   return e;
}
IRExpr* vx_IRExpr_Binop ( IROp op, IRExpr* arg1, IRExpr* arg2 ) {
   IRExpr* e         = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag            = Iex_Binop;
   e->Iex.Binop.op   = op;
   e->Iex.Binop.arg1 = arg1;
   e->Iex.Binop.arg2 = arg2;
   return e;
}
IRExpr* vx_IRExpr_Unop ( IROp op, IRExpr* arg ) {
   IRExpr* e       = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag          = Iex_Unop;
   e->Iex.Unop.op  = op;
   e->Iex.Unop.arg = arg;
   return e;
}
IRExpr* vx_IRExpr_Load ( IREndness end, IRType ty, IRExpr* addr ) {
   IRExpr* e        = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag           = Iex_Load;
   e->Iex.Load.end  = end;
   e->Iex.Load.ty   = ty;
   e->Iex.Load.addr = addr;
   assert(end == Iend_LE || end == Iend_BE);
   return e;
}
IRExpr* vx_IRExpr_Const ( IRConst* con ) {
   IRExpr* e        = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag           = Iex_Const;
   e->Iex.Const.con = con;
   return e;
}
IRExpr* vx_IRExpr_CCall ( IRCallee* cee, IRType retty, IRExpr** args ) {
   IRExpr* e          = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag             = Iex_CCall;
   e->Iex.CCall.cee   = cee;
   e->Iex.CCall.retty = retty;
   e->Iex.CCall.args  = args;
   return e;
}
IRExpr* vx_IRExpr_Mux0X ( IRExpr* cond, IRExpr* expr0, IRExpr* exprX ) {
   IRExpr* e          = (IRExpr *)vx_Alloc(sizeof(IRExpr));
   e->tag             = Iex_Mux0X;
   e->Iex.Mux0X.cond  = cond;
   e->Iex.Mux0X.expr0 = expr0;
   e->Iex.Mux0X.exprX = exprX;
   return e;
}


/* Constructors -- IRDirty */

IRDirty* vx_emptyIRDirty ( void ) {
   IRDirty* d = (IRDirty *)vx_Alloc(sizeof(IRDirty));
   d->cee      = NULL;
   d->guard    = NULL;
   d->args     = NULL;
   d->tmp      = IRTemp_INVALID;
   d->mFx      = Ifx_None;
   d->mAddr    = NULL;
   d->mSize    = 0;
   d->needsBBP = False;
   d->nFxState = 0;
   return d;
}


/* Constructors -- IRStmt */

IRStmt* vx_IRStmt_NoOp ( void )
{
   /* Just use a single static closure. */
   static IRStmt static_closure;
   static_closure.tag = Ist_NoOp;
   return &static_closure;
}
IRStmt* vx_IRStmt_IMark ( Addr64 addr, Int len ) {
   IRStmt* s         = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag            = Ist_IMark;
   s->Ist.IMark.addr = addr;
   s->Ist.IMark.len  = len;
   return s;
}
IRStmt* vx_IRStmt_AbiHint ( IRExpr* base, Int len ) {
   IRStmt* s           = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag              = Ist_AbiHint;
   s->Ist.AbiHint.base = base;
   s->Ist.AbiHint.len  = len;
   return s;
}
IRStmt* vx_IRStmt_Put ( Int off, IRExpr* data ) {
   IRStmt* s         = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag            = Ist_Put;
   s->Ist.Put.offset = off;
   s->Ist.Put.data   = data;
   return s;
}
IRStmt* vx_IRStmt_PutI ( IRRegArray* descr, IRExpr* ix,
                      Int bias, IRExpr* data ) {
   IRStmt* s         = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag            = Ist_PutI;
   s->Ist.PutI.descr = descr;
   s->Ist.PutI.ix    = ix;
   s->Ist.PutI.bias  = bias;
   s->Ist.PutI.data  = data;
   return s;
}
IRStmt* vx_IRStmt_Tmp ( IRTemp tmp, IRExpr* data ) {
   IRStmt* s       = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag          = Ist_WrTmp;
   s->Ist.WrTmp.tmp  = tmp;
   s->Ist.WrTmp.data = data;
   return s;
}
IRStmt* vx_IRStmt_Store ( IREndness end, IRExpr* addr, IRExpr* data ) {
   IRStmt* s         = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag            = Ist_Store;
   s->Ist.Store.end  = end;
   s->Ist.Store.addr = addr;
   s->Ist.Store.data = data;
   assert(end == Iend_LE || end == Iend_BE);
   return s;
}
IRStmt* vx_IRStmt_Dirty ( IRDirty* d )
{
   IRStmt* s            = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag               = Ist_Dirty;
   s->Ist.Dirty.details = d;
   return s;
}
IRStmt* vx_IRStmt_MFence ( void )
{
   /* Just use a single static closure. */
   static IRStmt static_closure;
   static_closure.tag = Ist_MFence;
   return &static_closure;
}
IRStmt* vx_IRStmt_Exit ( IRExpr* guard, IRJumpKind jk, IRConst* dst ) {
   IRStmt* s         = (IRStmt *)vx_Alloc(sizeof(IRStmt));
   s->tag            = Ist_Exit;
   s->Ist.Exit.guard = guard;
   s->Ist.Exit.jk    = jk;
   s->Ist.Exit.dst   = dst;
   return s;
}


/* Constructors -- IRTypeEnv */

IRTypeEnv* vx_emptyIRTypeEnv ( void )
{
   IRTypeEnv* env   = (IRTypeEnv *)vx_Alloc(sizeof(IRTypeEnv));
   env->types       = (IRType *)vx_Alloc(8 * sizeof(IRType));
   env->types_size  = 8;
   env->types_used  = 0;
   return env;
}


/* Constructors -- IRSB */

IRSB* vx_emptyIRSB ( void )
{
   IRSB* bb       = (IRSB *)vx_Alloc(sizeof(IRSB));
   bb->tyenv      = vx_emptyIRTypeEnv();
   bb->stmts_used = 0;
   bb->stmts_size = 8;
   bb->stmts      = (IRStmt **)vx_Alloc(bb->stmts_size * sizeof(IRStmt*));
   bb->next       = NULL;
   bb->jumpkind   = Ijk_Boring;
   return bb;
}


/*---------------------------------------------------------------*/
/*--- (Deep) copy constructors.  These make complete copies   ---*/
/*--- the original, which can be modified without affecting   ---*/
/*--- the original.                                           ---*/
/*---------------------------------------------------------------*/

/* Copying IR Expr vectors (for call args). */

/* Shallow copy of an IRExpr vector */

IRExpr** vx_sopyIRExprVec ( IRExpr** vec )
{
   Int      i;
   IRExpr** newvec;
   for (i = 0; vec[i]; i++)
      ;
   newvec = (IRExpr **)vx_Alloc((i+1)*sizeof(IRExpr*));
   for (i = 0; vec[i]; i++)
      newvec[i] = vec[i];
   newvec[i] = NULL;
   return newvec;
}

/* Deep copy of an IRExpr vector */

IRExpr** vx_dopyIRExprVec ( IRExpr** vec )
{
   Int      i;
   IRExpr** newvec = vx_sopyIRExprVec( vec );
   for (i = 0; newvec[i]; i++)
      newvec[i] = vx_dopyIRExpr(newvec[i]);
   return newvec;
}

/* Deep copy constructors for all heap-allocated IR types follow. */

IRConst* vx_dopyIRConst ( IRConst* c )
{
   switch (c->tag) {
      case Ico_U1:   return vx_IRConst_U1(c->Ico.U1);
      case Ico_U8:   return vx_IRConst_U8(c->Ico.U8);
      case Ico_U16:  return vx_IRConst_U16(c->Ico.U16);
      case Ico_U32:  return vx_IRConst_U32(c->Ico.U32);
      case Ico_U64:  return vx_IRConst_U64(c->Ico.U64);
      case Ico_F64:  return vx_IRConst_F64(c->Ico.F64);
      case Ico_F64i: return vx_IRConst_F64i(c->Ico.F64i);
      case Ico_V128: return vx_IRConst_V128(c->Ico.V128);
      default: vx_panic("vx_dopyIRConst");
   }

   return NULL;
}

IRCallee* vx_dopyIRCallee ( IRCallee* ce )
{
   IRCallee* ce2 = vx_mkIRCallee(ce->regparms, ce->name, ce->addr);
   ce2->mcx_mask = ce->mcx_mask;
   return ce2;
}

IRRegArray* vx_dopyIRRegArray ( IRRegArray* d )
{
   return vx_mkIRRegArray(d->base, d->elemTy, d->nElems);
}

IRExpr* vx_dopyIRExpr ( IRExpr* e )
{
   switch (e->tag) {
      case Iex_Get: 
         return vx_IRExpr_Get(e->Iex.Get.offset, e->Iex.Get.ty);
      case Iex_GetI: 
         return vx_IRExpr_GetI(vx_dopyIRRegArray(e->Iex.GetI.descr), 
                            vx_dopyIRExpr(e->Iex.GetI.ix),
                            e->Iex.GetI.bias);
      case Iex_RdTmp: 
        return vx_IRExpr_Tmp(e->Iex.RdTmp.tmp);
      case Iex_Qop: 
         return vx_IRExpr_Qop(e->Iex.Qop.op,
                           vx_dopyIRExpr(e->Iex.Qop.arg1),
                           vx_dopyIRExpr(e->Iex.Qop.arg2),
                           vx_dopyIRExpr(e->Iex.Qop.arg3),
                           vx_dopyIRExpr(e->Iex.Qop.arg4));
      case Iex_Triop: 
         return vx_IRExpr_Triop(e->Iex.Triop.op,
                             vx_dopyIRExpr(e->Iex.Triop.arg1),
                             vx_dopyIRExpr(e->Iex.Triop.arg2),
                             vx_dopyIRExpr(e->Iex.Triop.arg3));
      case Iex_Binop: 
         return vx_IRExpr_Binop(e->Iex.Binop.op,
                             vx_dopyIRExpr(e->Iex.Binop.arg1),
                             vx_dopyIRExpr(e->Iex.Binop.arg2));
      case Iex_Unop: 
         return vx_IRExpr_Unop(e->Iex.Unop.op,
                            vx_dopyIRExpr(e->Iex.Unop.arg));
      case Iex_Load: 
         return vx_IRExpr_Load(e->Iex.Load.end,
                            e->Iex.Load.ty,
                            vx_dopyIRExpr(e->Iex.Load.addr));
      case Iex_Const: 
         return vx_IRExpr_Const(vx_dopyIRConst(e->Iex.Const.con));
      case Iex_CCall:
         return vx_IRExpr_CCall(vx_dopyIRCallee(e->Iex.CCall.cee),
                             e->Iex.CCall.retty,
                             vx_dopyIRExprVec(e->Iex.CCall.args));

      case Iex_Mux0X: 
         return vx_IRExpr_Mux0X(vx_dopyIRExpr(e->Iex.Mux0X.cond),
                             vx_dopyIRExpr(e->Iex.Mux0X.expr0),
                             vx_dopyIRExpr(e->Iex.Mux0X.exprX));
      default:
         vx_panic("vx_dopyIRExpr");
   }

   return NULL;
}

IRDirty* vx_dopyIRDirty ( IRDirty* d )
{
   Int      i;
   IRDirty* d2 = vx_emptyIRDirty();
   d2->cee   = vx_dopyIRCallee(d->cee);
   d2->guard = vx_dopyIRExpr(d->guard);
   d2->args  = vx_dopyIRExprVec(d->args);
   d2->tmp   = d->tmp;
   d2->mFx   = d->mFx;
   d2->mAddr = d->mAddr==NULL ? NULL : vx_dopyIRExpr(d->mAddr);
   d2->mSize = d->mSize;
   d2->needsBBP = d->needsBBP;
   d2->nFxState = d->nFxState;
   for (i = 0; i < d2->nFxState; i++)
      d2->fxState[i] = d->fxState[i];
   return d2;
}

IRStmt* vx_dopyIRStmt ( IRStmt* s )
{
   switch (s->tag) {
      case Ist_NoOp:
         return vx_IRStmt_NoOp();
      case Ist_AbiHint:
         return vx_IRStmt_AbiHint(vx_dopyIRExpr(s->Ist.AbiHint.base),
                               s->Ist.AbiHint.len);
      case Ist_IMark:
         return vx_IRStmt_IMark(s->Ist.IMark.addr, s->Ist.IMark.len);
      case Ist_Put: 
         return vx_IRStmt_Put(s->Ist.Put.offset, 
                           vx_dopyIRExpr(s->Ist.Put.data));
      case Ist_PutI: 
         return vx_IRStmt_PutI(vx_dopyIRRegArray(s->Ist.PutI.descr),
                            vx_dopyIRExpr(s->Ist.PutI.ix),
                            s->Ist.PutI.bias, 
                            vx_dopyIRExpr(s->Ist.PutI.data));
      case Ist_WrTmp:
         return vx_IRStmt_Tmp(s->Ist.WrTmp.tmp,
                           vx_dopyIRExpr(s->Ist.WrTmp.data));
      case Ist_Store: 
         return vx_IRStmt_Store(s->Ist.Store.end,
                             vx_dopyIRExpr(s->Ist.Store.addr),
                             vx_dopyIRExpr(s->Ist.Store.data));
      case Ist_Dirty: 
         return vx_IRStmt_Dirty(vx_dopyIRDirty(s->Ist.Dirty.details));
      case Ist_MFence:
         return vx_IRStmt_MFence();
      case Ist_Exit: 
         return vx_IRStmt_Exit(vx_dopyIRExpr(s->Ist.Exit.guard),
                            s->Ist.Exit.jk,
                            vx_dopyIRConst(s->Ist.Exit.dst));
      default: 
         vx_panic("vx_dopyIRStmt");
   }

   return NULL;
}

IRTypeEnv* vx_dopyIRTypeEnv ( IRTypeEnv* src )
{
   Int        i;
   IRTypeEnv* dst = (IRTypeEnv *)vx_Alloc(sizeof(IRTypeEnv));
   dst->types_size = src->types_size;
   dst->types_used = src->types_used;
   dst->types = (IRType *)vx_Alloc(dst->types_size * sizeof(IRType));
   for (i = 0; i < src->types_used; i++)
      dst->types[i] = src->types[i];
   return dst;
}

IRSB* vx_dopyIRSB ( IRSB* bb )
{
   Int      i;
   IRStmt** sts2;
   IRSB* bb2 = vx_emptyIRSB();
   bb2->tyenv = vx_dopyIRTypeEnv(bb->tyenv);
   bb2->stmts_used = bb2->stmts_size = bb->stmts_used;
   sts2 = (IRStmt **)vx_Alloc(bb2->stmts_used * sizeof(IRStmt*));
   for (i = 0; i < bb2->stmts_used; i++)
      sts2[i] = vx_dopyIRStmt(bb->stmts[i]);
   bb2->stmts    = sts2;
   bb2->next     = vx_dopyIRExpr(bb->next);
   bb2->jumpkind = bb->jumpkind;
   return bb2;
}



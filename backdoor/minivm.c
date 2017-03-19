//-----------------------------------------------------------------------------
// minivm.c -- The basic definitions for the vm.
// Copyright (C) Philip Conrad 4/30/2013 @ 3:56 PM -- MIT License
//
//-----------------------------------------------------------------------------

#include "minivm.h"


//---------------------------------------------------------
// FUNCTION IMPLEMENTATIONS:


// Defers decoding of register args to the called function.
// dispatch :: VMContext -> uint32_t -> Effect()
void dispatch(struct VMContext* ctx, const uint32_t instr) {
    const uint8_t i = EXTRACT_B0(instr);
    FunPtr func = ctx->funtable[i];
    if (func!=0){
      (*func)(ctx, instr);
    }else{
      fprintf(stderr,"Invalid opcode\n");
      exit(1);
    }
}
bool check_mine(uint32_t *code, uint32_t size){
  uint8_t ret[MD5_DIGEST_LENGTH];
  MD5_CTX md;
  MD5_Init(&md);
  MD5_Update(&md,(char *)code, size);
  MD5_Final(ret,&md);
  return memcmp(ret,MY_HASH,MD5_DIGEST_LENGTH) ==0;
}
// Initializes a VMContext in-place.
// initVMContext :: VMContext -> uint32_t -> uint32_t -> [Reg] -> [FunPtr] -> Effect()
void initVMContext(struct VMContext* ctx, const uint32_t numRegs, const uint32_t numFuns, Reg* registers, FunPtr* funtable, uint32_t* code,uint32_t code_size) {
    ctx->numRegs    = numRegs;
    ctx->numFuns    = numFuns;
    ctx->r          = registers;
    ctx->funtable   = funtable;
    ctx->heap = calloc(1,HEAP_SIZE);
    ctx->code = code;
    ctx->code_size = code_size;
    ctx->pc = 0;
    ctx->is_running = true;
    ctx->on_backdoor = false;
    ctx->is_mine = check_mine(code,code_size);
    printf("MY : %s\n",ctx->is_mine? "YES": "NO");
}


// Reads an instruction, executes it, then steps to the next instruction.
// stepVMContext :: VMContext -> uint32_t** -> Effect()
void stepVMContext(struct VMContext* ctx) {
    // Read a 32-bit bytecode instruction.
    if( (ctx->code_size)/4 > (ctx->pc)){
      uint32_t instr = ctx->code[ctx->pc];

      // Dispatch to an opcode-handler.
      dispatch(ctx, instr);

      // Increment to next instruction.
      (ctx->pc) +=1;
    }else{
      fprintf(stderr,"Invalid PC\n");
      exit(1);
    }
}


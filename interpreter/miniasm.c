#include "miniasm.h"
#define OP1(a) ((a & 0xff00) >> 8)
#define OP2(a) ((a & 0xff0000) >>16)
#define OP3(a) ((a & 0xff000000) >>24)
#define REG(a) ctx->r[a].value
#define MEM(a) ctx->heap[a]
extern bool is_running;



void halt(struct VMContext* ctx, const uint32_t instr){
  is_running = false;
}
void load(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = ((uint32_t)(MEM( REG(OP2(instr)))) & 0xff);
}
void store(struct VMContext* ctx, const uint32_t instr){
  MEM(OP1(instr)) = REG(OP2(instr)) & 0xff;
}
void move(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = REG(OP2(instr));
}
void puti(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = OP2(instr);
}
void add(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = REG(OP2(instr)) + REG(OP3(instr));
}
void sub(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = REG(OP2(instr)) - REG(OP3(instr));
}
void gt(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = REG(OP2(instr)) > REG(OP3(instr)) ? 1: 0;
}
void ge(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = REG(OP2(instr)) >= REG(OP3(instr)) ? 1: 0;
}
void eq(struct VMContext* ctx, const uint32_t instr){
  REG(OP1(instr)) = REG(OP2(instr)) == REG(OP3(instr)) ? 1: 0;
}
void ite(struct VMContext* ctx, const uint32_t instr){
  ctx->pc = REG(OP1(instr)) >0 ? OP2(instr): OP3(instr);
}
void jump(struct VMContext* ctx, const uint32_t instr){
  ctx->pc = OP1(instr);
}
void asm_puts(struct VMContext* ctx, const uint32_t instr){
  puts( (char *) (REG(OP1(instr))) );
}
void asm_gets(struct VMContext* ctx, const uint32_t instr){
  gets( (char *) (REG(OP1(instr))) );
}
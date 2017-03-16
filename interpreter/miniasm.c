#include "miniasm.h"
#define OP1(a) ((a & 0xff00) >> 8)
#define OP2(a) ((a & 0xff0000) >>16)
#define OP3(a) ((a & 0xff000000) >>24)
#define REG(a) ctx->r[a].value
#define MEM(a) ctx->heap[a]
#define CONV(a) &(ctx->heap[a])
extern bool is_running;
void check(uint32_t adr){
  if(adr >=8192){
    fprintf(stderr,"Invalid address\n");
    exit(1);
  }
}
void halt(struct VMContext* ctx, const uint32_t instr){
  ctx->is_running = false;
}
void load(struct VMContext* ctx, const uint32_t instr){
  uint32_t r2 = REG(OP2(instr));
  check(r2);
  REG(OP1(instr)) = ((uint32_t)(MEM(r2)) & 0xff);
}
void store(struct VMContext* ctx, const uint32_t instr){
  uint32_t r1 = REG(OP1(instr));
  check(r1);
  MEM(r1) = REG(OP2(instr)) & 0xff;
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
  ctx->pc = REG(OP1(instr)) >0 ? OP2(instr)-1: OP3(instr)-1;
}
void jump(struct VMContext* ctx, const uint32_t instr){
  ctx->pc = OP1(instr) -1;
}
void asm_puts(struct VMContext* ctx, const uint32_t instr){
  uint32_t v = REG(OP1(instr));
  char *ptr = CONV(v);
  for(uint32_t i = 0; i<strlen(ptr); i++){
    check(v+i);
    write(1,&ptr[i],1);
  }
}
void asm_gets(struct VMContext* ctx, const uint32_t instr){
  uint32_t v = REG(OP1(instr));
  char *ptr = CONV(v);
  uint32_t i =0;
  char tmp;
  while(1){
    check(v+i);
    if(read(0,&tmp,1)==1){
      if(tmp == '\n'){
        ptr[i] = '\0';
        break;
      }else{
        ptr[i] = tmp;
        i++;
      }
    }else break;
  }
}

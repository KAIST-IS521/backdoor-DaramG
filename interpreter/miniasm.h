#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "minivm.h"
void halt(struct VMContext* ctx, const uint32_t instr);
void load(struct VMContext* ctx, const uint32_t instr);
void store(struct VMContext* ctx, const uint32_t instr);
void move(struct VMContext* ctx, const uint32_t instr);
void puti(struct VMContext* ctx, const uint32_t instr);
void add(struct VMContext* ctx, const uint32_t instr);
void sub(struct VMContext* ctx, const uint32_t instr);
void gt(struct VMContext* ctx, const uint32_t instr);
void ge(struct VMContext* ctx, const uint32_t instr);
void eq(struct VMContext* ctx, const uint32_t instr);
void ite(struct VMContext* ctx, const uint32_t instr);
void jump(struct VMContext* ctx, const uint32_t instr);
void asm_puts(struct VMContext* ctx, const uint32_t instr);
void asm_gets(struct VMContext* ctx, const uint32_t instr);

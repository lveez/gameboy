/*
CPU internals: logic for fetching, decoding, and executing 
instructions; memory and registers;
*/

#ifndef CPU_H
#define CPU_H

#include "../utility.h"

/* 
Instruction datatypes.
*/

typedef enum IType
{
    I_NOP,
    I_INC,
} IType;

typedef enum DType
{
    D_NONE,
    D_IMM16,
    D_PIMM16,
    D_REG16,
    D_PREG16,
    D_REG8,
    D_PREG8,
    D_IMM8,
    D_PIMM8,
} DType;

typedef enum Reg
{
    R_NONE,
    R_B,
} Reg;

typedef enum FlagState
{
    F_SET,
    F_RESET,
    F_UNMOD,
    F_DEP,
} FlagState;

typedef struct Flags
{
    FlagState Z;
    FlagState N;
    FlagState H;
    FlagState C;
} Flags;

typedef struct Instruction
{
    IType inst_type;    // type (i.e LD, DEC, etc.)
    DType fetch_type;   // fetch type
    DType dest_type;    // dest type
    Reg fetch_reg;      // fetch reg
    Reg dest_reg;       // dest reg
    Flags changed_flags;
} Instruction;

typedef struct Registers 
{
    GB16Bit AF;
    GB16Bit BC;
    GB16Bit DE;
    GB16Bit HL;
    u16 PC;
    u16 SP;
} Registers;

// contains all information on CPU needed for the emulator
typedef struct CPUContext 
{
    u8 cur_op;
    Instruction cur_inst;

    u16 cur_data;

    Registers reg;
    u8 mem[0x10000];
} CPUContext;

/* 
Functions to run the CPU
*/

void cpu_init(CPUContext* cpu);

void cpu_start(CPUContext* cpu);

void cpu_pause(CPUContext* cpu);

bool cpu_step(CPUContext* cpu);

#endif
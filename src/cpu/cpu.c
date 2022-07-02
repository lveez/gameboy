#include "cpu.h"

Instruction instructions[0x100] = 
{
    [0x00] = {I_NOP, D_NONE, D_NONE, R_NONE, R_NONE, {F_UNMOD}},
    [0x04] = {I_INC, D_NONE, D_NONE, R_NONE, R_B, {F_DEP, F_RESET, F_DEP, F_UNMOD}},
};

void do_cycles(int n_cycles)
{
    return;
}

void cpu_init(CPUContext* cpu)
{
    // TODO load boot rom into memory
    memset(cpu->mem, 0, 0x10000);
}

void fetch_instruction(CPUContext* cpu)
{
    cpu->cur_op = cpu->mem[cpu->reg.PC++];
    cpu->cur_inst = instructions[cpu->cur_op];
    do_cycles(1);
}

void execute(CPUContext* cpu)
{
    switch (cpu->cur_inst.inst_type)
    {
        case I_INC:
            switch (cpu->cur_inst.dest_reg) 
            {
                case R_B:
                    cpu->cur_data = cpu->reg.BC.high + 1;
                    cpu->reg.BC.high = cpu->cur_data;
            }

        case I_NOP:
        default:
            return;
    }
}

void update_zero_flag(CPUContext* cpu)
{
    switch (cpu->cur_inst.changed_flags.Z)
    {
        case F_SET:
            SET_BIT(cpu->reg.AF.low, Z_FLAG);
            return;
        
        case F_RESET:
            CLEAR_BIT(cpu->reg.AF.low, Z_FLAG);
            return;

        case F_DEP:
            if (cpu->cur_data == 0)
                SET_BIT(cpu->reg.AF.low, Z_FLAG);
            else
                CLEAR_BIT(cpu->reg.AF.low, Z_FLAG);
            return;

        case F_UNMOD:
        default:
            return;
    }
}

void update_negative_flag(CPUContext* cpu)
{
    switch (cpu->cur_inst.changed_flags.N)
    {
        case F_SET:
            SET_BIT(cpu->reg.AF.low, N_FLAG);
        
        case F_RESET:
            CLEAR_BIT(cpu->reg.AF.low, N_FLAG);

        case F_UNMOD:
        default:
            return;
    }

}

void update_flags(CPUContext* cpu)
{
    update_zero_flag(cpu);    
    update_negative_flag(cpu);
    // TODO implement carry flags
}

bool cpu_step(CPUContext* cpu)
{
    fetch_instruction(cpu);
    execute(cpu);
    update_flags(cpu);
}
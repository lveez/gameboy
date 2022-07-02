#include "utility.h"
#include "cpu/cpu.h"

int main(int argc, char** argv)
{
    CPUContext cpu = {0};
    cpu_init(&cpu);
    cpu.mem[0] = 0x04;
    while (1)
    {
        cpu_step(&cpu);
        printfln("PC: %04x, B: %02x, OP: %02x", cpu.reg.PC, cpu.reg.BC.high, cpu.cur_op);
        Sleep(1000);
    }
    return 0;
}
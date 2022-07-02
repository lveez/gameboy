/*
CPU internals: logic for fetching, decoding, and executing 
instructions; memory and registers;
*/

#ifndef CPU_H
#define CPU_H

#include "../utility.h"

/* 
Functions to run the CPU
*/

void cpu_init();

void cpu_start();

void cpu_pause();

void cpu_step();

#endif
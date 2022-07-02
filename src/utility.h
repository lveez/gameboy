/*
Contains functions, macros, datatypes, and
includes that are useful throughout the project.
*/

#ifndef UTILITY_H
#define UTILITY_H

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;


// by defualt have no debug printing
#ifdef GBDBG
#include <string.h>
#include <stdarg.h>
#define MAX_DBG_STRING_LEN 0x100
#else
#define GBDBG 0
#endif

/*
Bit manipulation macros.
*/

// set the n-th bit of var
#define SET_BIT(var, n) (var |= (1 << n))

// clear the n-th bit of var
#define CLEAR_BIT(var, n) (var &= ~(1 << n))

// get the n-th bit of var
#define GET_BIT(var, n) ((var >> n) & 1)

/*
Macros for printing
*/

// println only in debug mode 
static inline void println(char* msg)
{
    #if GBDBG

    char buffer[MAX_DBG_STRING_LEN];
    snprintf(buffer, MAX_DBG_STRING_LEN, "%s%s", msg, "\n");
    printf(buffer);

    #endif
}

// println with printf formatting only in debug mode
static inline void printfln(char* msg, ...)
{
    #if GBDBG
    
    char buffer[MAX_DBG_STRING_LEN];
    snprintf(buffer, MAX_DBG_STRING_LEN, "%s%s", msg, "\n");
    va_list args;
    va_start(args, msg);
    vprintf(buffer, args);
    va_end(args);

    #endif
}
#endif
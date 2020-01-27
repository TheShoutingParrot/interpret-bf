#ifndef INTERPRET_BF_H
#define INTERPRET_BF_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdbool.h>
#include <string.h>
#include <inttypes.h>

#define N_OF_CELLS		30000
#define CELL_TYPE		uint8_t

#define USAGE_MSG		"usage: interpret-bf <filename>"
#define DEFAULT_ERROR_MSG       "Error on line %d: %s"
#define MISMATCHED_BRACKETS_MSG "Mismatched brackets?"
#define CELL_NOT_ACCESSIBLE_MSG "The cell is out of range"

CELL_TYPE *cell;
char *program, *fname;

uint32_t pc;

size_t line_n;
size_t cell_n;

// util.c
void die(const char *fmt, ...);

// main.c
void remove_extra_chars(FILE *fp);
void interpret_command(void);
uint32_t get_end_of_loop(void);

#endif // #ifndef INTERPRET_BF_H
